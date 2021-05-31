#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mytree.h"
#include <QMainWindow>
#include <QColor>
#include <QStandardItemModel>
#include <QString>
#include <QTreeWidgetItem>
#include <qstring.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonInitialize_clicked();

    void on_pushButtonPlus_clicked();

    void on_pushButtonMinus_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButtonShow_clicked();

    void on_pushButtonBalance_clicked();

    void on_pushButtonDelBranch_clicked();

private:
    Ui::MainWindow *ui;

    MyTree *tree;

    void update();
    void print(QVector<std::pair<int, QString>> *arr);
};
#endif // MAINWINDOW_H
