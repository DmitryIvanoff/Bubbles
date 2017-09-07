#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "mybubble.h"
#include <QObject>

class Calculator : public QObject
{
    Q_OBJECT
public:
     Calculator(QList<MyBubble*>* l,QMutex* m, QObject* parent =0);
    ~Calculator();


private:
  QList<MyBubble*>* ItemsList;
  QTime time;
  QMutex* mutex;
public slots:
  void calculate();
};

#endif // CALCULATOR_H
