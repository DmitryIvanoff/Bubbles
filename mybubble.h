#ifndef MYBUBBLE_H
#define MYBUBBLE_H
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QtCore>
#include <QtGui>
class MyBubble : public QGraphicsObject
{

public:
    MyBubble();
    MyBubble(qreal);
    virtual ~MyBubble();
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
    void advance(int phase);

private:
    qreal diameter;
    qreal v_x;
    qreal v_y;
    qreal v_z;

};

#endif // MYBUBBLE_H
