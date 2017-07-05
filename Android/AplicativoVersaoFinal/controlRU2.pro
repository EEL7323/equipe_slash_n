#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T18:27:52
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = controlRU2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    secondwindow.cpp \
    cardinfo.cpp \
    addcredits.cpp \
    extrainfo.cpp \
    aluno.cpp \
    clientjsoninterface.cpp \
    sockettcpru.cpp \
    alunoapp.cpp \
    carddata.cpp \
    creditstoadd.cpp \
    mainwindow.cpp \
    socketesp.cpp

HEADERS  += \
    secondwindow.h \
    cardinfo.h \
    addcredits.h \
    extrainfo.h \
    aluno.h \
    clientjsoninterface.h \
    sockettcpru.h \
    alunoapp.h \
    carddata.h \
    creditstoadd.h \
    mainwindow.h \
    socketesp.h

FORMS    += \
    secondwindow.ui \
    cardinfo.ui \
    addcredits.ui \
    extrainfo.ui \
    mainwindow.ui

CONFIG += mobility
MOBILITY =

RESOURCES += \
    fontes.qrc

