#include "serverru.h"
#include <QTime>

ServerRU::ServerRU(QObject *parent)
{
    Oscilate = false;
    QTextStream out(stdout);

    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any,1234))
    {
        out << "Não foi possível conectar o Servidor :/" << endl;
    } else
    {
        out << "Servidor foi iniciado!" << endl;
    }


    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    mTimer->start(20000);

}

void ServerRU::updateTimer()
{
    QTextStream out(stdout);

    QString Error;
    QString thereis;
    if (Oscilate)
        thereis = "getUpdates";
    else
        thereis = "WhatDoYouWant";
    Oscilate = !Oscilate;
//    thereis = "getUpdates";

    QByteArray responseESP = socket.talkESP(thereis, &Error);
    QByteArray new_responseESP;

    if (QString::fromLocal8Bit(responseESP) != "isnotLive")
    {
        bool flag = true;
        int index = 0;
        int size = 4;
        while (flag)
        {
            QString dataOut = dbJson.Handler(responseESP, flag, index, size);
            index = index + size;

            if (!flag)
                break;

            if (dataOut == "nothing")
                out << "Ele não quis nada agora...\n\n";
            else if (dataOut == "Good")
            {
                out << "ESP disse:\n\n" << responseESP;
            }
            else
            {
                out << "ESP disse:\n\n" << responseESP;
                new_responseESP = socket.sendThis(dataOut);
                QTime dieTime = QTime::currentTime().addSecs(1);
                while (QTime::currentTime() < dieTime)
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                out << "ESP disse depois:\n\n" << new_responseESP;
            }
        }
    }
}

// Client Request...
void ServerRU::newConnection()
{
    QTextStream out(stdout);

    QTcpSocket *socket = server->nextPendingConnection();

    // Wait Receive Data
    socket->waitForReadyRead(1000);

    out << "Numero de bytes recebidos do cliente: " << socket->bytesAvailable() << endl;
    QString data = socket->readAll();
    out << "Client Send: " << data << endl;

    // envia o JSON recebido para o tratador do Json <-> database
    bool flag;
    int index;
    int size;
    QString dataOut = dbJson.Handler(data.toLocal8Bit(), flag, index, size);

    socket->write(QString("%1\n\n\r\n").arg(dataOut).toLocal8Bit());

    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
}
