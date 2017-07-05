#include "sockettcpru.h"

SocketTcpRU::SocketTcpRU()
{
    //IPaddress = "192.168.43.167";
    IPaddress = "192.168.137.109";
}

AlunoApp SocketTcpRU::SearchAluno(int matricula, QString *Error, bool &ErrorOccurs)
{
    QTextStream out(stdout);

    ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 1234);
//    socket->connectToHost(IPAddress, 1234);

    if (socket->waitForConnected(7000))
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
        out << "Read bytes: " << socket->bytesAvailable() << endl << endl;

        QString recData = socket->readAll();
        out << "Server says: " << recData.toLocal8Bit();

        JsonInterpreter.JsonReceiver(recData.toLocal8Bit());
        AlunoApp aluno;
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

bool SocketTcpRU::addCreditCard(int matricula, float amount, CardData teste, QString *Error)
{
	QTextStream out(stdout);

    bool ErrorOccurs = false;
    QString auxCard = teste.getCardNumber();
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
            {"CardMonth", teste.getMonthDeadline()},
            {"CardYear", teste.getYearDeadline()},
            {"CardSafe", teste.getSafeCard()},
            {"CardNumb", auxCard},
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
        if (JsonInterpreter.getFlag() == "changeCard:Ok")
            aluno.setCreditsCard(JsonInterpreter.getAluno().getCreditsCard());
        else if (JsonInterpreter.getFlag() == "changeCard:Error")
            ErrorOccurs = true;
        else
            out << "Deu erro no interpretador!" << endl;

        *Error = JsonInterpreter.getErrorText();

        socket->close();

        return !ErrorOccurs;
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
    }
}

bool SocketTcpRU::addCreditMobile(int matricula, float amount, CardData teste, QString *Error)
{
	QTextStream out(stdout);

    bool ErrorOccurs = false;
    QString auxCard = teste.getCardNumber();
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
            {"CardMonth", teste.getMonthDeadline()},
            {"CardYear", teste.getYearDeadline()},
            {"CardSafe", teste.getSafeCard()},
            {"CardNumb", auxCard},
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

        if (JsonInterpreter.getFlag() == "changeMobile:Ok")
            aluno.setCreditsMobile(JsonInterpreter.getAluno().getCreditsMobile());
        else if (JsonInterpreter.getFlag() == "changeMobile:Error")
            ErrorOccurs = true;
        else
            out << "Deu erro no interpretador!" << endl;

        *Error = JsonInterpreter.getErrorText();

        socket->close();

        return !ErrorOccurs;
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;
    }
}
