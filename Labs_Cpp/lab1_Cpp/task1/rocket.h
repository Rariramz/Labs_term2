#ifndef ROCKET_H
#define ROCKET_H
#include <QPainter>
#include <line.h>

class Rocket: public Line
{
public:
    Rocket(int x0, int y0);

    void DrawRocket(QPainter *painter);

    void FireOn();

    void FireOff();

private:
    bool IsFireOn = false;
};
#endif // ROCKET_H
