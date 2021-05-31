#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

#include "check.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString fileOpenName, fileSaveName;

    int amount = 0;
    Check **checks = new Check*[1000];
    int k;

    void addCheck();
    void removeCheck(Check*);
    void sortChecks();
    void showCheck(Check*, int);
    void correctCheck();
    int* search();

    void saveFile();
    void readFile();

    void blockButtons();

private slots:
    void on_pushButtonAdd_clicked();
    void on_comboBoxChecks_currentIndexChanged(int index);
    void on_pushButtonShowAll_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonSort_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonCorrect_clicked();
    void on_pushButtonShowNotCompleted_clicked();
    void on_pushButtonSearch_clicked();
    void on_comboBoxParameters_currentIndexChanged(int index);

    void on_lineEditReceptionDate_cursorPositionChanged(int arg1, int arg2);
    void on_lineEditReturnDate_cursorPositionChanged(int arg1, int arg2);
    void on_lineEditType_cursorPositionChanged(int arg1, int arg2);
    void on_lineEditModel_cursorPositionChanged(int arg1, int arg2);
    void on_lineEditSearchBy_cursorPositionChanged(int arg1, int arg2);
    void on_lineEditCorrect_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
