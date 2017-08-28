#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    double sceneWidth=400;
    double sceneHeight=400;
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
    for (int i=0;i<400;++i)
    {
        MyBubble* item= new MyBubble(10);
        scene->addItem((QGraphicsItem*)item);
        items.append(item);
    }
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
    timer1->start(10);
    timer2->start(200);

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











