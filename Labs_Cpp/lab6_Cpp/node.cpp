#include "node.h"

Node::Node(int key, QString value)
{
    this->key = key;
    this->value = value;

    left = nullptr;
    right = nullptr;
}
