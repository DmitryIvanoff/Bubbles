#include "mybubble.h"

MyBubble::MyBubble(qreal d):QGraphicsObject(),
                                         diameter(d),
                                         velocity(0,0)
{
    setPos(QPoint(qrand()%400,qrand()%400));
    anim=new QPropertyAnimation(this,"pos");
    anim->setEasingCurve(QEasingCurve::Linear);
    position=pos();
}

MyBubble::MyBubble(qreal d, qreal x, qreal y):QGraphicsObject(),
                                              diameter(d),
                                              velocity(0,0)
{
    setPos(QPointF(x,y));
    anim=new QPropertyAnimation(this,"pos");
    anim->setEasingCurve(QEasingCurve::Linear);
    position=pos();
}

MyBubble::MyBubble(qreal d, QPointF v, QPointF p):QGraphicsObject(),
                                                  diameter(d),
                                                  velocity(v)
{
    setPos(p);
    anim=new QPropertyAnimation(this,"pos");
    anim->setEasingCurve(QEasingCurve::Linear);
    position=pos();
}

MyBubble::MyBubble(const MyBubble &bubble):QGraphicsObject(),
                                           diameter(bubble.diameter),
                                           velocity(0,0)
{
    setPos(bubble.pos());
    position=pos();
    anim=new QPropertyAnimation(this,"pos");
    anim->setEasingCurve(QEasingCurve::Linear);
}

MyBubble::~MyBubble()
{
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
        //setPos(position);
        anim->start();
    }
    else
    {
        if (anim->state() == QPropertyAnimation::Running)
        {
            anim->setCurrentTime(anim->totalDuration());
        }
        if (anim->state() ==QPropertyAnimation::Stopped)
        {
            anim->setEndValue(position);
            anim->setDuration();
        }
    }
}


QPointF MyBubble::getV()
{
    return velocity;
}

void MyBubble::setV(const QPointF &value)
{
     velocity=value;
}

qreal MyBubble::getDiameter()
{
    return diameter;
}

void MyBubble::setDiameter(const qreal &value)
{
    diameter = value;
}

QPointF MyBubble::getPosition() const
{
    return position;
}

void MyBubble::setPosition(const QPointF &value)
{



    position = value;
}

int MyBubble::getFrameDuration() const
{
    return anim->duration();
}

void MyBubble::setFrameDuration(int value)
{
    anim->setDuration(value);
}





