#include "randomqueue.h"
#include <random>
#include <math.h>

RandomQueue::RandomQueue()
{

}

RandomQueue::RandomQueue(int count, int lowerBound, int upperBound)
{
    for( int i = 0; i < count; i++)
        push(lowerBound + rand() % (upperBound - lowerBound));
}

int RandomQueue::getMin()
{
    Node *current = first;

    int min = INT_MAX;

    while (current != nullptr)
    {
        min = std::min(min, current->value);
        current = current->next;
    }
    return min;
}

int RandomQueue::getMax()
{
    Node *current = first;

    int max = INT_MIN;

    while (current != nullptr)
    {
        max = std::max(max, current->value);
        current = current->next;
    }
    return max;
}

void RandomQueue::clearBetweenMinAndMax()
{
    if (isEmpty() || first == last)
        return;

    int min = getMin();
    int max = getMax();

    Node *left = first, *right = last;

    while (left->value != min && left->value != max)
        left = left->next;

    while ((left->value == min && right->value != max) ||
          (left->value == max && right->value != min))
        right = right->prev;

    while (left->next != right)
    {
        Node *middle = left->next;
        left->next = middle->next;
        middle->next->prev = left;
        delete middle;
    }
}
