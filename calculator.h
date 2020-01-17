#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "mybubble.h"
#include <QObject>

using BubbleList=std::list<MyBubble*>;

class Calculator : public QObject
{
    Q_OBJECT
public:
     Calculator(BubbleList* l,QMutex* m);
    ~Calculator();


private:
  BubbleList* items;
  QTime time;
  QMutex* mutex;
public slots:
  void calculate();
};

#endif // CALCULATOR_H
