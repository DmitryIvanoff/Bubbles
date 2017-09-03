#include "calculatorthread.h"

CalculatorThread::CalculatorThread(QList<MyBubble *> *l, int updateInterval, QObject *parent):QThread(parent)
{
   timer=new QTimer();
   interval=updateInterval;
   calculator=new Calculator(l);
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
