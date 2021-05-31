#ifndef TREE_H
#define TREE_H

#include <utility>
#include <QString>
#include "node.h"
#include <QVector>
class Tree
{
public:
    Tree();
    Tree(QVector<std::pair<int, QString>> *arr);

    Node *root;

    void add(int key, QString value);
    void add(QVector<std::pair<int, QString>> *arr);

    void remove(int key);

    QString find(int key);

    void balance();
    void dispose();

    QVector<std::pair<int, QString>> *getSorted();
    QVector<std::pair<int, QString>> *getForward();
    QVector<std::pair<int, QString>> *getBack();

protected:
    void pushRecursivly(Node *value, Node *current);

    void removeRecursivly(int key, Node *current, Node *parent);
    Node *findMostLeft(Node *startPos);

    QString findRecursivly(int key, Node *current);

    void disposeRecursivly(Node *first);
    void addSorted(QVector<std::pair<int, QString>> *out, int left, int right);

    void dfsSorted(Node *current, QVector<std::pair<int, QString>> *out);
    void dfsForward(Node *current, QVector<std::pair<int, QString>> *out);
    void dfsBack(Node *current, QVector<std::pair<int, QString>> *out);
};

#endif // TREE_H
