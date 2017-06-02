#include "serverru.h"

ServerRU::ServerRU(QObject *parent)
{
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
    QString dataOut = dbJson.Handler(data.toLocal8Bit());

    socket->write(QString("%1\n\n\r\n").arg(dataOut).toLocal8Bit());

    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
}
