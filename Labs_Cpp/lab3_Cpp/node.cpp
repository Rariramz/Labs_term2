#include "node.h"

Node::Node(QString surname, QString name, QString patronim,
           bool missedExam, bool thisUniversity, int *marks)
{
    this->surname = surname;
    this->name = name;
    this->patronim = patronim;
    this->missedExam = missedExam;
    this->thisUniversity = thisUniversity;
    this->marks = marks;
    averagePoint = (marks[0] + marks[1] + marks[2]) / 3;

    prev = nullptr;
    next = nullptr;
}
