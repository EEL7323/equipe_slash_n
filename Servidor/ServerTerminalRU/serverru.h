#ifndef SERVERRU_H
#define SERVERRU_H

#include <QObject>
#include <QTextStream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "dbjsoninterface.h"
#include "sockettcpesp.h"

class ServerRU : public QObject
{
    Q_OBJECT
public:
    explicit ServerRU(QObject *parent = 0);

signals:
    void interruptTimer();

public slots:
    void newConnection();
    void updateTimer();

private:
    bool Oscilate;
    SocketTcpESP socket;
    QTcpServer *server;
    DbJsonInterface dbJson;
    QTimer *mTimer;
};

#endif // SERVERRU_H
