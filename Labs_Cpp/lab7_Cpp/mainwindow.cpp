#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    map = new MyHashMap(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    ui->treeWidget->clear();

    for (int i = 0; i < map->capacity; i++)
    {
        if (!map->arr[i]->isEmpty())
        {
            QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
            root->setText(0, QString::number(i));

            Node *current = map->arr[i]->first;

            while (current != nullptr)
            {
                QTreeWidgetItem *val = new QTreeWidgetItem(root);
                val->setText(0, QString::number(current->key) + " - " + current->value);
                current = current->next;
            }
        }
    }
}

void MainWindow::on_pushButtonPlus_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void MainWindow::on_pushButtonMinus_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
}

void MainWindow::on_pushButtonInitialize_clicked()
{
    map->clear();

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        int key = ui->tableWidget->item(i, 0)->text().toInt();
        QString value = ui->tableWidget->item(i, 1)->text();

        map->add(key, value);
    }
    update();
}

void MainWindow::on_pushButtonAdd_clicked()
{
    int key = ui->lineEditKeyAdd->text().toInt();
    QString value = ui->lineEditValueAdd->text();

    map->add(key, value);
    update();
}

void MainWindow::on_pushButtonRemove_clicked()
{
    int key = ui->lineEditKeyRemove->text().toInt();

    map->remove(key);
    update();
}

void MainWindow::on_pushButtonSearch_clicked()
{
    QString value = map->find(ui->lineEditKeySearch->text().toInt());
    ui->labelValueSearch->setText("Значение: " + value);
}

void MainWindow::on_pushButtonDelNegativeKeys_clicked()
{
    map->removeNegativeKeys();
    update();
}
