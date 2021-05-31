#ifndef LIST_H
#define LIST_H

#include "node.h"

class List
{
public:
    List();

    Node *first, *last;

    bool isEmpty();
    int getLength();

    void pushBack(QString surname, QString name, QString patronim,
                  bool missedExam, bool thisUniversity, int *marks);
    int remove(); //возвращает количество удаленных элементов

    int findBySurname(QString surname, int** arr);  //возвращает количество найденных совпадений

    QString toString(QString format = "All", int index = 0);

    double getAveragePointByUniversity();
    int findByHighestAveragePoint(double averagePointByUniversity, int** arr);  //возвращает количество абитуриентов
                                                                               //со ср.баллом выше ср.балла по университету
};

#endif // LIST_H

