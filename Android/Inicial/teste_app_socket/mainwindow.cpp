#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    app_socket = new socket();
    QObject::connect(&(*app_socket),socket::SIGNAL_socket_received_data,this,on_received_data);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonConnect_clicked()
{
    app_socket->setIP("192.168.100.13");
    app_socket->setPort(7009);
    app_socket->start_connection();
    if(app_socket->getConnectionStatus() == true){
        ui->label->setText("Connected");
    }
    else{
        ui->label->setText("Not connected");
    }
}

void MainWindow::on_button_send_clicked()
{
    //app_socket->start_connection();
    QString data = ui->line_data->text();
    string data_string = data.toStdString();
    app_socket->writeMessage(data_string);
}

void MainWindow::on_received_data(){
    qDebug() << app_socket->readMessage();
}
