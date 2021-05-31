#ifndef MYTREE_H
#define MYTREE_H
#include "tree.h"

class MyTree : public Tree
{
public:
    MyTree();
    MyTree(QVector<std::pair<int, QString>> *arr);

    void removeBranch(int key);

private:
    void findAndRemove(int key, Node * cur);
};

#endif // MYTREE_H
