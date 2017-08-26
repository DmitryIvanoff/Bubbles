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
#include "mybubble.h"
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
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QList<MyBubble*> list;
    QTimer* timer;
};

#endif // MAINWINDOW_H
