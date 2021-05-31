#include "queue.h"

Queue::Queue()
{
    first = nullptr;
    last = nullptr;
}

bool Queue::isEmpty()
{
    return (first == nullptr && last == nullptr);
}

void Queue::push(int value)
{
    Node *node = new Node(value);

    if (first == nullptr)
    {
        first = node;
        last = node;
    }
    else
    {
        node->prev = last;
        last->next = node;
        last = node;
    }
}

int Queue::front()
{
    return first->value;
}

void Queue::pop()
{
    if (isEmpty())
        return;

    Node *node = first;

    if (first == last)
    {
        first = nullptr;
        last = nullptr;
    }
    else
    {
        first = first->next;
        first->prev = nullptr;
    }
    delete node;
}
