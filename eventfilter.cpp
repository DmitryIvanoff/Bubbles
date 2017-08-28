#include "eventfilter.h"

EventFilter::EventFilter(QList<MyBubble*>* l,QObject *parent):QObject(parent)
{
  items=l;
}

bool EventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type()==QEvent::MouseButtonPress)
    {
        if (dynamic_cast<QMouseEvent*>(event)->button()==Qt::LeftButton)
        {
            QGraphicsView* view=dynamic_cast<QGraphicsView*>(watched);
            if (view)
            {
               if (!items->empty())
               {
                   QGraphicsScene* scene=view->scene();
                   MyBubble* b=new MyBubble(*(items->at(0)));
                   b->setPos(view->mapToScene(dynamic_cast<QMouseEvent*>(event)->pos()));
                   scene->addItem((QGraphicsItem*)b);
                   items->append(b);
               }
            }
        }
    }

    return false;
}

EventFilter::~EventFilter()
{

}
