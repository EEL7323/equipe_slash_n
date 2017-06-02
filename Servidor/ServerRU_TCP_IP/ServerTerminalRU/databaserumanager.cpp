#include "databaserumanager.h"
#include <QTextStream>

DataBaseRUManager::DataBaseRUManager()
{
    db = QSqlDatabase::addDatabase("QODBC");
    connection = false;
    query = nullptr;
}

DataBaseRUManager::~DataBaseRUManager()
{
    delete query;
}


bool DataBaseRUManager::Connect(QString *Error) {

    QString servername = "NATANVOTRE\\SQLEXPRESS";
    QString dbname = "RU_control_db";
    QString UID = "natan";

    db.setConnectOptions();

    QString dsn = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;UID=%3;Trusted_Connection=Yes;").arg(servername).arg(dbname).arg(UID);

    db.setDatabaseName(dsn);

    if (!db.open()) {
//        QMessageBox::critical(0, qApp->tr("Banco de Dados Não abriu! :("),
//            qApp->tr("Infelizmente, o banco de dados não abriu.\n"
//                     "Tente abrir o SQL Management Studio!"
//                     "Caso nao tenha instalado, favor instalar!\n\n"
//                     "Click Cancel to exit."), QMessageBox::Cancel);
        *Error = db.lastError().text();
        QTextStream out(stdout);
        out << Error << endl;

        connection = false;

        return false;
    }

    connection = true;
    delete query;
    query = new QSqlQuery();

//    query->exec("create table cliente (matricula int primary key, "
//               "nome varchar(40), creditsmobile float, creditscard float)");

    return true;
}

bool DataBaseRUManager::AddAluno(AlunoServer aluno, QString *Error) {

    delete query;
    query = new QSqlQuery();

    QString querycommand = QString("insert into cliente values(%1, '%2', %3, %4)")
                .arg(aluno.getMatricula()).arg(aluno.getNome()).arg(aluno.getcreditsMobile()).arg(aluno.getcreditsCard());

    if (!query->exec(querycommand))
    {
        *Error = query->lastError().text();
        QString error = *Error;
        QTextStream out(stdout);
        out << error << endl;
        return false;
    } else
        return true;
}

bool DataBaseRUManager::delAluno(int matricula, QString *Error)
{
    delete query;
    query = new QSqlQuery();

    QString querycommand = QString("DELETE FROM cliente WHERE matricula = %1").arg(matricula);

    if (!query->exec(querycommand))
    {
        *Error = query->lastError().text();
        QString error = *Error;
        QTextStream out(stdout);
        out << error << endl;
        return false;
    } else
        return true;
}

bool DataBaseRUManager::UpdateAluno(AlunoServer aluno, QString *Error) {

    delete query;
    query = new QSqlQuery();

    QString querycommand = QString("UPDATE cliente SET nome = '%1', creditsmobile = %2, creditscard = %3 "
                                        "WHERE matricula = %4")
                                        .arg(aluno.getNome())
                                        .arg(aluno.getcreditsMobile())
                                        .arg(aluno.getcreditsCard())
                                        .arg(aluno.getMatricula());

    if (!query->exec(querycommand))
    {
        *Error = query->lastError().text();
        QString error = *Error;
        QTextStream out(stdout);
        out << error << endl;
        return false;
    } else
        return true;
}

AlunoServer DataBaseRUManager::SearchAluno(ulong matricula, QString *Error, bool &ErrorOccurs)
{

    Model = new QSqlQueryModel();
    QString queryString = QString("SELECT * FROM cliente WHERE matricula = %1").arg(matricula);
//    QString queryString = QString("SELECT %1 FROM cliente").arg(matricula);
    Model->setQuery(queryString);

    QTextStream out(stdout);

    QModelIndex index;
    QString rowData[4];

    for (int column = 0; column < 4; column++)
    {
        index = Model->index(0, column, QModelIndex());
        rowData[column] = Model->data(index, Qt::DisplayRole).toString();
    }

    AlunoServer aluno;
    aluno.setMatricula(rowData[0].toULong());
    aluno.setNome(rowData[1]);
    aluno.setcreditsMobile(rowData[2].toFloat());
    aluno.setcreditsCard(rowData[3].toFloat());

//    if (query->exec(queryString))
    if (aluno.getNome() == "Empty")
    {
        *Error = Model->lastError().text();
        QString error = *Error;
        QTextStream out(stdout);
        out << error << "Aluno nao encontrado no banco de dados" << endl;
        ErrorOccurs = true;
    } else
        ErrorOccurs = false;

    delete Model;

    return aluno;
}

QList<AlunoServer> DataBaseRUManager::getAllAlunos(int *howmuch)
{
    QList<AlunoServer> alunos;

    Model = new QSqlQueryModel();
    QString queryString = QString("SELECT * FROM cliente");
//    QString queryString = QString("SELECT %1 FROM cliente").arg(matricula);
    Model->setQuery(queryString);

    QTextStream out(stdout);
    out << Model->lastError().text() << endl;

    QModelIndex index;
    QString rowData[4];


    int rows = 0;
    while (Model->hasIndex(rows, 0, QModelIndex()))
    {
        for (int column = 0; column < 4; column++)
        {
            index = Model->index(rows, column, QModelIndex());
            rowData[column] = Model->data(index, Qt::DisplayRole).toString();
        }

        AlunoServer aluno;
        aluno.setMatricula(rowData[0].toULong());
        aluno.setNome(rowData[1]);
        aluno.setcreditsMobile(rowData[2].toFloat());
        aluno.setcreditsCard(rowData[3].toFloat());

        alunos.push_front(aluno);
        rows++;
    }

    delete Model;
    *howmuch = rows;

    return alunos;
}



bool DataBaseRUManager::isConnected()
{
    return connection;
}
