#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);

    readFile();

    ui->comboBoxParameters->addItem("Тип");
    ui->comboBoxParameters->addItem("Марка");
    ui->comboBoxParameters->addItem("Время получения заказа");
    ui->comboBoxParameters->addItem("Время исполнения заказа");
    ui->comboBoxParameters->addItem("Готовность заказа");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// -------------------------------------------------------- Добавить чек
void MainWindow::addCheck()
{
    QString type = ui->lineEditType->text();
    QString model = ui->lineEditModel->text();
    bool isCompleted = false;
    QString recDate = ui->lineEditReceptionDate->text();
    QDate receptionDate = QDate(QDate::fromString(recDate, "dd.MM.yyyy"));
    QString retDate = ui->lineEditReturnDate->text();
    QDate returnDate = QDate(QDate::fromString(retDate, "dd.MM.yyyy"));

    if (!(receptionDate.isValid() || (retDate == "" && returnDate.isValid())))
        ui->textEdit->setText("Неправильный формат даты.\nПопробуйте ввести ее в виде \"dd.mm.yyyy\"");
    else
    {
        if (receptionDate > QDate::currentDate() || returnDate > QDate::currentDate())
            ui->textEdit->setText("Вы из будущего? :)\nПерепроверьте введённые даты");
        else
        if (receptionDate > returnDate && !returnDate.isNull())
            ui->textEdit->setText("Дата исполнения заказа не может быть больше даты получения заказа");
        else
        {
            if (returnDate.isValid())
                isCompleted = true;

            Check *check = new Check(type, model, receptionDate, returnDate, isCompleted);
            checks[amount] = check;

            ui->comboBoxChecks->addItem(check->type);
            ui->comboBoxChecks->setCurrentIndex(amount);

            amount++;


            ui->lineEditType->clear();
            ui->lineEditModel->clear();
            ui->lineEditReceptionDate->clear();
            ui->lineEditReturnDate->clear();
            ui->lineEditIsCompleted->clear();

            if (ui->comboBoxChecks->currentIndex() == 0)
            {
                ui->pushButtonSort->setEnabled(true);
                ui->pushButtonDelete->setEnabled(true);
                ui->pushButtonShowAll->setEnabled(true);
                ui->pushButtonShowNotCompleted->setEnabled(true);
            }
        }
    }
}

// -------------------------------------------------------- Удалить чек
void MainWindow::on_pushButtonDelete_clicked()
{
    if (ui->comboBoxChecks->currentIndex() > -1)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  "Удаление квитанции","Вы действительно желаете удалить эту квитанцию?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            int i = ui->comboBoxChecks->currentIndex();
            delete checks[i];
            ui->comboBoxChecks->removeItem(i);
            amount--;
        }
    }
    else
    {
        ui->textEdit->setText("Список пуст");
        blockButtons();
    }
}

// -------------------------------------------------------- Показать квитанцию
void MainWindow::showCheck(Check *check, int i)
{
    ui->textEdit->append("Квитанция #" + QString::number(i + 1) + "\n" +
                         "Тип: " + check->type + "\n" +
                         "Марка: " + check->model + "\n" +
                         "Дата получения заказа: " + check->receptionDate.toString(Qt::SystemLocaleLongDate) + "\n" +
                         "Дата исполнения заказа: " + check->returnDate.toString(Qt::SystemLocaleLongDate) + "\n" +
                         "Заказ выполнен: " + ({check->isCompleted ? "да" : "нет";}) + "\n");
}

// -------------------------------------------------------- Сортировать по убыванию даты исполнения заказа
bool cmpByDate(Check* left, Check* right)
{
    if (left->returnDate.isValid() && right->returnDate.isValid())
        return left->returnDate > right->returnDate;
    else
    if (!left->returnDate.isValid() && right->returnDate.isValid())
        return 1;
    else
    if (left->returnDate.isValid() && !right->returnDate.isValid())
        return 0;
    else
        return 1;
}

void MainWindow::sortChecks()
{
    if (ui->comboBoxChecks->currentIndex() != -1)
    {
        std::sort(checks, checks + amount, cmpByDate);
        ui->textEdit->clear();
        on_pushButtonShowAll_clicked();
    }
}

// -------------------------------------------------------- Поиск по параметру
int* MainWindow::search()
{
    if (ui->comboBoxChecks->currentIndex() != -1)
    {
        QString input = ui->lineEditSearchBy->text();
        int parameterIndex = ui->comboBoxParameters->currentIndex();
        int* numbers = new int[100];

        k = 0;
        for (int i = 0; i < amount; i++)
        {
            switch(parameterIndex)
            {
            case 0: //by type
            {
                    if (checks[i]->type == input)
                        numbers[k++] = i;
                    break;
            }
            case 1: //by model
            {
                if (checks[i]->model == input)
                    numbers[k++] = i;
                break;
            }
            case 2: //by receptionDate
            {
                if (checks[i]->receptionDate == QDate::fromString(input, "dd.MM.yyyy"))
                    numbers[k++] = i;
                break;
            }
            case 3: //by returnDate
            {
                if (checks[i]->returnDate == QDate::fromString(input, "dd.MM.yyyy"))
                    numbers[k++] = i;
                break;
            }
            case 4: //by isComplited
            {
                bool is = (input == "+" || input == "Yes" || input == "yes");
                if (checks[i]->isCompleted == is)
                    numbers[k++] = i;
                break;
            }
            }
        }

        if (k == 0)
            numbers[0] = -1;

        return numbers;
    }
}

