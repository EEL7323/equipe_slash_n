#ifndef CLIENTJSONINTERFACE_H
#define CLIENTJSONINTERFACE_H

#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "Aluno.h"

class ClientJsonInterface
{
    QList<Aluno> alunos;

    QString flag_last_change;
    QString ErrorText;

    void JsonSaldoMobile(QJsonArray *JsonArray, QJsonObject JsonRequest);
    void JsonSaldoCard(QJsonArray *JsonArray, QJsonObject JsonRequest);
    void JsonSync(QJsonArray *JsonArray, QJsonObject JsonRequest);
    void JsonFeedbackHandler(QJsonObject JsonFb);

public:
    Aluno aluno;
    ClientJsonInterface();

    void JsonReceiver(QByteArray data);

    QString getFlag();
    QString getErrorText();
};

#endif // CLIENTJSONINTERFACE_H
