#ifndef DBJSONINTERFACE_H
#define DBJSONINTERFACE_H

#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "databaserumanager.h"

class DbJsonInterface
{
    DataBaseRUManager dbManager;
    QString *Error;

    QJsonDocument requestAluno(int matricula, bool &has_aluno, int index, int size);
    QJsonDocument addAluno(AlunoServer aluno);
    QJsonDocument updateAluno(AlunoServer aluno);
    QJsonDocument delAluno(int matricula);
    QJsonDocument DontUnderstand(QJsonObject header);
    QJsonDocument addCreditCard(int matricula, float amount);
    QJsonDocument addCreditMobile(int matricula, float amount);

    float RUprice = 1.5;
public:
    DbJsonInterface();

    QByteArray Handler(QByteArray inputData, bool &flag, int index, int size);
};

#endif // DBJSONINTERFACE_H
