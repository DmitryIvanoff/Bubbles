#include "mybubble.h"

MyBubble::MyBubble(qreal d):QGraphicsObject(),V_mutex(),Pos_mutex(),d_mutex()
{
    diameter=d;
    velocity.setX(0);
    velocity.setY(0);
    setPos(QPoint(qrand()%200,qrand()%200));
    anim=new QPropertyAnimation(this,"position");
    anim->setDuration(10);
}

MyBubble::MyBubble(qreal d, qreal x, qreal y):QGraphicsObject(),V_mutex(),Pos_mutex(),d_mutex()
{
    diameter=d;
    velocity.setX(0);
    velocity.setY(0);
    setPos(QPoint(x,y));
    anim=new QPropertyAnimation(this,"position");
    anim->setDuration(10);
}

MyBubble::MyBubble(qreal d, QPointF v, QPointF p):QGraphicsObject(),V_mutex(),Pos_mutex(),d_mutex()
{
    diameter=d;
    velocity=v;
    setPos(p);
    anim=new QPropertyAnimation(this,"position");
    anim->setDuration(10);
}

MyBubble::MyBubble(const MyBubble &bubble)
{
    diameter=bubble.diameter;
    velocity.setX(0);
    velocity.setY(0);
    setPos(QPointF(0.0,0.0));
    anim=new QPropertyAnimation(this,"position");
    anim->setDuration(bubble.anim->duration());
}

MyBubble::~MyBubble()
{
   delete anim;
}


QRectF MyBubble::boundingRect() const
{
    return QRectF(x(),y(),diameter,diameter);
}

void MyBubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setRenderHint(QPainter::Antialiasing);
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
        QPointF v=getV();
        QPointF p=getPosition();
        anim->setStartValue(p);
        anim->setEndValue(QPointF(p.x()+v.x(),p.y()+v.y()));
        anim->start();
    }

}

QPointF MyBubble::getV()
{
    V_mutex.lock();
    QPointF value;
    value=velocity;
    V_mutex.unlock();
    return value;
}

void MyBubble::setV(const QPointF &value)
{
     V_mutex.lock();
     velocity=value;
     V_mutex.unlock();
}

QPointF MyBubble::getPosition()
{
    Pos_mutex.lock();
    QPointF value;
    value=pos();
    Pos_mutex.unlock();
    return value;
}


void MyBubble::setPosition(const QPointF &value)
{
    Pos_mutex.lock();
    setPos(value);
    Pos_mutex.unlock();
}

qreal MyBubble::getDiameter()
{
    d_mutex.lock();
    qreal value;
    value=diameter;
    d_mutex.unlock();
    return value;
}

void MyBubble::setDiameter(const qreal &value)
{
    d_mutex.lock();
    diameter = value;
    d_mutex.unlock();
}

int MyBubble::getFrameDuration() const
{
    return anim->duration();
}

void MyBubble::setFrameDuration(int msecs)
{
    if (anim)
    {
        anim->setDuration(msecs);
    }
}




