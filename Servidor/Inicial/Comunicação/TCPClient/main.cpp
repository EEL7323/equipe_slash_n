#include <iostream>
#include <string>
#include <QCoreApplication>
#include "socket.h"
#include "serverclass.h"

using namespace std;


//-----------------------------------------------
//Exemplo de uma classe que usa o socket
//-----------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    serverClass server_obj;

        QString IP = "192.168.100.13";     //Fixei o IP do módulo wifi nisso
        int port = 7009;              //Fixei o port que está sendo usado nisso
        server_obj.configSocketConnection(IP,port);


    string data_string = "Teste string\n";
    server_obj.server_send(data_string);

    char *data_array = "Teste array\n";
    server_obj.server_send(data_array);

    return a.exec();
}






//-----------------------------------------------
//Exemplo apenas do socket
//-----------------------------------------------
/*
socket socketTest;
void read(){
    socketTest.readMessage();
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Criando um socket da classe "socket"

        //Fixando qual o IP e porta que o módulo wifi está configurado
        QString IP = "127.0.0.1";     //Fixei o IP do módulo wifi nisso
        int port = 7009;                    //Fixei o port que está sendo usado nisso
        socketTest.setIP(IP);
        socketTest.setPort(port);

    //Inicia conexão
    socketTest.doConnect();
    QObject::connect(&socketTest,&socket::canRead,read());
    //Criei dois métodos para enviar dados, com array e strings
    //Ambos funcionam, mas strings podem ser mais fáceis de trabalhar
    char *data_array = "Teste array\n";
    string data_string = "Teste string\n";
    socketTest.writeMessage(data_array);
    socketTest.writeMessage(data_string);

    socketTest.readMessage();

    //Percebi um "problema" ao mandar muitos dados para o ESP
    //Um pacote grande (5025 bytes) é separado em vários pacotes menores
    //A conexão não é fechada, só são mandados separadamente
    //Talvez seja uma funcionalidade do próprio TCP, mas vale lembrar

    for(int i=0;i<10;i++){
        socketTest.writeMessage("RUN \n");
    }


    //Disconecta a conexão
    //socketTest.disconnect();
    return a.exec();
}
*/
