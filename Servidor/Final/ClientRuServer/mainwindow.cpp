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

//void MainWindow::on_ButtonProcurar_clicked()
//{
//    AlunoServer aluno;

//    aluno = socket.SearchAluno(ui->EditMatricula->text().toInt());

//    ui->EditMatricula->setText(QString("%1").arg(aluno.getMatricula()));
//    ui->EditNome->setText(aluno.getNome());
//    ui->EditCartao->setText(QString("%1").arg(aluno.getcreditsCard()));
//    ui->EditMovel->setText(QString("%1").arg(aluno.getcreditsMobile()));

//}


//void MainWindow::on_ButtonProcurar_clicked()
//{
//    AlunoServer aluno;

//    QString Error;
//    bool ErrorOccurs;

//    aluno = socket.SearchAluno(ui->EditMatricula->text().toInt(), &Error, ErrorOccurs);

//    if (ErrorOccurs)
//    {
//        QMessageBox::warning(0, qApp->tr("Aluno nao encontrado!"),
//            QString("Tal coleguinha nao esta no banco de dados.\n\n\n"
//                     "DataBase responde: %1!.. " "\n\n\n"
//                     "Click Cancel to exit.").arg(Error), QMessageBox::Cancel);
//    } else
//    {
//        ui->EditMatricula->setText(QString("%1").arg(aluno.getMatricula()));
//        ui->EditNome->setText(aluno.getNome());
//        ui->EditCartao->setText(QString("%1").arg(aluno.getcreditsCard()));
//        ui->EditMovel->setText(QString("%1").arg(aluno.getcreditsMobile()));
//    }
//}

void MainWindow::on_ButtonSearch_clicked()
{
    AlunoServer aluno;
    QString Error;
    bool ErrorOccurs;

    aluno = socket.SearchAluno(ui->EditMatricula->text().toInt(), &Error, ErrorOccurs);

    if (ErrorOccurs)
    {
        QMessageBox::warning(0, qApp->tr("Aluno nao encontrado!"),
            QString("Tal coleguinha nao esta no banco de dados.\n\n\n"
                     "DataBase responde: %1!.. " "\n\n\n"
                     "Click Cancel to exit.").arg(Error), QMessageBox::Cancel);
        ui->EditNome->setText("");
        ui->EditCartao->setText("");
        ui->EditMovel->setText("");
    } else
    {
        ui->EditMatricula->setText(QString("%1").arg(aluno.getMatricula()));
        ui->EditNome->setText(aluno.getNome());
        ui->EditCartao->setText(QString("%1").arg(aluno.getcreditsCard()));
        ui->EditMovel->setText(QString("%1").arg(aluno.getcreditsMobile()));
        ui->EditSenha->setText(QString("%1").arg(aluno.getSenha()));
    }

}

void MainWindow::on_ButtonSalvar_clicked()
{
    AlunoServer aluno;

    aluno.setNome(ui->EditNome->text());
    aluno.setMatricula(ui->EditMatricula->text().toULong());
    aluno.setcreditsMobile(ui->EditMovel->text().toFloat());
    aluno.setcreditsCard(ui->EditCartao->text().toFloat());
    aluno.setSenha(ui->EditSenha->text());

    QString Error;
    bool flagError;
    flagError = !socket.AddAluno(aluno, &Error);
    if (flagError)
        flagError = !socket.updateAluno(aluno, &Error);

    if (flagError)
    {
        QMessageBox::warning(0, qApp->tr("Não foi possivel adiciona-lo!"),
            QString("Não foi possivel adiciona-lo! Nao sei pq... .\n\n\n"
                     "DataBase respondeu: %1!.. " "\n\n\n"
                     "Click Cancel to exit.").arg(Error), QMessageBox::Cancel);

    } else
    {
        QMessageBox::warning(0, qApp->tr("Aluno adicionado corretamente!"),
            QString("Deu tudo certo!\n"
                     "\n\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_ButtonDeletar_clicked()
{
    QString Error;
    bool flagError;
    flagError = !socket.delAluno(ui->EditMatricula->text().toULong(), &Error);

    if (flagError)
    {
        QMessageBox::warning(0, qApp->tr("Não foi possivel deleta-lo!"),
            QString("Tal coleguinha ja esta no banco de dados.\n\n\n"
                     "DataBase responde: %1!.. " "\n\n\n"
                     "Click Cancel to exit.").arg(Error), QMessageBox::Cancel);

    } else
    {
        QMessageBox::warning(0, qApp->tr("Aluno deletado!"),
            QString("Deu tudo certo!\n"
                     "\n\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);

    }
}
