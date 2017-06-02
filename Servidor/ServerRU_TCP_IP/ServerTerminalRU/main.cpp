#include <QCoreApplication>
#include <QTextStream>

#include "databaserumanager.h"
#include "serverru.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);
    out << "Saida OK!" << endl;

    ServerRU mServer;


    return a.exec();
}
