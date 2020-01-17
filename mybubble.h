#ifndef MYBUBBLE_H
#define MYBUBBLE_H
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneEvent>
#include <QtCore>
#include <QtGui>
class MyBubble : public QGraphicsObject
{
     Q_OBJECT
public:
    MyBubble(qreal);
    MyBubble(qreal,qreal,qreal);
    MyBubble(qreal,QPointF velocity,QPointF position);
    MyBubble(const MyBubble&);
    virtual ~MyBubble();
     QRectF boundingRect() const override;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
    void advance(int) override;
    QPointF getV();
    void setV(const QPointF &value);

    qreal getDiameter();
    void setDiameter(const qreal &value);

    QPointF getPosition() const;
    void setPosition(const QPointF &value);

    int getFrameDuration() const;
    void setFrameDuration(int value);

private:
    QPropertyAnimation* anim;
    qreal diameter;
    QPointF position;
    QPointF velocity;

};

#endif // MYBUBBLE_H
