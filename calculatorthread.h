#ifndef CALCULATORTHREAD_H
#define CALCULATORTHREAD_H
#include "calculator.h"

class CalculatorThread : public QThread
{
    Q_OBJECT
public:
    CalculatorThread(QList<MyBubble *> *l,QMutex* m,int updateInterval, QObject *parent=0);
 protected:
    virtual void run();
    QTimer* timer;
    Calculator* calculator;
    int interval;

};

#endif // CALCULATORTHREAD_H
