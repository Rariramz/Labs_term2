#ifndef LINE_H
#define LINE_H
#include <QPainter>

class Line
{
public:
    Line();

    void Move();
protected:
    int x, y;

    void DrawLine(QPainter *painter);
};

#endif // LINE_H