// -------------------------------------------------------- Считать информацию с файла
void MainWindow::readFile()
{
    fileOpenName = QFileDialog::getOpenFileName(this, "Выберите файл", /*"C://"*/"/labs2sem/C++/lab2_Cpp/docChecks.txt");
    QFile f(fileOpenName);

    if(!f.exists())
    {
        QMessageBox::warning(this, "Что-то не так..", "Файл не был открыт");
        QApplication::quit();
    }

    f.open(QFile::ReadOnly);
    QTextStream in(&f);

    amount = in.readLine().toInt();

    for (int i = 0; i < amount; i++)
    {
        in.readLine();
        QString type = in.readLine();
        QString model = in.readLine();
        QString recDate = in.readLine();
        QDate receptionDate = QDate(QDate::fromString(recDate, "dd.MM.yyyy"));
        QString retDate = in.readLine();
        QDate returnDate = QDate(QDate::fromString(retDate, "dd.MM.yyyy"));
        bool isCompleted = true;
        if (retDate == "")
            isCompleted = false;
        Check *check = new Check(type, model, receptionDate, returnDate, isCompleted);
        checks[i] = check;

        ui->comboBoxChecks->addItem(check->type);
    }

    f.close();
}

// -------------------------------------------------------- Блокировать кнопки управления списком
void MainWindow::blockButtons()
{
    ui->pushButtonSort->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
    ui->pushButtonSearch->setEnabled(false);
    ui->pushButtonCorrect->setEnabled(false);
    ui->pushButtonShowAll->setEnabled(false);
    ui->pushButtonShowNotCompleted->setEnabled(false);
}

// -------------------------------------------------------- Сохранить изменения в файле
void MainWindow::saveFile()
{
    fileSaveName = QFileDialog::getSaveFileName(this, "Выберите файл", "/labs2sem/C++/lab2_Cpp/docChecks.txt", "TXT files (*.txt)");
    QFile f(fileSaveName);

    f.open(QFile::WriteOnly);
    f.write(QString::number(amount).toUtf8());
    f.write("\n");
    for (int i = 0; i < amount; i++)
    {
        f.write("\n");
        Check *check = checks[i];
        f.write(check->type.toUtf8() + "\n");
        f.write(check->model.toUtf8() + "\n");
        f.write(check->receptionDate.toString("dd.MM.yyyy").toUtf8() + "\n");
        f.write(check->returnDate.toString("dd.MM.yyyy").toUtf8() + "\n");
        //f.write(check->isCompleted ? QString("true").toUtf8() : QString("false").toUtf8());
    }
    f.close();
}

// -------------------------------------------------------- Редактировать информацию квитанции
void MainWindow::correctCheck()
{
    if (ui->comboBoxChecks->currentIndex() != -1)
    {
        int i = ui->comboBoxChecks->currentIndex();

        int parameterIndex = ui->comboBoxParameters->currentIndex();
        switch(parameterIndex)
        {
        case 0: //correct type
        {
            checks[i]->type = ui->lineEditCorrect->text();
            break;
        }
        case 1: //correct model
        {
            checks[i]->model = ui->lineEditCorrect->text();
            break;
        }
        case 2: //correct receptionDate
        {
            QDate newDate(QDate::fromString(ui->lineEditCorrect->text(), "dd.MM.yyyy"));
            if (newDate.isValid())
            {
                if (checks[i]->returnDate.isValid())
                {
                    if (newDate < checks[i]->returnDate)
                        checks[i]->receptionDate = newDate;
                    else
                        ui->textEdit->setText("Дата получения заказа не может быть позже даты исполнения заказа");
                }
            }
            else
                ui->textEdit->setText("Некорректный формат.\nПопробуйте повторить ввод в формате dd.mm.yyyy");
            break;
        }
        case 3: //correct returnDate
        {
            QDate newDate(QDate::fromString(ui->lineEditCorrect->text(), "dd.MM.yyyy"));
            if (newDate.isValid())
            {
                if (newDate > checks[i]->receptionDate)
                    checks[i]->returnDate = newDate;
                else
                    ui->textEdit->setText("Дата исполнения заказа не может быть раньше даты получения заказа");
            }
            else
                ui->textEdit->setText("Некорректный формат.\nПопробуйте повторить ввод в формате dd.mm.yyyy");
            break;
        }
        case 4: //correct isComplited
        {
            if (checks[i]->returnDate.isNull())
                ui->textEdit->setText("Заказ не может быть выполнен, так как дата выдачи не установлена");
            else
                ui->textEdit->setText("Заказ и до этого был выполнен");
            break;
        }
        }
    }
}

