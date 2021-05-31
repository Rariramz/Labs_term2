#ifndef CHECK_H
#define CHECK_H

#include <QString>
#include <QDate>

class Check
{
public:
    Check(QString type, QString model, QDate receptionDate, QDate returnDate, bool isCompleted);
    QString type;
    QString model;
    QDate receptionDate;
    QDate returnDate;
    bool isCompleted;
};

#endif // CHECK_H
