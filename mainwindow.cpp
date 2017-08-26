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
    for (int i=0;i<50;++i)
    {
        MyBubble* item= new MyBubble(20);
        scene->addItem((QGraphicsItem*)item);
        list.append(item);
    }
    timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(1000);
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
    foreach (MyBubble* obj,list)
    {
        scene->removeItem(obj);
        delete obj;
    }
    list.clear();
    delete ui;
}
