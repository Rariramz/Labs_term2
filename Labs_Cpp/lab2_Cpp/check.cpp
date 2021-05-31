#include "check.h"

Check::Check(QString type, QString model, QDate receptionDate, QDate returnDate = QDate::currentDate(), bool isCompleted = false)
{
    this->type = type;
    this->model = model;
    this->receptionDate = receptionDate;
    this->returnDate = returnDate;
    this->isCompleted = isCompleted;
}
