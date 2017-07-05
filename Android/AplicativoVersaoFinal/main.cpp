#include "MainWindow.h"
#include "secondwindow.h"
#include <QApplication>

/*
*  1 - Add Credits to Card
*  2 - Add Credits to Mobile
*  3 - Went to RU?
*/
char updateType;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
