#include "sockettcpesp.h"


SocketTcpESP::SocketTcpESP()
{
//    IPaddress = "150.162.236.217";
    IPaddress = "192.168.137.210";
}

QByteArray SocketTcpESP::talkESP(QString thereis, QString *Error)
{
    QTextStream out(stdout);

    bool ErrorOccurs = false;
    Error->clear();

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 8025);

    if (socket->waitForConnected(3000))
    {
        out << "Here is the Socket!! \n\n";
        out << "Connected! Ready to Sent!\nWe are here to try talk with the ESP" << endl;

        // Write to Server a Request!
        QJsonObject jsonObj {   // requisicao em Json
            {"ThereIs", thereis},
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

        socket->close();

        return recData.toLocal8Bit();
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;

        return QString("isnotLive").toLocal8Bit();
    }
}

QByteArray SocketTcpESP::sendThis(QString data)
{
    QTextStream out(stdout);

    socket = new QTcpSocket(this);

    socket->connectToHost(IPaddress, 8025);

    if (socket->waitForConnected(3000))
    {
        QString outData = QString("%1\r\n\r\n\r\n").arg(data);
        socket->write(outData.toLocal8Bit());  // escreve requisicao pro server

        socket->waitForBytesWritten(1000);
        out << "Waiting..." << endl;

        socket->waitForReadyRead(3000);
        out << "Readed bytes: " << socket->bytesAvailable() << endl << endl;

        QString recData = socket->readAll();
        out << "Server says: " << recData.toLocal8Bit();

        socket->close();

        return recData.toLocal8Bit();
    } else
    {
        out << "Nao foi possivel estabelecer conexao com o servidor! :/" << endl;

        return QString("isnotLive").toLocal8Bit();
    }
}

