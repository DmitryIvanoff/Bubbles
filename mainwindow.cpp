#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    amount=1000;
    double sceneWidth=400;
    double sceneHeight=400;
    int updPeriod=33;
    scene=new QGraphicsScene(0,0,sceneWidth,sceneHeight,this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->addLine(scene->sceneRect().left(),scene->sceneRect().top(),scene->sceneRect().right(),scene->sceneRect().top(),QPen(Qt::red));
    scene->addLine(scene->sceneRect().left(),scene->sceneRect().top(),scene->sceneRect().left(),scene->sceneRect().bottom(),QPen(Qt::red));
    scene->addLine(scene->sceneRect().left(),scene->sceneRect().bottom(),scene->sceneRect().right(),scene->sceneRect().bottom(),QPen(Qt::red));
    scene->addLine(scene->sceneRect().right(),scene->sceneRect().top(),scene->sceneRect().right(),scene->sceneRect().bottom(),QPen(Qt::red));
    ui->graphicsView->setScene(scene);
    QGridLayout* l=new QGridLayout;
    l->addWidget(ui->graphicsView);
    ui->centralWidget->setLayout(l);
    setWindowTitle("Bubbles");
    //setMinimumSize(QSize(sceneWidth+100,sceneHeight+100));
    CoordinateLabel=new QLabel(this);
    BubblesAmountLabel=new QLabel(this);
    scene->installEventFilter(this);
    ui->graphicsView->setMouseTracking(true);
    ui->statusBar->addWidget(BubblesAmountLabel);
    ui->statusBar->addWidget(CoordinateLabel);
    BubblesAmountLabel->setText("amount: "+QString::number(amount));
    group=new QParallelAnimationGroup(this);
    for (int i=0;i<amount;++i)
    {
        MyBubble* item= new MyBubble(10);
        item->setFrameDuration(updPeriod);
        scene->addItem((QGraphicsItem*)item);
        group->addAnimation(item->anim);
        items.append(item);
    }
    // calculator=new Calculator(&items);

    thread=new QThread(this);
    //calculator->moveToThread(thread);
    timer=new QTimer(this);
    CThread=new CalculatorThread(&items,33,this);
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    // connect(timer,SIGNAL(timeout()),group,SLOT(start()));
    //   connect(timer1,SIGNAL(timeout()),this,SLOT(advance()));
    //    connect(thread, SIGNAL(finished()),calculator,SLOT(deleteLater()));
    //    connect(timer1,SIGNAL(timeout()),calculator,SLOT(calculate()));
    //thread->start(QThread::NormalPriority);
    QThread::currentThread()->setPriority(QThread::NormalPriority);

    timer->start(updPeriod);
    CThread->start(QThread::NormalPriority);
    //    timer2->start(updPeriod*10);





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
//    thread->quit();
//    thread->wait();
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
               if (!items.empty())
               {
                   MyBubble* b=new MyBubble(*(items.at(0)));
                   scene->addItem((QGraphicsItem*)b);
                   BubblesAmountLabel->setText("amount: "+QString::number(++amount));
                   b->setPos(dynamic_cast<QGraphicsSceneMouseEvent*>(event)->scenePos());
                   b->setPosition(b->pos());
                   items.append(b);
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
                    BubblesAmountLabel->setText("amount: "+QString::number(--amount));
                    scene->removeItem(item);
                    items.removeAll(b);
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












