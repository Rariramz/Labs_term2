#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    Node(QString, QString, QString, bool, bool, int *);

    Node *prev, *next;

    QString surname, name, patronim;
    int *marks;
    double averagePoint;
    bool missedExam = false;
    bool thisUniversity = true;
};

#endif // NODE_H
