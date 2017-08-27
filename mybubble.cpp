#include "mybubble.h"

MyBubble::MyBubble(qreal d):QGraphicsObject(),mutex()
{
    diameter=d;
    v.setX(0);
    v.setY(0);
    setPos(QPoint(qrand()%200,qrand()%200));
    anim=new QPropertyAnimation(this,"position");
    anim->setDuration(100);
    //setFlags(QGraphicsObject::ItemIsMovable);
}

MyBubble::~MyBubble()
{
   delete anim;
}

MyBubble::MyBubble():QGraphicsObject()
{
    diameter=5;
    v.setX(10*(double)qrand()/(double)RAND_MAX);
    v.setY(10*(double)qrand()/(double)RAND_MAX);
    //setPos(mapToParent(QPoint(qrand()%100,qrand()%100)));
}

QRectF MyBubble::boundingRect() const
{
    return QRectF(x(),y(),diameter,diameter);
}

void MyBubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
//    if (collidingItems().isEmpty())
//    {
//        painter->setPen(Qt::blue);
//    }
//    else
//    {
//        painter->setPen(Qt::red);
//    }
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

        anim->setStartValue(getPosition());
        anim->setEndValue(QPointF(getPosition().x()+getV().x(),getPosition().y()+getV().y()));
        anim->start();


        //setPos(QPointF(pos().x()+v_x,pos().y()+v_y));
    }

}

QPointF MyBubble::getV()
{
    mutex.lock();
    QPointF value;
    value=v;
    mutex.unlock();
    return value;
}

void MyBubble::setV(const QPointF &value)
{
     mutex.lock();
     v=value;
     mutex.unlock();
}

QPointF MyBubble::getPosition()
{
    mutex.lock();
    QPointF value;
    value=pos();
    mutex.unlock();
    return value;
}


void MyBubble::setPosition(const QPointF &value)
{
    mutex.lock();
    setPos(value);
    mutex.unlock();
}

qreal MyBubble::getDiameter() const
{
    return diameter;
}

void MyBubble::setDiameter(const qreal &value)
{
    diameter = value;
}




