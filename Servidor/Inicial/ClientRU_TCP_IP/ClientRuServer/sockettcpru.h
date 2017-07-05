#ifndef SOCKETTCPRU_H
#define SOCKETTCPRU_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include "alunoserver.h"
#include "clientjsoninterface.h"

class SocketTcpRU : public QObject
{
public:

    SocketTcpRU();

    void connect();
    AlunoServer SearchAluno(int matricula, QString *Error, bool &ErrorOccurs);
    bool AddAluno(AlunoServer aluno, QString *Error);
    bool updateAluno(AlunoServer aluno, QString *Error);
    bool delAluno(ulong matricula, QString *Error);
    bool addCreditCard(int matricula, float saldo, float amount, QString *Error); //returns true if credits were added
    bool addCreditMobile(int matricula, float saldo, float amount, QString *Error); //returns true if credits were added

signals:

private:
    QTcpSocket *socket;
    ClientJsonInterface JsonInterpreter;
    QString IPaddress;
};

#endif // SOCKETTCPRU_H
