#ifndef CLIENTJSONINTERFACE_H
#define CLIENTJSONINTERFACE_H

#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "alunoserver.h"

class ClientJsonInterface
{

    QList<AlunoServer> alunos;
    AlunoServer aluno;

    QString flag_last_change;
    QString ErrorText;

    void JsonRecAluno(QJsonArray *JsonArray, QJsonObject JsonRequest);
    void JsonFeedbackHandler(QJsonObject JsonFb);

public:
    ClientJsonInterface();

    void JsonReceiver(QByteArray data);

    AlunoServer getAluno();
    QList<AlunoServer> getAlunos();
    QString getFlag();
    QString getErrorText();
};

#endif // CLIENTJSONINTERFACE_H
