#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "mybubble.h"
#include <QObject>

class Calculator : public QObject
{
    Q_OBJECT
public:
     Calculator(QList<MyBubble*>* l,QObject* parent =0);
    ~Calculator();


private:
  QList<MyBubble*>* ItemsList;
public slots:
  void calculate();
};

#endif // CALCULATOR_H
