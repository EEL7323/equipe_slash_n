#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "socket.h"
#include <QDebug>
#include <string>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonConnect_clicked();
    void on_button_send_clicked();
    void on_received_data();

private:
    socket* app_socket;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
