#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tree = new MyTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void updateRecursivly(Node *curNode, QTreeWidgetItem *prevItem, bool isLeft)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(prevItem);
    item->setText(0, QString::number(curNode->key) + " " + curNode->value);

    if (isLeft)
        item->setForeground(0, Qt::GlobalColor::blue);
    else
        item->setForeground(0, Qt::GlobalColor::red);

    if (curNode->left != nullptr)
        updateRecursivly(curNode->left, item, true);

    if (curNode->right != nullptr)
        updateRecursivly(curNode->right, item, false);
}

void MainWindow::update()
{
    ui->treeWidget->clear();

    if (tree->root == nullptr)
        return;

    QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);

    root->setText(0, QString::number(tree->root->key) + " " + tree->root->value);

    ui->treeWidget->addTopLevelItem(root);

    if (tree->root->left != nullptr)
        updateRecursivly(tree->root->left, root, true);

    if (tree->root->right != nullptr)
        updateRecursivly(tree->root->right, root, false);
}

void MainWindow::print(QVector<std::pair<int, QString>> *arr)
{
    if (arr == nullptr)
        return;

    for (auto i : *arr)
        ui->textEdit->append(QString::number(i.first) + " - " + i.second);
}

void MainWindow::on_pushButtonInitialize_clicked()
{
    if (tree != nullptr)
        tree->dispose();

    tree = new MyTree();

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        int key = ui->tableWidget->item(i, 0)->text().toInt();
        QString value = ui->tableWidget->item(i, 1)->text();
        tree->add(key, value);
    }
    update();
}

void MainWindow::on_pushButtonPlus_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void MainWindow::on_pushButtonMinus_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
}

void MainWindow::on_pushButtonAdd_clicked()
{
    int key = ui->lineEditKeyAdd->text().toInt();
    QString value = ui->lineEditValueAdd->text();

    tree->add(key, value);
    update();
}

void MainWindow::on_pushButtonRemove_clicked()
{
    int key = ui->lineEditKeyRemove->text().toInt();

    tree->remove(key);
    update();
}

void MainWindow::on_pushButtonSearch_clicked()
{
    QString value = tree->find(ui->lineEditSearch->text().toInt());
    ui->labelValueSearch->setText("Значение: " + value);
}

void MainWindow::on_pushButtonShow_clicked()
{
    ui->textEdit->clear();
    print(tree->getSorted());
    ui->textEdit->append("--------------------");
    print(tree->getForward());
    ui->textEdit->append("--------------------");
    print(tree->getBack());
}

void MainWindow::on_pushButtonBalance_clicked()
{
    tree->balance();
    update();
}

void MainWindow::on_pushButtonDelBranch_clicked()
{
    int key = ui->lineEditKeyDelBranch->text().toInt();

    tree->removeBranch(key);
    update();
}
