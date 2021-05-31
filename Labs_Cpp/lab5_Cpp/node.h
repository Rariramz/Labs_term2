#ifndef NODE_H
#define NODE_H

class Node
{
public:
    Node(int value);

    int value;

    Node *prev;
    Node *next;
};

#endif // NODE_H
