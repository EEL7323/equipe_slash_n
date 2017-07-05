#include "sockettcpru.h"

SocketTcpRU::SocketTcpRU()
{
//    IPaddress = "150.162.236.217";
//    IPaddress = "192.168.0.23";
    IPaddress = "192.168.137.148";
}

AlunoServer SocketTcpRU::SearchAluno(int matricula, QString *Error, bool &ErrorOccurs)
{
    QTextStream out(stdout);

    ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 1234);
//    socket->connectToHost(IPAddress, 1234);

    if (socket->waitForConnected(3000))
    {
        out << "Connected! Ready to Sent!" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {
            {"IWant", "rAluno"},
            {"Matricula", matricula},
        };

        QJsonArray jsonArr {jsonObj};
        QJsonDocument jsonDoc {jsonArr};

        QString data = QString("%1\r\n\r\n\r\n").arg(jsonDoc.toJson().constData());
        socket->write(data.toLocal8Bit());
//        socket->write("regards. <bang!>");

        socket->waitForBytesWritten(1000);
        out << "Waiting..." << endl;

        socket->waitForReadyRead(3000);
        out << "Readed bytes: " << socket->bytesAvailable() << endl << endl;

        QString recData = socket->readAll();
        out << "Server says: " << recData.toLocal8Bit();

        JsonInterpreter.JsonReceiver(recData.toLocal8Bit());
        AlunoServer aluno;
        if (JsonInterpreter.getFlag() == "aluno")
            aluno = JsonInterpreter.getAluno();
        else if (JsonInterpreter.getFlag() == "rAluno:Error")
            ErrorOccurs = true;
        else
            out << "Deu erro no interpretador!" << endl;

        *Error = JsonInterpreter.getErrorText();

        socket->close();

        return aluno;
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
    }

}

bool SocketTcpRU::AddAluno(AlunoServer aluno, QString *Error)
{
    QTextStream out(stdout);

    bool ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 1234);

    if (socket->waitForConnected(3000))
    {
        out << "Connected! Ready to Sent!\nWe are here to try Add an Aluno in dataBase" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {   // requisicao em Json
            {"IWant", "addAluno"},
            {"Matricula", int(aluno.getMatricula())},
            {"Nome", aluno.getNome()},
            {"creditsMobile", aluno.getcreditsMobile()},
            {"creditsCard", aluno.getcreditsCard()},
            {"senhaApp", aluno.getSenha()},
        };
        QJsonArray jsonArr {jsonObj};
        QJsonDocument jsonDoc {jsonArr};

        QString data = QString("%1\r\n\r\n\r\n").arg(jsonDoc.toJson().constData());
        socket->write(data.toLocal8Bit());  // escreve requisicao pro server

        socket->waitForBytesWritten(1000);
        out << "Waiting..." << endl;

        socket->waitForReadyRead(3000);
        out << "Readed bytes: " << socket->bytesAvailable() << endl << endl;

        QString recData = socket->readAll();
        out << "Server says: " << recData.toLocal8Bit();

        JsonInterpreter.JsonReceiver(recData.toLocal8Bit());

        *Error = JsonInterpreter.getErrorText();
        if (JsonInterpreter.getFlag() == "addAluno:Ok")
        {
            ErrorOccurs = false;
        } else if (JsonInterpreter.getFlag() == "addAluno:Error")
            ErrorOccurs = true;
        else
            *Error = *Error + "\nErro no interpretador JSON";

        socket->close();

        return !ErrorOccurs;
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
    }

}

bool SocketTcpRU::updateAluno(AlunoServer aluno, QString *Error)
{
    QTextStream out(stdout);

    bool ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 1234);

    if (socket->waitForConnected(3000))
    {
        out << "Connected! Ready to Sent!\nWe are here to try Update an Aluno in dataBase" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {   // requisicao em Json
            {"IWant", "updateAluno"},
            {"Matricula", int(aluno.getMatricula())},
            {"Nome", aluno.getNome()},
            {"creditsMobile", aluno.getcreditsMobile()},
            {"creditsCard", aluno.getcreditsCard()},
            {"senhaApp", aluno.getSenha()},
        };
        QJsonArray jsonArr {jsonObj};
        QJsonDocument jsonDoc {jsonArr};

        QString data = QString("%1\r\n\r\n\r\n").arg(jsonDoc.toJson().constData());
        socket->write(data.toLocal8Bit());  // escreve requisicao pro server

        socket->waitForBytesWritten(1000);
        out << "Waiting..." << endl;

        socket->waitForReadyRead(3000);
        out << "Readed bytes: " << socket->bytesAvailable() << endl << endl;

        QString recData = socket->readAll();
        out << "Server says: " << recData.toLocal8Bit();

        JsonInterpreter.JsonReceiver(recData.toLocal8Bit());

        *Error = JsonInterpreter.getErrorText();
        if (JsonInterpreter.getFlag() == "updateAluno:Ok")
        {
            ErrorOccurs = false;
        } else if (JsonInterpreter.getFlag() == "updateAluno:Error")
            ErrorOccurs = true;
        else
            *Error = *Error + "\nErro no interpretador JSON";

        socket->close();

        return !ErrorOccurs;
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
        *Error = "Nao foi possivel estabelecer conexao com o servidor!";
    }
}

bool SocketTcpRU::delAluno(ulong matricula, QString *Error)
{
    QTextStream out(stdout);

    bool ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 1234);

    if (socket->waitForConnected(3000))
    {
        out << "Connected! Ready to Sent!\nWe are here to try delete an Aluno in dataBase" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {   // requisicao em Json
            {"IWant", "delAluno"},
            {"Matricula", int(matricula)},
        };
        QJsonArray jsonArr {jsonObj};
        QJsonDocument jsonDoc {jsonArr};

        QString data = QString("%1\r\n\r\n\r\n").arg(jsonDoc.toJson().constData());
        socket->write(data.toLocal8Bit());  // escreve requisicao pro server

        socket->waitForBytesWritten(1000);
        out << "Waiting..." << endl;

        socket->waitForReadyRead(3000);
        out << "Readed bytes: " << socket->bytesAvailable() << endl << endl;

        QString recData = socket->readAll();
        out << "Server says: " << recData.toLocal8Bit();

        JsonInterpreter.JsonReceiver(recData.toLocal8Bit());

        *Error = JsonInterpreter.getErrorText();
        if (JsonInterpreter.getFlag() == "delAluno:Ok")
        {
            ErrorOccurs = false;
        } else if (JsonInterpreter.getFlag() == "delAluno:Error")
            ErrorOccurs = true;
        else
            *Error = *Error + "\nErro no interpretador JSON";

        socket->close();

        return !ErrorOccurs;
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
    }
}

