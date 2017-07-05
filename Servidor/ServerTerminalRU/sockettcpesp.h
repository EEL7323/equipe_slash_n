#ifndef SOCKETTCPESP_H
#define SOCKETTCPESP_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "alunoserver.h"
#include "clientespjsoninterface.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class SocketTcpESP : public QObject
{
public:

    SocketTcpESP();

    void connect();
//    AlunoServer SearchAluno(int matricula, QString *Error, bool &ErrorOccurs);
//    bool AddAluno(AlunoServer aluno, QString *Error);
//    bool updateAluno(AlunoServer aluno, QString *Error);
//    bool delAluno(ulong matricula, QString *Error);
    QByteArray talkESP(QString thereis, QString *Error);
    QByteArray sendThis(QString data);

signals:

private:
    QTcpSocket *socket;
    QString IPaddress;

};

#endif // SOCKETTCPRU_H
