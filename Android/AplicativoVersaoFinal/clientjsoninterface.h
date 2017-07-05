#ifndef CLIENTJSONINTERFACE_H
#define CLIENTJSONINTERFACE_H

#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "AlunoApp.h"

class ClientJsonInterface
{
    QList<Aluno> alunos;

    QString flag_last_change;
    QString ErrorText;
    int occupants;

    void JsonSaldoMobile(QJsonArray *JsonArray, QJsonObject JsonRequest);
    void JsonSaldoCard(QJsonArray *JsonArray, QJsonObject JsonRequest);
    void JsonSync(QJsonArray *JsonArray, QJsonObject JsonRequest);
    void JsonRecAluno(QJsonArray *JsonArray, QJsonObject JsonRequest);

    void JsonFeedbackHandler(QJsonObject JsonFb);

public:
    AlunoApp aluno;
    ClientJsonInterface();

    void JsonReceiver(QByteArray data);
    int getOccupants();
    AlunoApp getAluno();
    QString getFlag();
    QString getErrorText();
};

#endif // CLIENTJSONINTERFACE_H
