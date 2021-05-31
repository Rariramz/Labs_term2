#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    list = new List();
    count = 0;

    ui->labelWarning->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------------------------------------------------------------------- Добавление нового абитуриента
void MainWindow::on_pushButtonAdd_clicked()
{
    if (!(count < ui->spinBox->value()) && !(ui->checkBoxThisUniversity->isChecked()))
        ui->labelWarning->setVisible(true);
    else
    {
        ui->labelWarning->setVisible(false);

        QString surname = ui->lineEditSurname->text();
        QString name = ui->lineEditName->text();
        QString patronim = ui->lineEditPatronim->text();
        bool missedExam = !ui->checkBoxAttendedExam->isChecked();
        bool thisUniversity = ui->checkBoxThisUniversity->isChecked();
        int mark1 = ui->lineEditMark1->text().toInt();
        int mark2 = ui->lineEditMark2->text().toInt();
        int mark3 = ui->lineEditMark3->text().toInt();
        int *marks = new int[3];
        marks[0] = mark1;
        marks[1] = mark2;
        marks[2] = mark3;

        list->pushBack(surname, name, patronim, missedExam, thisUniversity, marks);

        ui->textEdit->clear();
        ui->textEdit->setText(list->toString());

        ui->lineEditSurname->clear();
        ui->lineEditName->clear();
        ui->lineEditPatronim->clear();
        ui->lineEditMark1->clear();
        ui->lineEditMark2->clear();
        ui->lineEditMark3->clear();

        count++;
    }
}

// ---------------------------------------------------------------------- Удаление отсутствовавших на экзамене
void MainWindow::on_pushButtonDelete_clicked()
{
    count -= list->remove();

    ui->textEdit->clear();
    ui->textEdit->setText(list->toString());
}

// ---------------------------------------------------------------------- Поиск абитуриента по фамилии
void MainWindow::on_pushButtonInfo_clicked() //вывести информацию о студенте
{       
    QString surname = ui->lineEditFindBySurname->text();

    int *nums = new int[list->getLength()];
    int len = list->findBySurname(surname, &nums);

    ui->textEdit->clear();
    if (len != 0)
        for (int i = 0; i < len; i++)
            ui->textEdit->append(list->toString("", nums[i]));
    else
        ui->textEdit->setText("Совпадений не найдено :(");
}

// ---------------------------------------------------------------------- Поиск абитуриентов с высоким средним баллом
void MainWindow::on_pushButtonHighAveragePoint_clicked()
{
    double averagePointByUniversity = list->getAveragePointByUniversity();

    int *nums = new int[list->getLength()];
    int len = list->findByHighestAveragePoint(averagePointByUniversity, &nums);

    ui->textEdit->clear();
    if (len != 0)
        for (int i = 0; i < len; i++)
            ui->textEdit->append(list->toString("", nums[i]));
    else
        ui->textEdit->setText("Не найдено студентов со средним баллом выше среднего балла по университету :(");
}

void MainWindow::on_pushButtonShowAll_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->setText(list->toString());
}

// ------------------------------------------------------------------------------ Обеспечение корректного ввода
void MainWindow::on_lineEditSurname_textChanged(const QString &arg1)
{
    isAddingPossible();
}

void MainWindow::on_lineEditName_textChanged(const QString &arg1)
{
    isAddingPossible();
}

void MainWindow::on_lineEditPatronim_textChanged(const QString &arg1)
{
    isAddingPossible();
}

void MainWindow::on_lineEditMark1_textChanged(const QString &arg1)
{
    isAddingPossible();
}

void MainWindow::on_lineEditMark2_textChanged(const QString &arg1)
{
    isAddingPossible();
}

void MainWindow::on_lineEditMark3_textChanged(const QString &arg1)
{
    isAddingPossible();
}

void MainWindow::isAddingPossible()
{
    if (ui->lineEditSurname->text() != "" && ui->lineEditName->text() != "" && ui->lineEditPatronim->text() != "" &&
            ui->lineEditMark1->text() != "" && ui->lineEditMark2->text() != "" && ui->lineEditMark3->text() != "" &&
            isDigit(ui->lineEditMark1->text()) && isDigit(ui->lineEditMark2->text()) && isDigit(ui->lineEditMark3->text()))
    {
        if (ui->lineEditMark1->text() == '0' && ui->lineEditMark2->text() == '0' && ui->lineEditMark3->text() == '0')
            ui->checkBoxAttendedExam->setChecked(false);
        else
            ui->checkBoxAttendedExam->setChecked(true);

        ui->pushButtonAdd->setEnabled(true);
    }
    else
        ui->pushButtonAdd->setEnabled(false);
}

bool MainWindow::isDigit(QString text)
{
    int n = text.length();

    if (n > 2)
        return false;

    if (n == 2 && text[0] == '1' && text[1] == '0')
        return true;

    if (n == 1 && text[0] >= '0' && text[0] <= '9')
        return true;

    return false;
}

void MainWindow::on_lineEditFindBySurname_textChanged(const QString &arg1)
{
    if (ui->lineEditFindBySurname->text() != "")
        ui->pushButtonInfo->setEnabled(true);
    else
        ui->pushButtonInfo->setEnabled(false);
}
