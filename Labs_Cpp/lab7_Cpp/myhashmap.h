#ifndef MYHASHMAP_H
#define MYHASHMAP_H

#include "hashmap.h"

class MyHashMap : public HashMap
{
public:
    MyHashMap(int capacity);

    void removeNegativeKeys();
};

#endif // MYHASHMAP_H
