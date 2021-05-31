#include "node.h"

Node::Node(int key, QString value)
{
    this->key = key;
    this->value = value;

    prev = nullptr;
    next = nullptr;
}
