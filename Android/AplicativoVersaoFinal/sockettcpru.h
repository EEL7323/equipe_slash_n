#ifndef SOCKETTCPRU_H
#define SOCKETTCPRU_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include "alunoapp.h"
#include "carddata.h"
#include "clientjsoninterface.h"

class SocketTcpRU : public QObject
{
public:

    SocketTcpRU();

    AlunoApp SearchAluno(int matricula, QString *Error, bool &ErrorOccurs);
    bool addCreditCard(int matricula, float amount, CardData teste, QString *Error);
    bool addCreditMobile(int matricula, float amount, CardData teste, QString *Error);


signals:

private:
    QTcpSocket *socket;
    ClientJsonInterface JsonInterpreter;
    QString IPaddress;
};

#endif // SOCKETTCPRU_H
