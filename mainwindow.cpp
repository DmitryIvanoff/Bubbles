#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),
                                         ui(new Ui::MainWindow),
                                         FPS(60),
                                         items_mutex(),
                                         amount(500),
                                         items(),
                                         BubbleDiameter(10)
{
    ui->setupUi(this);
    const double sceneWidth=400.0;
    const double sceneHeight=400.0;
    scene=new QGraphicsScene(0,0,sceneWidth,sceneHeight,this);
    scene->installEventFilter(this);
    QGridLayout* l=new QGridLayout;
    l->addWidget(ui->graphicsView);

    ui->centralWidget->setLayout(l);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setMouseTracking(true);

    setWindowTitle("Bubbles");
    setMinimumSize(QSize(sceneWidth+100.0,sceneHeight+100.0));

    BubblesAmountLabel=new QLabel(this);
    CoordinateLabel=new QLabel(this);
    BubblesAmountLabel->setText("amount: "+QString::number(amount));

    ui->statusBar->addWidget(BubblesAmountLabel);
    ui->statusBar->addWidget(CoordinateLabel);
    int updatePeriod=1000/FPS;//result in msec
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));

    for (uint32_t i=0;i<amount;++i)
    {
        MyBubble* item= new MyBubble(BubbleDiameter,updatePeriod);
        scene->addItem(static_cast<QGraphicsItem*>(item));
        items.push_back(item);
    }

    CThread=new CalculatorThread(&items,&items_mutex,updatePeriod/6,this);
    timer->start(updatePeriod);
    CThread->start();
}

MainWindow::~MainWindow()
{
    CThread->quit();
    CThread->wait();
    for (MyBubble* obj: items)
    {
        scene->removeItem(obj);
        delete obj;
    }
    items.clear();
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{

    if (watched == scene)
    {
        if (event->type()==QEvent::GraphicsSceneMouseMove)
        {
            //qDebug()<<"mouse move";
            QGraphicsSceneMouseEvent* me=static_cast<QGraphicsSceneMouseEvent*>(event);
            CoordinateLabel->setText(QString("x: %1;y: %2").arg(me->scenePos().x()).arg(me->scenePos().y()));
            return true;
        }

        if (event->type()==QEvent::GraphicsSceneMousePress)
        {
            QGraphicsSceneMouseEvent* me=static_cast<QGraphicsSceneMouseEvent*>(event);
            if (me->button()==Qt::LeftButton)
            {
                items_mutex.lock();
                //qDebug()<<"mouse press";
                //qDebug()<<"mutex is locked by "<<QThread::currentThreadId();
                MyBubble* b=new MyBubble(BubbleDiameter,QPointF(0,0),me->buttonDownScenePos(Qt::LeftButton),1000/FPS);
                scene->addItem(b);
                BubblesAmountLabel->setText("amount: "+QString::number(++amount));
                items.push_back(b);
                items_mutex.unlock();

            }
            if (me->button()==Qt::RightButton)
            {
                QGraphicsItem* item=scene->itemAt(me->buttonDownScenePos(Qt::RightButton),ui->graphicsView->transform());
                if (item)
                {
                    MyBubble* b=static_cast<MyBubble*>(item);
                    BubblesAmountLabel->setText("amount: "+QString::number(--amount));
                    scene->removeItem(item);
                    items_mutex.lock();
                    //qDebug()<<"mouse rb pressed";
                    //qDebug()<<"mutex is locked by "<<QThread::currentThreadId();
                    items.remove(b);
                    items_mutex.unlock();
                    delete b;
                }
            }
            return true;
        }
        return false;
    }
    else
    {
        return QMainWindow::eventFilter(watched, event);
    }
}