// -------------------------------------------------------- События кнопок
void MainWindow::on_pushButtonAdd_clicked()
{
    addCheck();
}

void MainWindow::on_pushButtonShowAll_clicked()
{
    if (ui->comboBoxChecks->currentIndex() != -1)
    {
        ui->textEdit->clear();
        ui->comboBoxChecks->setEditText("");
        for (int i = 0; i < amount; i++)
            showCheck(checks[i], i);
    }
}

void MainWindow::on_pushButtonSort_clicked()
{
    if (ui->comboBoxChecks->currentIndex() != -1)
        sortChecks();
}

void MainWindow::on_pushButtonSave_clicked()
{
    saveFile();
}

void MainWindow::on_pushButtonCorrect_clicked()
{
    int index = ui->comboBoxChecks->currentIndex();

    if (index != -1)
    {
        correctCheck();
        ui->lineEditCorrect->clear();
        ui->pushButtonCorrect->setEnabled(false);

        ui->textEdit->clear();
        showCheck(checks[index], index);
    }
}

void MainWindow::on_pushButtonShowNotCompleted_clicked()
{
    if (ui->comboBoxChecks->currentIndex() != -1)
    {
        ui->textEdit->clear();
        for(int i = 0; i < amount; i++)
            if (!checks[i]->isCompleted)
                showCheck(checks[i], i);
    }
}

void MainWindow::on_pushButtonSearch_clicked()
{
    if (ui->comboBoxChecks->currentIndex() != -1)
    {
        ui->textEdit->clear();

        int* nums = search();
        if (nums[0] != -1)
        {
            for (int i = 0; i < k; i++)
                showCheck(checks[nums[i]], i);
        }
        else
            ui->textEdit->setText("Совпадений не найдено :(");

        ui->lineEditSearchBy->clear();
        ui->pushButtonSearch->setEnabled(false);
    }
}

// -------------------------------------------------------- События текстового редактора
void MainWindow::on_comboBoxChecks_currentIndexChanged(int index)
{
    ui->textEdit->clear();
    if (ui->comboBoxChecks->currentIndex() != -1)
        showCheck(checks[index], index);
}

void MainWindow::on_comboBoxParameters_currentIndexChanged(int index)
{
    ui->lineEditSearchBy->clear();
    ui->lineEditCorrect->clear();
}

// -------------------------------------------------------- События списков элементов
void MainWindow::on_lineEditReceptionDate_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->lineEditReceptionDate->text() != "")
    {
        if (ui->lineEditReturnDate->text() != "")
            ui->lineEditIsCompleted->setText("да");
        else
            ui->lineEditIsCompleted->setText("нет");
    }
    else
        ui->lineEditIsCompleted->clear();

    if (ui->lineEditType->text() != "" && ui->lineEditModel->text() != "" && ui->lineEditReceptionDate->text() != "")
        ui->pushButtonAdd->setEnabled(true);
    else
        ui->pushButtonAdd->setEnabled(false);
}

void MainWindow::on_lineEditReturnDate_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->lineEditReturnDate->text() != "")
    {
        if (ui->lineEditReceptionDate->text() != "")
            ui->lineEditIsCompleted->setText("да");
        else
            ui->lineEditIsCompleted->clear();
    }
    else
    {
        if (ui->lineEditReceptionDate->text() != "")
            ui->lineEditIsCompleted->setText("нет");
        else
           ui->lineEditIsCompleted->clear();
    }
}

void MainWindow::on_lineEditType_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->lineEditType->text() != "" && ui->lineEditModel->text() != "" && ui->lineEditReceptionDate->text() != "")
        ui->pushButtonAdd->setEnabled(true);
    else
        ui->pushButtonAdd->setEnabled(false);
}

void MainWindow::on_lineEditModel_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->lineEditType->text() != "" && ui->lineEditModel->text() != "" && ui->lineEditReceptionDate->text() != "")
        ui->pushButtonAdd->setEnabled(true);
    else
        ui->pushButtonAdd->setEnabled(false);
}

void MainWindow::on_lineEditSearchBy_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->comboBoxChecks->currentIndex() != -1)
    {
        if (ui->lineEditSearchBy->text() != "")
            ui->pushButtonSearch->setEnabled(true);
        else
            ui->pushButtonSearch->setEnabled(false);
    }
}

void MainWindow::on_lineEditCorrect_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->comboBoxChecks->currentIndex() != -1)
    {
        if (ui->lineEditCorrect->text() != "")
            ui->pushButtonCorrect->setEnabled(true);
        else
            ui->pushButtonCorrect->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Выход","Вы желаете сохранить изменения?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
        on_pushButtonSave_clicked();
    QApplication::quit();
}
