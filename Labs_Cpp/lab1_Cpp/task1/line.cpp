#include "line.h"

Line::Line()
{

}

void Line::DrawLine(QPainter *painter)
{
    int randLen = qrand() % (((x - 10) + 1) - (x - 330)) + (x - 330); //мин. длина отрезка 10, макс. 130
    int randY = qrand() % (((y + 29) + 1) - (y - 29)) + (y - 29);

    if (qrand() % 2 == 1)
        painter->setPen(QPen(Qt::magenta, 3, Qt::SolidLine, Qt::FlatCap));
    else
        painter->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::FlatCap));

    painter->drawLine(x, randY, randLen, randY);
}

void Line::Move()
{
   if (x < 1220) x += 2;
   else x = -220;
}
