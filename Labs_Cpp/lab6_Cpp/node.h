#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    Node(int key, QString value);

    Node *left, *right;

    int key;
    QString value;
};

#endif // NODE_H
