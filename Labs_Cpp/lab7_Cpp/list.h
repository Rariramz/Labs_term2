#ifndef LIST_H
#define LIST_H

#include "node.h"

class List
{
public:
    List();

    bool isEmpty();
    bool findAndReplace(int key, QString value);
    void add(int key, QString value);
    void clear();
    QString find(int key);
    void remove(int key);

    Node *first;
    Node *last;
};

#endif // LIST_H
