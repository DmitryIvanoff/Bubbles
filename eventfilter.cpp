#include "eventfilter.h"

EventFilter::EventFilter(QList<MyBubble*>* l,QObject *parent):QObject(parent)
{
  items=l;
}

bool EventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type()==QEvent::GraphicsSceneMousePress)
    {
        QGraphicsScene* scene=dynamic_cast<QGraphicsScene*>(watched);
        if (dynamic_cast<QGraphicsSceneMouseEvent*>(event)->button()==Qt::LeftButton)
        {
            if (scene)
            {
               if (!items->empty())
               {
                   MyBubble* b=new MyBubble(*(items->at(0)));
                   scene->addItem((QGraphicsItem*)b);
                   b->setPosition(dynamic_cast<QGraphicsSceneMouseEvent*>(event)->scenePos());
                   items->append(b);
               }
            }
        }
        if (dynamic_cast<QGraphicsSceneMouseEvent*>(event)->button()==Qt::RightButton)
        {
            if (scene)
            {
                QGraphicsView* view=NULL;
                if  (!scene->views().isEmpty())
                {
                    view=scene->views().last();
                }
                   QGraphicsItem* item=scene->itemAt(dynamic_cast<QGraphicsSceneMouseEvent*>(event)->scenePos(),view->transform());
                   if (item)
                   {
                       MyBubble* b=dynamic_cast<MyBubble*>(item);
                       //b->setPosition(dynamic_cast<QGraphicsSceneMouseEvent*>(event)->scenePos());
                       scene->removeItem(item);
                       items->removeAll(b);
                       delete b;
                   }
            }
        }
    }

    return false;
}

EventFilter::~EventFilter()
{

}
