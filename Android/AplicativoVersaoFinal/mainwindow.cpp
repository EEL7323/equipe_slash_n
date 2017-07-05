#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Salvando as entradas de texto
    QString storeAux = ui->lineEdit->text();
    bool okAux1, okAux2;
    this->setMatriculaDigitada(storeAux.toULong(&okAux1, 10));

    storeAux = ui->lineEdit_2->text();
    this->setSenhaDigitada(storeAux);

    QString errorSearch;
    bool errorAux;
    //UNCOMMENT
    AlunoApp alunoAux = socket.SearchAluno(int(matriculaDigitada), &errorSearch, errorAux);

    if (errorAux == false)
    {
        //COMMENT
        //AlunoApp alunoAux;
        //alunoAux.setMatricula(14101336);
        //alunoAux.setCreditsCard(10.55);
        //alunoAux.setSenha("senha");
        aluno = alunoAux;
    } else {
        QMessageBox::warning(0, qApp->tr("Aluno nao encontrado!"),
                    QString("Tal coleguinha nao esta no banco de dados.\n\n\n"
                             "DataBase responde: %1!.. " "\n\n\n"
                             "Click Cancel to exit.").arg(errorSearch), QMessageBox::Cancel);
    }


    if(this->checkLogin()){
        //Abrindo a nova janela
        loggedWindow =  new SecondWindow(this);
        loggedWindow -> setAluno(aluno);
        loggedWindow -> SecondConstructor();
        loggedWindow -> showMaximized();
    }
}

void MainWindow::getAluno(AlunoApp alunoAux)
{
    aluno = alunoAux;
}

void MainWindow::setSenhaDigitada(QString senhaAux)
{
    senhaDigitada = senhaAux;
}

void MainWindow::setMatriculaDigitada(ulong matriculaAux)
{
    matriculaDigitada = matriculaAux;
}

ulong MainWindow::getMatriculaDigitada()
{
    return matriculaDigitada;
}

QString MainWindow::getSenhaDigitada()
{
    return senhaDigitada;
}

bool MainWindow::checkLogin()
{
    bool returnAux, condSenha, condMatricula;


    condSenha = (QString::compare(senhaDigitada, aluno.getSenha()) == 0);
    condMatricula = (matriculaDigitada == aluno.getMatricula());

    if ( condSenha && condMatricula )
        returnAux = true;
    else
        returnAux = false;

    return returnAux;
}
