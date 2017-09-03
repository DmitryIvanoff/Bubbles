#include "calculator.h"

Calculator::Calculator(QList<MyBubble *> *l, QObject *parent): QObject(parent),time()
{
    ItemsList=l;
    time.start();
}

Calculator::~Calculator()
{

}

void Calculator::calculate()
{
    double deltaTime=(qreal)time.elapsed()/(qreal)(1000);
    time.restart();
    double x;
    double y;
    double v_x;
    double v_y;
    double rx;
    double ry;
    double r;
    double F;
    double F_x;
    double F_y;
    std::list<QPointF> v;
    std::list<MyBubble*> items=ItemsList->toStdList();
    std::list<MyBubble*>::iterator it=items.begin();
    std::list<MyBubble*>::iterator it_2;
    for (;it!=items.end();++it)
    {
        it_2=items.begin();
        QPointF v1=(*it)->getV();
        QPointF p1=(*it)->getPosition();
        v_x=v1.x();
        v_y=v1.y();
        x=p1.x();
        y=p1.y();
        while (it_2!=items.end())
        {
            if (it!=it_2)
            {
                QPointF v2=(*it_2)->getV();
                QPointF p2=(*it_2)->getPosition();
                rx=p2.x()-x;
                ry=p2.y()-y;
                r=sqrt(rx*rx+ry*ry);
                if (r>(*it)->getDiameter())
                {
                    F=fabs(1.0/r-1.0/(r*r));
                    F_x=F*rx/r;
                    F_y=F*ry/r;
                    v_x+=F_x*deltaTime;
                    v_y+=F_y*deltaTime;
                }
                else
                {
                    //v_x+=v2.x();
                    //v_y+=v2.y();
                }
            }
            ++it_2;
        }
        v.push_back(QPointF(v_x,v_y));
       //(*it)->setV(QPointF(v_x,v_y));
    }
    it=items.begin();
    std::list<QPointF>::iterator it_v=v.begin();
    for (;it!=items.end();++it)
    {
        QPointF v=*it_v;
        QPointF p=(*it)->getPosition();
        (*it)->setV(v);
        (*it)->setPosition(QPointF(p.x()+v.x()*deltaTime,p.y()+v.y()*deltaTime));
        ++it_v;
    }

}


