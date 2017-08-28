#include "calculator.h"

Calculator::Calculator(QList<MyBubble *> *l, QObject *parent): QObject(parent)
{
    ItemsList=l;
}

Calculator::~Calculator()
{

}

void Calculator::calculate()
{
    double v_x;
    double v_y;
    double rx;
    double ry;
    double r;
    double F;
    double F_x;
    double F_y;
    std::list<MyBubble*> items=ItemsList->toStdList();
    std::list<MyBubble*>::iterator it=items.begin();
    std::list<MyBubble*>::iterator it_2;
    for (;it!=items.end();++it)
    {
        it_2=items.begin();
        v_x=(*it)->getV().x();
        v_y=(*it)->getV().y();
        while (it_2!=items.end())
        {
            rx=(*it_2)->getPosition().x()-(*it)->getPosition().x();
            ry=(*it_2)->getPosition().y()-(*it)->getPosition().y();
            r=sqrt(rx*rx+ry*ry);
            if (r>(*it)->getDiameter())
            {
                F=fabs(1/r-1/(r*r));
                F_x=F*rx/r;
                F_y=F*ry/r;
                v_x+=F_x;
                v_y+=F_y;
            }
            else
            {
                v_x+=0.0;
                v_y+=0.0;
            }
            ++it_2;
        }
        (*it)->setV(QPointF(v_x,v_y));


    }
    QThread::msleep(4);
}


