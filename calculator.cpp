#include "calculator.h"

Calculator::Calculator(BubbleList* l,QMutex* m): QObject(nullptr),time()
{
    items=l;
    mutex=m;
    time.start();
}

Calculator::~Calculator()
{

}

void Calculator::calculate()
{

    double x,y,v_x,v_y;
    double rx,ry,r;
    double F,F_x,F_y;
    mutex->lock();
    double deltaTime=(double)time.elapsed()/(double)(100);
    time.restart();
    //qDebug()<<"mutex is locked by "<<QThread::currentThreadId();
    for (BubbleList::iterator it=items->begin();it!=items->end();++it)
    {
        QPointF v1=(*it)->getV();
        QPointF p1=(*it)->getPosition();
        v_x=v1.x();
        v_y=v1.y();
        x=p1.x();
        y=p1.y();
        for (BubbleList::const_iterator it_2=items->cbegin();it_2!=items->cend();++it_2)
        {
            if (it!=it_2)
            {
                QPointF p2=(*it_2)->getPosition();
                rx=p2.x()-x;
                ry=p2.y()-y;
                r=sqrt(rx*rx+ry*ry);
                if (r>(*it)->getDiameter())
                {
                    F=fabs(1.0/r-1.0/(r*r));
                    F_x=F*(rx/r);
                    F_y=F*(ry/r);
                    v_x+=F_x*deltaTime;
                    v_y+=F_y*deltaTime;
                }
                else
                {
                    //v_x+=v2.x();
                    //v_y+=v2.y();
                }
            }
        }
       (*it)->setV(QPointF(v_x,v_y));
       QPointF pEnd=QPointF(p1.x()+v_x*deltaTime,p1.y()+v_y*deltaTime);
       (*it)->setPosition(pEnd);
    }
    mutex->unlock();
}


