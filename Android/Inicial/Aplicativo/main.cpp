#include "mainwindow.h"
#include "secondwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

void ControlSecondWindow(bool createSecondWindow, bool createCardInfo, bool destroyCardInfo)
{
    CardInfo *registerCard;
    SecondWindow *loggedWindow;

    if(createSecondWindow == true)
    {
        //loggedWindow =  new SecondWindow(this);
        //loggedWindow -> showMaximized();
    } else if(createCardInfo == true)
    {
        //registerCard = new CardInfo(this);
        //registerCard -> show();
    } else if(destroyCardInfo)
    {
        //registerCard -> close();
        //delete registerCard;
    }
}
