#include "sockettcpru.h"

SocketTcpRU::SocketTcpRU()
{
    IPaddress = "150.162.236.217";
    //IPaddress = "192.168.0.23";
}

bool SocketTcpRU::addCreditsCard(int matricula, float saldo, float amount, QString *Error)
{
	QTextStream out(stdout);

    bool ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 1234);

    if (socket->waitForConnected(3000))
    {
        out << "Connected! Ready to Sent!" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {
            {"IWant", "changeCard"},
            {"Matricula", matricula},
            {"Amount", amount},
            {"creditsCard", saldo},
        };

        QJsonArray jsonArr {jsonObj};
        QJsonDocument jsonDoc {jsonArr};

        QString data = QString("%1\r\n\r\n\r\n").arg(jsonDoc.toJson().constData());
        socket->write(data.toLocal8Bit());

        socket->waitForBytesWritten(1000);
        out << "Waiting..." << endl;

        socket->waitForReadyRead(3000);
        out << "Read bytes: " << socket->bytesAvailable() << endl << endl;

        QString recData = socket->readAll();
        out << "Server says: " << recData.toLocal8Bit();

        JsonInterpreter.JsonReceiver(recData.toLocal8Bit());
        Aluno aluno;
        if (JsonInterpreter.getFlag() == "cash")
            aluno.setCreditsCard(JsonInterpreter.aluno.getCreditsCard());
        else if (JsonInterpreter.getFlag() == "changeCard:Error")
            ErrorOccurs = true;
        else
            out << "Deu erro no interpretador!" << endl;

        *Error = JsonInterpreter.getErrorText();

        socket->close();

        return ErrorOccurs;
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
    }
}

bool SocketTcpRU::addCreditsMobile(int matricula, float saldo, float amount, QString *Error)
{
	QTextStream out(stdout);

    bool ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 1234);

    if (socket->waitForConnected(3000))
    {
        out << "Connected! Ready to Sent!" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {
            {"IWant", "changeMobile"},
            {"Matricula", matricula},
            {"Amount", amount},
            {"creditsMobile", saldo},
        };

        QJsonArray jsonArr {jsonObj};
        QJsonDocument jsonDoc {jsonArr};

        QString data = QString("%1\r\n\r\n\r\n").arg(jsonDoc.toJson().constData());
        socket->write(data.toLocal8Bit());

        socket->waitForBytesWritten(1000);
        out << "Waiting..." << endl;

        socket->waitForReadyRead(3000);
        out << "Read bytes: " << socket->bytesAvailable() << endl << endl;

        QString recData = socket->readAll();
        out << "Server says: " << recData.toLocal8Bit();

        JsonInterpreter.JsonReceiver(recData.toLocal8Bit());
        Aluno aluno;

        if (JsonInterpreter.getFlag() == "cash")
            aluno.setCreditsMobile(JsonInterpreter.aluno.getCreditsMobile());
        else if (JsonInterpreter.getFlag() == "changeMobile:Error")
            ErrorOccurs = true;
        else
            out << "Deu erro no interpretador!" << endl;

        *Error = JsonInterpreter.getErrorText();

        socket->close();

        return ErrorOccurs;
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
    }
}
