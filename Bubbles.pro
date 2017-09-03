#-------------------------------------------------
#
# Project created by QtCreator 2017-08-26T09:13:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bubbles
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mybubble.cpp \
    calculator.cpp \
    calculatorthread.cpp

HEADERS  += mainwindow.h \
    mybubble.h \
    calculator.h \
    calculatorthread.h

FORMS    += mainwindow.ui
