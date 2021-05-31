#include "tree.h"

Tree::Tree()
{
    root = nullptr;
}

Tree::Tree(QVector<std::pair<int, QString>> *arr)
{
    add(arr);
}

// -------------------------------------------------------------------- Добавление
void Tree::add(int key, QString value)
{
    Node *newNode = new Node(key, value);

    if (root == nullptr)
        root = newNode;
    else
        pushRecursivly(newNode, root);
}

void Tree::add(QVector<std::pair<int, QString>> *arr)
{
    for (std::pair<int, QString> i : *arr)
        add(i.first, i.second);
}

void Tree::pushRecursivly(Node *node, Node *current)
{
    if (node->key < current->key)
    {
        if (current->left == nullptr)
            current->left = node;
        else
            pushRecursivly(node, current->left);
    }
    else if (node->key == current->key)
    {
        current->value = node->value;
        delete node;
    }
    else
    {
        if (current->right == nullptr)
            current->right = node;
        else
            pushRecursivly(node, current->right);
    }
}

// -------------------------------------------------------------------- Удаление
void Tree::remove(int key)
{
    if (root == nullptr)
        return;

    removeRecursivly(key, root, nullptr);
}

void Tree::removeRecursivly(int key, Node *current, Node *parent)
{
    if (key < current->key && current->left != nullptr) //двигаемся влево, пока значение искомого ключа
        removeRecursivly(key, current->left, current); //меньше значения ключа текущего узла

    else if (key == current->key) //нашли узел, который нужно удалить
    {
        Node **branch;
        Node *newNode;

        if (parent == nullptr) //рассматриваемый узел - это корень
            branch = &root;
        else if (parent->left != nullptr && parent->left->key == current->key) //наш узел - это левый сын
            branch = &parent->left;
        else //наш узел - правый сын
            branch = &parent->right;

    //Собственно удаление
        if (current->left != nullptr && current->right != nullptr) //у удаляемого узла две ветки
        {
            Node *tmp = findMostLeft(current->right); //ищем узел с наименьшим ключом из правой ветви удаляемого узла
            newNode = new Node(tmp->key, tmp->value);//дублируем найденный узел
            removeRecursivly(tmp->key, this->root, nullptr); //удаляем его с предыдущего места
            newNode->left = current->left;   //и подставляем на новое место -
            newNode->right = current->right;//вместо  удаляемого узла

        }
        else if (current->left != nullptr || current->right != nullptr) //у удаляемого узла одна ветка
        {
            if (current->left != nullptr) //если эта ветка - левая, то подставим на место удалемого узла ее
                newNode = current->left;
            else
                newNode = current->right; //иначе подставляем правую ветку
        }
        else //удаляемый узел оказался листом
            newNode = nullptr;

        *branch = newNode;
        delete current;
    }
    else if (key > current->key && current->right != nullptr) //двигаемся вправо
        removeRecursivly(key, current->right, current);
}


Node *Tree::findMostLeft(Node *startPos)
{
    if (startPos->left != nullptr)
        return findMostLeft(startPos->left);

    return startPos;
}

// -------------------------------------------------------------------- Поиск по ключу
QString Tree::find(int key)
{
    if (root == nullptr)
        return "";

    return findRecursivly(key, root);
}

QString Tree::findRecursivly(int key, Node *current)
{
    if (key < current->key && current->left != nullptr)
        return findRecursivly(key, current->left);

    else if (key == current->key)
        return current->value;

    else if (current->right != nullptr)
        return findRecursivly(key, current->right);

    return nullptr;
}

// -------------------------------------------------------------------- Балансировка
void Tree::balance()
{
    if (root == nullptr)
        return;

    QVector<std::pair<int, QString>> *sorted = getSorted(); //все узлы дерева в векторе

    dispose(); //удаление старого дерева

    addSorted(sorted, 0, sorted->length() - 1);
}

void Tree::addSorted(QVector<std::pair<int, QString>> *arr, int left, int right)
{
    if (left == right) //случай, когда осталось распределить один элемент
        add((*arr)[left].first, (*arr)[left].second);

    else if (left + 1 == right) //случай, когда осталось распределить только два элемента
    {
        add((*arr)[left].first, (*arr)[left].second);
        add((*arr)[right].first, (*arr)[right].second);
    }
    else
    {
        int m = (left + right) / 2; //находим индекс серединного элемента вектора
        add((*arr)[m].first, (*arr)[m].second); //добавляем этот элемент в дерево
        addSorted(arr, left, m - 1);   //повторяем операцию отдельно для левой
        addSorted(arr, m + 1, right); //и отдельно для правой части
    }
}

// -------------------------------------- Рекурсивное очищение дерева
void Tree::dispose()
{
    if (root == nullptr)
        return;

    disposeRecursivly(root);

    root = nullptr;
}


void Tree::disposeRecursivly(Node *first)
{
    if (first->left != nullptr)
        disposeRecursivly(first->left);

    if (first->right != nullptr)
        disposeRecursivly(first->right);

    delete first;
}

// -------------------------------------------------------------------- Обходим дерево ...
QVector<std::pair<int, QString>> *Tree::getSorted()  //обходим дерево Left-Root-Right
{
    if (root == nullptr)
        return nullptr;

    QVector<std::pair<int, QString>> *out = new QVector<std::pair<int, QString>>();
    dfsSorted(root, out);

    return out;
}

void Tree::dfsSorted(Node *current, QVector<std::pair<int, QString>> *out)
{
    if (current->left != nullptr)
        dfsSorted(current->left, out);

    out->push_back(std::make_pair(current->key, current->value));

    if (current->right != nullptr)
        dfsSorted(current->right, out);
}

QVector<std::pair<int, QString>> *Tree::getForward() //обходим дерево Root-Left-Right
{
    if (root == nullptr)
        return nullptr;

    QVector<std::pair<int, QString>> *out = new QVector<std::pair<int, QString>>();

    dfsForward(root, out);

    return out;
}

void Tree::dfsForward(Node *current, QVector<std::pair<int, QString>> *out)
{
    out->push_back(std::make_pair(current->key, current->value));

    if (current->left != nullptr)
        dfsSorted(current->left, out);

    if(current->right != nullptr)
        dfsSorted(current->right, out);
}

QVector<std::pair<int, QString>> *Tree::getBack()  //обходим дерево Left-Right-Root
{
    if (root == nullptr)
        return nullptr;

    QVector<std::pair<int, QString>> *out = new QVector<std::pair<int, QString>>();

    dfsBack(root, out);

    return out;
}

void Tree::dfsBack(Node *current, QVector<std::pair<int, QString>> *out)
{
    if (current->left != nullptr)
        dfsSorted(current->left, out);

    if (current->right != nullptr)
        dfsSorted(current->right, out);

    out->push_back(std::make_pair(current->key, current->value));
}
