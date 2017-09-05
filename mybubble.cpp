#include "mybubble.h"

MyBubble::MyBubble(qreal d):QGraphicsObject(),V_mutex(),Pos_mutex(),d_mutex()
{
    diameter=d;
    velocity.setX(0);
    velocity.setY(0);
    setPos(QPoint(qrand()%400,qrand()%400));
    position=pos();
    anim=new QPropertyAnimation(this,"pos");
    anim->setEasingCurve(QEasingCurve::Linear);
}

MyBubble::MyBubble(qreal d, qreal x, qreal y):QGraphicsObject(),V_mutex(),Pos_mutex(),d_mutex()
{
    diameter=d;
    velocity.setX(0);
    velocity.setY(0);
    setPos(QPoint(x,y));
    position=pos();
    anim=new QPropertyAnimation(this,"pos");
    anim->setEasingCurve(QEasingCurve::Linear);
}

MyBubble::MyBubble(qreal d, QPointF v, QPointF p):QGraphicsObject(),V_mutex(),Pos_mutex(),d_mutex()
{
    diameter=d;
    velocity=v;
    setPos(p);
    position=pos();
    anim=new QPropertyAnimation(this,"pos");
    anim->setEasingCurve(QEasingCurve::Linear);
}

MyBubble::MyBubble(const MyBubble &bubble):QGraphicsObject(),V_mutex(),Pos_mutex(),d_mutex()
{
    diameter=bubble.diameter;
    velocity.setX(0);
    velocity.setY(0);
    setPos(QPointF(0.0,0.0));
    position=pos();
    anim=new QPropertyAnimation(this,"pos");
    setFrameDuration(bubble.getFrameDuration());
    anim->setEasingCurve(QEasingCurve::Linear);
}

MyBubble::~MyBubble()
{
    delete anim;
}


QRectF MyBubble::boundingRect() const
{
    return QRectF(-diameter/2,-diameter/2,diameter,diameter);
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
//        painter->setPen(Qt::green);
//        painter->drawRect(boundingRect());
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
//        anim->start();
           setPos(getPosition());
    }
    else
    {
        anim->setEndValue(getPosition());
    }


}

QPointF MyBubble::getV()
{
    V_mutex.lockForRead();
    QPointF value;
    value=velocity;
    V_mutex.unlock();
    return value;
}

void MyBubble::setV(const QPointF &value)
{
     V_mutex.lockForWrite();
     velocity=value;
     V_mutex.unlock();
}

QPointF MyBubble::getPosition()
{
    Pos_mutex.lockForRead();
    QPointF value;
    value=position;
    Pos_mutex.unlock();
    return value;
}


void MyBubble::setPosition(const QPointF &value)
{
    Pos_mutex.lockForWrite();
    position=value;
    Pos_mutex.unlock();
}


qreal MyBubble::getDiameter()
{
    d_mutex.lockForRead();
    qreal value;
    value=diameter;
    d_mutex.unlock();
    return value;
}

void MyBubble::setDiameter(const qreal &value)
{
    d_mutex.lockForWrite();
    diameter = value;
    d_mutex.unlock();
}

int MyBubble::getFrameDuration() const
{
    return FrameDuration;
}

void MyBubble::setFrameDuration(int msecs)
{

        FrameDuration=msecs;
        anim->setDuration(msecs);

}

void MyBubble::updatePosition(int frame)
{
    setPos(getPosition());
}




