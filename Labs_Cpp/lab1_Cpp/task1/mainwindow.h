#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <rocket.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButtonON_clicked();

    void on_pushButtonOFF_clicked();

    void Run();

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    Rocket *rocket;
};
#endif // MAINWINDOW_H
