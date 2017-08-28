#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include "mybubble.h"
class EventFilter : public QObject
{
    Q_OBJECT
public:
    EventFilter(QList<MyBubble*>* list,QObject *parent = 0);
    bool eventFilter(QObject *watched, QEvent *event);
    ~EventFilter();
signals:

public slots:
private:
    QList<MyBubble*>* items;
};

#endif // EVENTFILTER_H
