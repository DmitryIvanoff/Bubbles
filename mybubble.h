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
    MyBubble(qreal,QPointF,QPointF);
    MyBubble(const MyBubble&);
    virtual ~MyBubble();
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
    void advance(int phase);

    QPointF getV();
    void setV(const QPointF &value);
    QPointF getPosition();
    void setPosition(const QPointF &value);



    qreal getDiameter();
    void setDiameter(const qreal &value);

    int getFrameDuration() const;
    QPropertyAnimation* anim;
private:
    //QPropertyAnimation* anim;
    int FrameDuration;
    QReadWriteLock V_mutex;
    QReadWriteLock Pos_mutex;
    QReadWriteLock d_mutex;
    QPointF position;
    qreal diameter;
    QPointF velocity;
public slots:
    void setFrameDuration(int);

};

#endif // MYBUBBLE_H
