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
    for (int i=0;i<300;++i)
    {
        MyBubble* item= new MyBubble(10);
        scene->addItem((QGraphicsItem*)item);
        list.append(item);
    }
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    connect(timer1,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(advance()));
    timer1->start(33);
    timer2->start(100);

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

void calculate(std::list<MyBubble *> items)
{
    std::list<MyBubble*>::iterator it=items.begin();
    for (;it!=items.end();++it)
    {
        std::list<MyBubble*>::iterator it_2=items.begin();
        double v_x=(*it)->getV().x();
        double v_y=(*it)->getV().y();
        while (it_2!=items.end())
        {
             double rx=(*it_2)->getPosition().x()-(*it)->getPosition().x();
             double ry=(*it_2)->getPosition().y()-(*it)->getPosition().y();
             double r=sqrt(rx*rx+ry*ry);
             if (r>(*it)->getDiameter())
             {
                 double F=fabs(1/r-1/(r*r));
                 double F_x=F*rx/r;
                 double F_y=F*ry/r;
                 v_x+=F_x;
                 v_y+=F_y;
             }
             else
             {
                 v_x+=0.0;
                 v_y+=0.0;
             }
             ++it_2;
        }
        (*it)->setV(QPointF(v_x,v_y));

    }
}

void MainWindow::advance()
{

        std::thread thr(calculate,list.toStdList());
        thr.join();
}



