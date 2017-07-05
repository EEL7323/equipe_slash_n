#include "myudp.h"

MyUDP::MyUDP(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 1234);
    connect(socket,SIGNAL(readyRead()),this,SLOT(ReadyRead()));

}


void MyUDP::SayHello()
{
    QByteArray data;
    data.append("Hello from SayHello");
    socket->writeDatagram(data,QHostAddress::LocalHost,1234);
}


void MyUDP::ReadyRead()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(), buffer.size(),&sender,&senderPort);
    qDebug() << "Message from " << sender.toString() << endl;
    qDebug() << "Message port " << senderPort << endl;
    qDebug() << "Message data " << buffer << endl;


}
