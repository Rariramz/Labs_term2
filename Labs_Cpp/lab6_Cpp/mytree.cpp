#include "mytree.h"

MyTree::MyTree() : Tree()
{

}

MyTree::MyTree(QVector<std::pair<int, QString> > *arr) : Tree(arr)
{

}

// ---------------------------------- Удаление из дерева ветви с вершиной, имеющей заданный ключ
void MyTree::removeBranch(int key)
{
    if (root == nullptr)
        return;

    findAndRemove(key, root);
}

void MyTree::findAndRemove(int key, Node *current)
{
    if (current->left != nullptr && key <= current->key)
    {
        if (current->left->key == key)
        {
            disposeRecursivly(current->left); //рекурсивное очищение ветви с найденной вершиной
            current->left = nullptr;
        }
        else if (key < current->key)
            findAndRemove(key, current->left);
    }
    if (current->right != nullptr && key >= current->key)
    {
        if (current->right->key == key)
        {
            disposeRecursivly(current->right); //нашли нужную вершину, рекурсивно очищаем ветвь
            current->right = nullptr;
        }
        else if (key > current->key)
            findAndRemove(key, current->right);
    }
    if (key == current->key)
    {
        disposeRecursivly(current);
        root = nullptr;
    }
}




