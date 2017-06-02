#ifndef SERVERRU_H
#define SERVERRU_H

#include <QObject>
#include <QTextStream>
#include <QTcpServer>
#include <QTcpSocket>

#include "dbjsoninterface.h"

class ServerRU : public QObject
{
    Q_OBJECT
public:
    explicit ServerRU(QObject *parent = 0);

signals:

public slots:
    void newConnection();

private:
    QTcpServer *server;
    DbJsonInterface dbJson;
};

#endif // SERVERRU_H
