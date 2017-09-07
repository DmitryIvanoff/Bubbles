#include "calculatorthread.h"

CalculatorThread::CalculatorThread(QList<MyBubble *> *l,QMutex* m, int updateInterval, QObject *parent):QThread(parent)
{
   timer=new QTimer();
   interval=updateInterval;
   calculator=new Calculator(l,m);
   timer->moveToThread(this);
   calculator->moveToThread(this);
   connect(timer,SIGNAL(timeout()),calculator,SLOT(calculate()));
   connect(this,SIGNAL(finished()),timer,SLOT(deleteLater()));
   connect(this,SIGNAL(finished()),calculator,SLOT(deleteLater()));
}

void CalculatorThread::run()
{
    timer->start(interval);


    exec();
}
