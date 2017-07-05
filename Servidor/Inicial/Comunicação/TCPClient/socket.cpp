#include "socket.h"

socket::socket(QObject *parent) :
    QObject(parent)
{
    qtsocket = new QTcpSocket(this);
    connect(qtsocket, SIGNAL(connected()),this, SLOT(connected()));
    connect(qtsocket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(qtsocket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(qtsocket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    isconnected = false;
    IPAddress = QString("-1");
    port = -1;
}



void socket::start_connection()
{
    if( (IPAddress == QString("-1")) || (port == -1)){
        qDebug() << "IPAddress ou Port não foram definidos!";
    }
    else{
        qDebug() << "Tentando estabelecer conexão...";

        qtsocket->connectToHost(IPAddress, port);
        if(!qtsocket->waitForConnected(10000))
        {
            qDebug() << "Error: " << qtsocket->errorString();
            isconnected = false;

        }
        else{
            qtsocket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
            isconnected = true;
        }
    }

}

void socket::disconnect(){
    qtsocket->disconnectFromHost();
    isconnected = false;
    qDebug() << "Closed connection";
}


void socket::writeMessage(char *data){
    if(isconnected == true){
        qtsocket->write(data);
    }
    else{
        qDebug() << "Error: não é possivel enviar dados antes de se conectar";
    }
}

void socket::writeMessage(string data){
    //Não sei se essa conversão de string -> char array precisa de alocação de memória
    if(isconnected == true){
        char *data_char = &data[0u];
        qtsocket->write(data_char);
    }
    else{
        qDebug() << "Error: não é possivel enviar dados antes de se conectar";
    }
}

QByteArray socket::readMessage(){
    return qtsocket->readAll();
}

void socket::setIP(QString IP){
    IPAddress = IP;
}

void socket::setPort(int p){
    port = p;
}

bool socket::getConnectionStatus(){
    return isconnected;
}

//-----------------------------------------------
//SLOTS
//-----------------------------------------------
void socket::connected()
{
    qDebug() << "On connected slot...";
}

void socket::disconnected()
{
    isconnected = false;
    qDebug() << "On disconnected slot...";
}

void socket::bytesWritten(qint64 bytes)
{
    qDebug() << "On bytes_written slot... bytes written:" << bytes;
}

void socket::readyRead()
{
    qDebug() << "On ready_read slot...";
    emit SIGNAL_socket_received_data();
}


