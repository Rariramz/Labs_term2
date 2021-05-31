#include "list.h"

List::List()
{
    first = nullptr;
    last = nullptr;
}

bool List::isEmpty()
{
    return first == nullptr;
}

int List::getLength()
{
    int i = 0;
    Node *current = first;
    while (current != nullptr)
    {
        i++;
        current = current->next;
    }
    return i;
}

void List::pushBack(QString surname, QString name, QString patronim,
                    bool missedExam, bool thisUniversity, int *marks)
{
    Node *node = new Node(surname, name, patronim, missedExam, thisUniversity, marks);

    if(first == nullptr)
    {
        first = node;
        last = node;
    }
    else
    {
        last->next = node;
        node->prev = last;
        last = node;
    }
}

int List::remove() //удалить всех, кто не был на экзамене
{
    int numberOfDeleted = 0;

    Node *current = first, *temp = nullptr;
    while(current != nullptr)
    {
        if (current->missedExam)
        {
            numberOfDeleted++;

            if (first == current && last == current)
            {
                first = nullptr;
                last = nullptr;
            }
            else if (first == current)
            {
                first = current->next;
                first->prev = nullptr;
            }
            else if (last == current)
            {
                last = current->prev;
                last->next = nullptr;
            }
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            temp = current;
            current = current->next;
            delete temp;
            continue;
        }
        current = current->next;
    }

    return numberOfDeleted;
}

int List::findBySurname(QString surname, int **numbers)
{
    int index = 0;
    int lenth = 0;

    Node *current = first;
    while (current != nullptr)
    {
        if (current->surname == surname)
            (*numbers)[lenth++] = index;

        current = current->next;
        index++;
    }

    return lenth;
}

QString List::toString(QString format, int index)
{
    QString output = "";
    int i = 0;

    Node *current = first;

    if (first == nullptr)
        return "Список пуст :(";

    if (format == "All")
    {
        while (current != nullptr)
        {
            output += "Студент №" + QString::number(++i) + "\n" +
                                 "Фамилия: " + current->surname + "\n" +
                                 "Имя: " + current->name + "\n" +
                                 "Отчество: " + current->patronim + "\n" +
                                 "Оценки" + (current->marks == nullptr ? ": отсутствуют" : "(3):");
            if (current->marks != nullptr)
                for (int k = 0; k < 3; k++)
                    output += " " + QString::number(current->marks[k]);
            output += "\n\n";

        current = current->next;
        }
    }
    else
    {
        while (i < index)
        {
            i++;
            current = current->next;
        }

        output += "Студент №" + QString::number(++i) + "\n" +
                             "Фамилия: " + current->surname + "\n" +
                             "Имя: " + current->name + "\n" +
                             "Отчество: " + current->patronim + "\n" +
                             "Оценки" + (current->marks == nullptr ? ": отсутствуют" : "(3):");
        if (current->marks != nullptr)
            for (int k = 0; k < 3; k++)
                output += " " + QString::number(current->marks[k]);
        output += "\n\n";
    }

    return output;
}

double List::getAveragePointByUniversity() //считает средний балл по университету
{
    Node *current = first;

    int i = 0;
    double sum = 0;
    while (current != nullptr)
    {
        if (current->thisUniversity)
        {
            i++;
            sum += current->averagePoint;
        }
        current = current->next;
    }

    return (sum / i);
}

int List::findByHighestAveragePoint(double averagePointByUniversity, int **numbers)
{
    int index = 0;
    int length = 0;

    Node *current = first;
    while (current != nullptr)
    {
        if (current->averagePoint >= averagePointByUniversity)
            (*numbers)[length++] = index;

        current = current->next;
        index++;
    }

    return length;
}

