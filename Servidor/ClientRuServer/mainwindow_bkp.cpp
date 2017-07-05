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
    AlunoServer aluno;

    aluno = socket.SearchAluno(ui->EditMatricula->text().toInt());

    ui->EditMatricula->setText(QString("%1").arg(aluno.getMatricula()));
    ui->EditNome->setText(aluno.getNome());
    ui->EditCartao->setText(QString("%1").arg(aluno.getcreditsCard()));
    ui->EditMovel->setText(QString("%1").arg(aluno.getcreditsMobile()));
}

void MainWindow::on_pushButton_2_clicked()
{

}
