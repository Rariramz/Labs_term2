#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"
#include <QString>

class HashMap
{
public:
    HashMap(int capacity);

    int capacity;

    void add(int key, QString value);
    void remove(int key);
    int getHash(int key);
    QString find(int key);
    void clear();

    List **arr;
};

#endif // HASHMAP_H
