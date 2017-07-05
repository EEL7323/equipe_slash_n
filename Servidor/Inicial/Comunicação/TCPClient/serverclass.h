#ifndef SERVERCLASS_H
#define SERVERCLASS_H

#include <QObject>
#include <QtNetwork>
#include "socket.h"

class serverClass : public QObject
{
    Q_OBJECT
public:
    explicit serverClass(QObject *parent = 0);
    void configSocketConnection(QString IP, qint64 port);
    void server_send(string data);
    void server_send(char *data);

    //Outras funções do servidor
    void configSQL();
    int readSQL(string table);
    void updateSQL(string table, string value, int newdata);
    //etc
    //etc

private:
    socket socket_obj;
public slots:
    QByteArray server_receive();
};

#endif // SERVERCLASS_H
