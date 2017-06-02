#ifndef DATABASERUMANAGER_H
#define DATABASERUMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include "alunoserver.h"

class DataBaseRUManager
{
private:
    QSqlDatabase db;
    QSqlQueryModel* Model;
    QSqlQuery* query;
    bool connection;

public:
    DataBaseRUManager();
    ~DataBaseRUManager();

    bool Connect(QString *Error);

    bool UpdateAluno(AlunoServer aluno, QString *Error);
    bool AddAluno(AlunoServer aluno, QString *Error);
    bool delAluno(int matricula, QString *Error);

    AlunoServer SearchAluno(ulong matricula, QString *Error, bool &ErrorOccurs);
    QList<AlunoServer> getAllAlunos(int *howmuch);

    bool isConnected();
};

#endif // DATABASERUMANAGER_H
