#ifndef CLIENTESPJSONINTERFACE_H
#define CLIENTESPJSONINTERFACE_H

#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class ClientEspJsonInterface
{

//    QList<AlunoServer> alunos;
//    AlunoServer aluno;

//    QString flag_last_change;
//    QString ErrorText;

//    void JsonRecAluno(QJsonArray *JsonArray, QJsonObject JsonRequest);
//    void JsonFeedbackHandler(QJsonObject JsonFb);

public:
    ClientEspJsonInterface();

    QString JsonReceiver(QByteArray data);

//    AlunoServer getAluno();
//    QList<AlunoServer> getAlunos();
//    QString getFlag();
//    QString getErrorText();
};

#endif // CLIENTJSONINTERFACE_H
