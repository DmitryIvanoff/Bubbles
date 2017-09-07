#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    items_mutex()
{
    ui->setupUi(this);
    amount=200;
    double sceneWidth=400;
    double sceneHeight=400;
    int updPeriod=16;
    scene=new QGraphicsScene(0,0,sceneWidth,sceneHeight,this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//    scene->addLine(scene->sceneRect().left(),scene->sceneRect().top(),scene->sceneRect().right(),scene->sceneRect().top(),QPen(Qt::red));
//    scene->addLine(scene->sceneRect().left(),scene->sceneRect().top(),scene->sceneRect().left(),scene->sceneRect().bottom(),QPen(Qt::red));
//    scene->addLine(scene->sceneRect().left(),scene->sceneRect().bottom(),scene->sceneRect().right(),scene->sceneRect().bottom(),QPen(Qt::red));
//    scene->addLine(scene->sceneRect().right(),scene->sceneRect().top(),scene->sceneRect().right(),scene->sceneRect().bottom(),QPen(Qt::red));
    ui->graphicsView->setScene(scene);
    QGridLayout* l=new QGridLayout;
    l->addWidget(ui->graphicsView);
    ui->centralWidget->setLayout(l);
    setWindowTitle("Bubbles");
    setMinimumSize(QSize(sceneWidth+100,sceneHeight+100));
    CoordinateLabel=new QLabel(this);
    BubblesAmountLabel=new QLabel(this);
    scene->installEventFilter(this);
    ui->graphicsView->setMouseTracking(true);
    ui->statusBar->addWidget(BubblesAmountLabel);
    ui->statusBar->addWidget(CoordinateLabel);
    BubblesAmountLabel->setText("amount: "+QString::number(amount));
    for (int i=0;i<amount;++i)
    {
        MyBubble* item= new MyBubble(10);
        item->setFrameDuration(updPeriod);
        scene->addItem((QGraphicsItem*)item);
        items.append(item);
    }
    timer=new QTimer(this);
    CThread=new CalculatorThread(&items,&items_mutex,updPeriod,this);
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    QThread::currentThread()->setPriority(QThread::NormalPriority);
    timer->start(updPeriod);
    CThread->start(QThread::NormalPriority);
}

MainWindow::~MainWindow()
{
    //    QMutableListIterator<MyBubble*> it(list);
    //    while (it.hasNext())
    //    {
    //        MyBubble* item=it.next();
    //        scene->removeItem(item);
    //        delete item;
    //    }
    CThread->quit();
    CThread->wait();
    foreach (MyBubble* obj,items)
    {
        scene->removeItem(obj);
        delete obj;
    }
    items.clear();
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    QGraphicsScene* view=dynamic_cast<QGraphicsScene*>(watched);
    if (view)
    {
        if (event->type()==QEvent::GraphicsSceneMouseMove)
        {
            QGraphicsSceneMouseEvent* e=dynamic_cast<QGraphicsSceneMouseEvent*>(event);
            CoordinateLabel->setText(QString("x: %1;y: %2").arg(e->scenePos().x()).arg(e->scenePos().y()));
        }
    }
    if (event->type()==QEvent::GraphicsSceneMousePress)
    {
        QGraphicsScene* scene=dynamic_cast<QGraphicsScene*>(watched);
        if (dynamic_cast<QGraphicsSceneMouseEvent*>(event)->button()==Qt::LeftButton)
        {
            if (scene)
            {
               items_mutex.lock();
               qDebug()<<"mutex is locked by "<<::currentThreadId();
               if (!items.empty())
               {
                   MyBubble* b=new MyBubble(*(items.at(0)));
                   scene->addItem((QGraphicsItem*)b);
                   BubblesAmountLabel->setText("amount: "+QString::number(++amount));
                   b->setPos(dynamic_cast<QGraphicsSceneMouseEvent*>(event)->scenePos());
                   b->setPosition(b->pos());
                   items.append(b);
               }
               items_mutex.unlock();
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
                    BubblesAmountLabel->setText("amount: "+QString::number(--amount));
                    scene->removeItem(item);
                    items_mutex.lock();
                    qDebug()<<"mutex is locked by "<<QThread::currentThreadId();
                    items.removeAll(b);
                    items_mutex.unlock();
                    delete b;
                }
            }
        }
    }

    return false;
}

void MainWindow::advance()
{

}












