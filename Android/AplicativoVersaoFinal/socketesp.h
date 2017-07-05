#ifndef SOCKETESP_H
#define SOCKETESP_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include "alunoapp.h"
#include "clientjsoninterface.h"

class SocketESP : public QObject
{

private:
    QTcpSocket *socket;
    ClientJsonInterface JsonInterpreter;
    QString IPaddress;

public:
    SocketESP();
    bool requestAccess(int matricula, int led, QString *Error, bool &ErrorOccurs);
    int requestOccupants();
};

#endif // SOCKETESP_H
