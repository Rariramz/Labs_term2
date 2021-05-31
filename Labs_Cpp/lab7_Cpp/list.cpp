#include "list.h"

List::List()
{
    first = nullptr;
    last = nullptr;
}

bool List::isEmpty()
{
    return first == nullptr;
}

bool List::findAndReplace(int key, QString value)
{
    Node *current = first;

    while (current != nullptr)
    {
        if (current->key == key)
        {
            current->value = value;
            return true;
        }
        current = current->next;
    }
    return false;
}

void List::add(int key, QString value)
{
    if (findAndReplace(key, value))
        return;

    Node *node = new Node(key, value);

    if (first == nullptr)
    {
        first = node;
        last = node;
    }
    else
    {
        last->next = node;
        node->prev = last;
        last = node;
    }
}

void List::clear()
{
    while(!isEmpty())
        remove(first->key);
}

QString List::find(int key)
{
    Node *current = first;

    while (current != nullptr)
    {
        if (current->key == key)
            return current->value;

        current = current->next;
    }
    return "";
}

void List::remove(int key)
{
    Node *current = first;

    while (current != nullptr)
    {
        if (current->key == key)
        {
            if (first == current && last == current)
            {
                first = nullptr;
                last = nullptr;
            }
            else if (first == current)
            {
                first = current->next;
                first->prev = nullptr;
            }
            else if (last == current)
            {
                last = current->prev;
                last->next = nullptr;
            }
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}
