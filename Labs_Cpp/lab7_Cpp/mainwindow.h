#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myhashmap.h"
#include <QMainWindow>
#include <QString>

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
    void on_pushButtonPlus_clicked();
    void on_pushButtonMinus_clicked();

    void on_pushButtonInitialize_clicked();

    void on_pushButtonAdd_clicked();
    void on_pushButtonRemove_clicked();
    void on_pushButtonSearch_clicked();

    void on_pushButtonDelNegativeKeys_clicked();

private:
    Ui::MainWindow *ui;

    MyHashMap * map;

    void update();
};
#endif // MAINWINDOW_H
