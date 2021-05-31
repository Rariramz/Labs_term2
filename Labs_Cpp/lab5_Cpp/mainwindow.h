#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "randomqueue.h"
#include <QAbstractItemView>
#include <QStringListModel>

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
    void on_pushButtonAdd_clicked();
    void on_pushButtonRemove_clicked();

    void on_pushButtonNewRandomQueue_clicked();
    void on_pushButtonDeleteBetwMaxMin_clicked();

    void on_lineEditAdd_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    RandomQueue * queue;

    void update();
};
#endif // MAINWINDOW_H
