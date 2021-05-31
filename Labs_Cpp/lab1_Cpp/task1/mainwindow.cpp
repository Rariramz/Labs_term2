#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1000,500);

    rocket = new Rocket(400, 200);

    timer = new QTimer();
    timer->setInterval(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(Run()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonON_clicked()
{
    timer->start(10);
    rocket->FireOn();
    repaint();
}

void MainWindow::on_pushButtonOFF_clicked()
{
    timer->stop();
    rocket->FireOff();
    repaint();
}

void MainWindow::Run()
{
    rocket->Move();
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    rocket->DrawRocket(&painter);
}
