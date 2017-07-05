#ifndef SOCKETTCPRU_H
#define SOCKETTCPRU_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include "aluno.h"
#include "clientjsoninterface.h"

class SocketTcpRU : public QObject
{
public:

    SocketTcpRU();

    bool addCreditsCard(int matricula, float saldo, float amount, QString *Error);
    bool addCreditsMobile(int matricula, float saldo, float amount, QString *Error);

signals:

private:
    QTcpSocket *socket;
    ClientJsonInterface JsonInterpreter;
    QString IPaddress;
};

#endif // SOCKETTCPRU_H
