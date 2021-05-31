#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

class Queue
{
public:
    Queue();

    void push(int value);
    int front();
    void pop();
    bool isEmpty();

    Node *first;
    Node *last;
};

#endif // QUEUE_H
