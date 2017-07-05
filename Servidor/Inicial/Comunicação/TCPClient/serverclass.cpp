#include "serverclass.h"

serverClass::serverClass(QObject *parent) : QObject(parent)
{
    //Este sistema de SIGNAL/SLOT do Qt cria algo parecido com um interrupt
    //Quando o socket_obj recebe algum dado, ele gera um sinal "SIGNAL_socket_received_data"
    //Esse sinal é conectado ao slot "server_receive" desta classe
    //Sempre que o sinal for ativado, o slot vai ser chamado
    QObject::connect(&socket_obj,&socket::SIGNAL_socket_received_data,this,server_receive);
    //connect(Objeto que cria o sinal,
    //        Sinal enviado,
    //        Objeto que recebe o sinal,
    //        Slot que é chamado quando o sinal é recebido
    //        );

}


QByteArray serverClass::server_receive(){
    //Função chamada sempre que o socket recebe algum dado
    QByteArray data = socket_obj.readMessage();
    qDebug() << data;
    return data;
}

void serverClass::server_send(string data){
    socket_obj.writeMessage(data);
}

void serverClass::server_send(char *data){
    socket_obj.writeMessage(data);
}

void serverClass::configSocketConnection(QString IP, qint64 port){
    socket_obj.setIP(IP);
    socket_obj.setPort(port);
    socket_obj.start_connection();
}
