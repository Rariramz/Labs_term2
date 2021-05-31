#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    Node(int key, QString value);

    int key;
    QString value;

    Node *next;
    Node *prev;
};

#endif // NODE_H
