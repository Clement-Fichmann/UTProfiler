#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T21:05:51
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTProfiler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    uvmanager.cpp \
    openingwindow.cpp \
    ajouteruvwindow.cpp \
    formationmanager.cpp \
    ajouterformationwindow.cpp

HEADERS  += mainwindow.h \
    uvmanager.h \
    utprofilerexception.h \
    openingwindow.h \
    ajouteruvwindow.h \
    formationmanager.h \
    ajouterformationwindow.h

FORMS    += mainwindow.ui \
    openingwindow.ui \
    ajouteruvwindow.ui \
    ajouterformationwindow.ui
