#include "myhashmap.h"

MyHashMap::MyHashMap(int capacity) : HashMap(capacity)
{

}

void MyHashMap::removeNegativeKeys()
{
    for (int i = 0; i < capacity; i++)
    {
        if (!arr[i]->isEmpty())
        {
            Node *current = arr[i]->first;

            while (current != nullptr)
            {
                if (current->key < 0)
                {
                    int k = current->key;
                    current = current->next;
                    arr[i]->remove(k);
                    continue;
                }
                current = current->next;
            }
        }
    }
}
