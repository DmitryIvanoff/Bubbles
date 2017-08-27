#ifndef MYBUBBLE_H
#define MYBUBBLE_H
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QtCore>
#include <QtGui>
class MyBubble : public QGraphicsObject
{
     Q_OBJECT
     Q_PROPERTY(QPointF position READ getPosition WRITE setPosition)
public:
    MyBubble();
    MyBubble(qreal);
    virtual ~MyBubble();
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
    void advance(int phase);

    QPointF getV();
    void setV(const QPointF &value);
    QPointF getPosition();
    void setPosition(const QPointF &value);



    qreal getDiameter() const;
    void setDiameter(const qreal &value);

private:
    QPropertyAnimation* anim;
    QMutex mutex;
    qreal diameter;
    QPointF v;

};

#endif // MYBUBBLE_H
