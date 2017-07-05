#ifndef SOCKET_H
#define SOCKET_H



#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <iostream>
#include <string>

using namespace std;

class socket : public QObject
{
    Q_OBJECT
public:
    explicit socket(QObject *parent = 0);

    void start_connection();
    void disconnect();
    void writeMessage(char *data);
    void writeMessage(string data);
    QByteArray readMessage();
    void setIP(QString IP);
    void setPort(int p);
    bool getConnectionStatus();

signals:
    void SIGNAL_socket_received_data();

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();


private:
    QTcpSocket *qtsocket;
    bool isconnected;
    QString IPAddress;
    int port;

};



#endif // SOCKET_H
