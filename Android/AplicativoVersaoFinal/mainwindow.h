#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>
#include "alunoapp.h"
#include "secondwindow.h"
#include "sockettcpru.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    AlunoApp aluno;

    void getAluno(AlunoApp alunoAux);
    void setSenhaDigitada(QString senhaAux);
    void setMatriculaDigitada(ulong matriculaAux);
    ulong getMatriculaDigitada();
    QString getSenhaDigitada();

    bool checkLogin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    SecondWindow *loggedWindow;
    SocketTcpRU socket;
    QString senhaDigitada;
    ulong matriculaDigitada;
};

#endif // MainWindow_H
