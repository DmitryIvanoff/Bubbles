#include "mybubble.h"

MyBubble::MyBubble(qreal d):QGraphicsObject()
{
    diameter=d;
    v_x=(double)qrand()/(double)RAND_MAX;
    v_y=(double)qrand()/(double)RAND_MAX;
    v_z=0.0;
    setPos(QPoint(qrand()%200,qrand()%200));
    //setFlags(QGraphicsObject::ItemIsMovable);
}

MyBubble::~MyBubble()
{

}

MyBubble::MyBubble():QGraphicsObject()
{
    diameter=5;
    v_x=1.0;
    v_y=1.0;
    v_z=0.0;
    //setPos(mapToParent(QPoint(qrand()%100,qrand()%100)));
}

QRectF MyBubble::boundingRect() const
{
    return QRectF(x(),y(),diameter,diameter);
}

void MyBubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    if (collidingItems().isEmpty())
    {
        painter->setPen(Qt::blue);
    }
    else
    {
         painter->setPen(Qt::red);
    }
    painter->drawEllipse(boundingRect());
//    painter->setPen(Qt::green);
//    painter->drawRect(boundingRect());
}

QPainterPath MyBubble::shape() const
{
   QPainterPath path;
   path.addEllipse(boundingRect());
   return path;
}

void MyBubble::advance(int phase)
{
    if (phase)
    {
    QPropertyAnimation *anim=new QPropertyAnimation(this,"pos");
    anim->setDuration(1000);
    anim->setStartValue(pos());
    anim->setEndValue(QPointF(pos().x()+v_x,pos().y()+v_y));
    anim->start();
    }
}
