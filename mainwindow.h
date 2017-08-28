#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QMutableListIterator>
#include <QTimeLine>
#include <QTimer>
#include <thread>
#include <QThread>
#include <list>
#include "mybubble.h"
#include "calculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    QThread* thread;
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QList<MyBubble*> items;
    QTimer* timer1;
    QTimer* timer2;
    Calculator* calculator;

};

#endif // MAINWINDOW_H
