#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    double sceneWidth=400;
    double sceneHeight=400;
    int updPeriod=10;
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
    setMinimumSize(QSize(sceneWidth+100,sceneHeight+100));
    label=new QLabel(this);
    ui->centralWidget->setMouseTracking(true);
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->setMouseTracking(true);
    ui->statusBar->addWidget(label);
    for (int i=0;i<3;++i)
    {
        MyBubble* item= new MyBubble(5);
        item->setFrameDuration(updPeriod);
        scene->addItem((QGraphicsItem*)item);
        items.append(item);
    }
    ui->graphicsView->installEventFilter(new EventFilter(&items));
    calculator=new Calculator(&items);
    thread=new QThread(this);
    calculator->moveToThread(thread);
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    connect(timer1,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(thread, SIGNAL(finished()),calculator,SLOT(deleteLater()));
    connect(timer2,SIGNAL(timeout()),calculator,SLOT(calculate()));
    thread->start(QThread::NormalPriority);
    QThread::currentThread()->setPriority(QThread::HighPriority);
    timer1->start(updPeriod);
    timer2->start(updPeriod);



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
    thread->quit();
    thread->wait();
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
    QGraphicsView* view=dynamic_cast<QGraphicsView*>(watched);
    if (view)
    {
        if (event->type()==QEvent::MouseMove)
        {
            QMouseEvent* e=dynamic_cast<QMouseEvent*>(event);
            label->setText(QString("x: %1;y: %2").arg(e->pos().x()).arg(e->pos().y()));
            ui->centralWidget->repaint();
        }
    }
    return false;
}












