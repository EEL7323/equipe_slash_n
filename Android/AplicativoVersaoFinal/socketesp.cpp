#include "socketesp.h"

SocketESP::SocketESP()
{
    IPaddress = "192.168.137.163";
}

bool SocketESP::requestAccess(int matricula, int led, QString *Error, bool &ErrorOccurs)
{
    QTextStream out(stdout);

    ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 8025);

    if (socket->waitForConnected(3000))
    {
        out << "Connected! Ready to Sent!" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {
            {"ThereIs", "LEDs"},
            {"Matricula", matricula},
            {"LEDs", led},
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
        AlunoApp aluno;
        if (JsonInterpreter.getFlag() == "enterRU:Ok")
            ErrorOccurs = false;
        else if (JsonInterpreter.getFlag() == "enterRU:Error")
            ErrorOccurs = true;
        else
        {
            ErrorOccurs = true;
            out << "Deu erro no interpretador!" << endl;
        }

        *Error = JsonInterpreter.getErrorText();

        socket->close();
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
        ErrorOccurs = true;
    }
    return !ErrorOccurs;
}

int SocketESP::requestOccupants()
{
    int returnAux;
    QTextStream out(stdout);
    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 8025);

    if (socket->waitForConnected(3000))
    {
        out << "Connected! Ready to Sent!" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {
            {"ThereIs", "getOcupacao"},
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

        returnAux = JsonInterpreter.getOccupants();

        socket->close();
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
        returnAux = -1;
    }
    return returnAux;
}
