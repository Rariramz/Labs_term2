#ifndef RANDOMQUEUE_H
#define RANDOMQUEUE_H
#include "queue.h"

class RandomQueue : public Queue
{
public:
    RandomQueue();
    RandomQueue(int count, int lowerBound, int upperBound);

    void clearBetweenMinAndMax();

private:
    int getMin();
    int getMax();
};

#endif // RANDOMQUEUE_H
