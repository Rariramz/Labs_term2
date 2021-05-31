#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "list.h"

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
    void on_pushButtonDelete_clicked();

    void on_pushButtonInfo_clicked();

    void on_pushButtonShowAll_clicked();

    void on_pushButtonHighAveragePoint_clicked();

    void on_lineEditSurname_textChanged(const QString &arg1);
    void on_lineEditName_textChanged(const QString &arg1);
    void on_lineEditPatronim_textChanged(const QString &arg1);
    void on_lineEditMark1_textChanged(const QString &arg1);
    void on_lineEditMark2_textChanged(const QString &arg1);
    void on_lineEditMark3_textChanged(const QString &arg1);
    void on_lineEditFindBySurname_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    void isAddingPossible();
    bool isDigit(QString text);

    List *list;
    int count;
};
#endif // MAINWINDOW_H
