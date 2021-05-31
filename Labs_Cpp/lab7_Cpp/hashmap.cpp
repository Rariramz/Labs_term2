#include "hashmap.h"

HashMap::HashMap(int capacity)
{
    this->capacity = capacity;

    arr = new List*[capacity];

    for (int i = 0; i < capacity; i++)
        arr[i] = new List();
}

void HashMap::add(int key, QString value)
{
    int index = std::abs(getHash(key) % capacity);
    arr[index]->add(key, value);
}

void HashMap::remove(int key)
{
    int index = std::abs(getHash(key) % capacity);
    arr[index]->remove(key);
}

int HashMap::getHash(int key)
{
    return key;
}

QString HashMap::find(int key)
{
    int index = std::abs(getHash(key) % capacity);
    return arr[index]->find(key);
}

void HashMap::clear()
{
    for (int i = 0; i < capacity; i++)
        arr[i]->clear();
}
