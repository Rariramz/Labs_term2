#include "rocket.h"

Rocket::Rocket(int x0, int y0)
{
    x = x0;
    y = y0;
}

void Rocket::FireOn()
{
    IsFireOn = true;
}

void Rocket::FireOff()
{
    IsFireOn = false;
}

void Rocket::DrawRocket(QPainter *painter)
{
    QPen rPen(Qt::darkBlue, 4, Qt::SolidLine, Qt::SquareCap);

    //top
    painter->setPen(rPen);
    painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));
    QPolygon top;
    top<<QPoint(x + 150, y - 30)<<QPoint(x + 220, y)<<QPoint(x + 150, y + 30);
    painter->drawPolygon(top);

    //body
    painter->setPen(rPen);
    painter->setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
    QRect body(x, y - 30, 150,60);
    painter->drawRect(body);

    //fire
    if (IsFireOn)
        DrawLine(painter);

    //wings
    painter->setPen(rPen);
    QPolygon wingUp, wingMiddle, wingDown;
    wingUp<<QPoint(x - 20, y - 30)<<QPoint(x + 80, y - 30)<<QPoint(x - 20, y - 70);
    wingMiddle<<QPoint(x - 20, y - 10)<<QPoint(x + 80, y)<<QPoint(x - 20, y + 10);
    wingDown<<QPoint(x - 20, y + 30)<<QPoint(x + 80, y + 30)<<QPoint(x - 20, y + 70);
    painter->setBrush(QBrush(Qt::darkMagenta, Qt::SolidPattern));
    painter->drawPolygon(wingUp);
    painter->drawPolygon(wingMiddle);
    painter->drawPolygon(wingDown);

    //window
    painter->setPen(rPen);
    painter->setPen(QPen(Qt::gray, 5, Qt::SolidLine, Qt::SquareCap));
    painter->drawEllipse(x + 100, y - 20, 40, 40);
    painter->setPen(QPen(Qt::darkBlue, 4, Qt::SolidLine, Qt::SquareCap));
    painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter->drawEllipse(x + 105, y - 15, 30, 30);
}
