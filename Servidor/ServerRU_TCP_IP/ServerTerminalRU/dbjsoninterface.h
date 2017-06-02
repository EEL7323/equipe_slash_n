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

    QJsonDocument requestAluno(int matricula);
    QJsonDocument addAluno(AlunoServer aluno);
    QJsonDocument updateAluno(AlunoServer aluno);
    QJsonDocument delAluno(int matricula);

public:
    DbJsonInterface();

    QByteArray Handler(QByteArray inputData);
};

#endif // DBJSONINTERFACE_H
