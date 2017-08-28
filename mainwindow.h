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
#include <QLabel>
#include "mybubble.h"
#include "calculator.h"
#include "eventfilter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     bool eventFilter(QObject *watched, QEvent *event);
protected:
private:
    QThread* thread;
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QList<MyBubble*> items;
    QTimer* timer1;
    QTimer* timer2;
    QLabel* label;
    Calculator* calculator;

};

#endif // MAINWINDOW_H
