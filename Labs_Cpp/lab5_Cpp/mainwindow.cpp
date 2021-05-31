#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    queue = new RandomQueue();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ------------------------------------------------------------------ Обновление ListView
void MainWindow::update()
{
    QStringListModel *model = new QStringListModel(this);
    QStringList List;

    Node *current = queue->first;
    while (current != nullptr)
    {
        List << QString::number(current->value);
        current = current->next;
    }
    model->setStringList(List);

    ui->listView->setModel(model);
}

// ------------------------------------------------------------------ Добавление элемента в очередь
void MainWindow::on_pushButtonAdd_clicked()
{
    queue->push(ui->lineEditAdd->text().toInt());

    ui->lineEditAdd->clear();
    update();
}

// ------------------------------------------------------------------ Добавление элемента в очередь
void MainWindow::on_pushButtonRemove_clicked()
{
    queue->pop();

    update();
}

// ------------------------------------------------------------------ Создание новой рандомной очереди
void MainWindow::on_pushButtonNewRandomQueue_clicked()
{
    int count = ui->lineEditAmount->text().toInt();
    int lowerBound = ui->lineEditMin->text().toInt();
    int upperBound = ui->lineEditMax->text().toInt();

    queue = new RandomQueue(count, lowerBound, upperBound);

    ui->lineEditAmount->clear();
    ui->lineEditMax->clear();
    ui->lineEditMin->clear();
    update();
}

// ------------------------------------------------------------------ Удаление элемента из очереди
void MainWindow::on_pushButtonDeleteBetwMaxMin_clicked()
{
    queue->clearBetweenMinAndMax();

    update();
}

void MainWindow::on_lineEditAdd_textChanged(const QString &arg1)
{
    if (ui->lineEditAdd->text() != "")
        ui->pushButtonAdd->setEnabled(true);
    else
        ui->pushButtonAdd->setEnabled(false);
}
