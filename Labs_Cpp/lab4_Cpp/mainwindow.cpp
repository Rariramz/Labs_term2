#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStack>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QHash<QChar, double> map;
QStack<double> values;
QStack<QChar> operators;

bool isOperator(QChar c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int operatorPriority(QChar c)
{
    if(c == '+' || c == '-')
        return 0;

    if(c == '*' || c == '/')
        return 1;

    return -1;
}

bool MainWindow::proceedOperation()
{
    double b = values.top();
    values.pop();
    double a = values.top();
    values.pop();
    QChar oper = operators.top();
    operators.pop();

    double result;
    switch(oper.unicode())
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
    {
        if(b == 0)
        {
            QMessageBox::warning(this, "Недопустимая операция", "Деление на ноль невозможно");
            return false;
        }
        result = a / b;
        break;
    }
    default:
        result = 0;
    }
    values.push(result);

    return true;
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    map.insert('a', ui->lineEditA->text().toDouble());
    map.insert('b', ui->lineEditB->text().toDouble());
    map.insert('c', ui->lineEditC->text().toDouble());
    map.insert('d', ui->lineEditD->text().toDouble());
    map.insert('e', ui->lineEditE->text().toDouble());

    QString expression = ui->lineEditExpression->text();

    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == ' ')
            continue;

        if (isOperator(expression[i]))
        {
            while (!operators.empty() &&
                   operatorPriority(expression[i]) < operatorPriority(operators.top()))
            {
                if (!proceedOperation())
                    return;
            }
            operators.push(expression[i]);
        }
        else if (expression[i] == '(')
            operators.push(expression[i]);
        else if (expression[i] == ')')
        {
            while (operators.top() != '(')
            {
                if (!proceedOperation())
                    return;
            }
            operators.pop();
        }
        else
            values.push(map.value(expression[i]));
    }

    while (!operators.empty())
    {
        if (!proceedOperation())
            return;
    }

    ui->lineEditResult->setText(QString::number(values.top()));
    values.pop();
}

void MainWindow::on_lineEditExpression_textChanged(const QString &arg1)
{
    if (ui->lineEditExpression->text() != "")
        ui->pushButtonCalculate->setEnabled(true);
    else
        ui->pushButtonCalculate->setEnabled(false);
}
