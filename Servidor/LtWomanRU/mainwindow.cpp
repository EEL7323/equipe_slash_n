#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonSearch_clicked()
{
    QString Error;
    bool ErrorOccurs;

    aluno = socket.SearchAluno(ui->EditMatricula->text().toInt(), &Error, ErrorOccurs);

    if (ErrorOccurs)
    {
        QMessageBox::warning(0, qApp->tr("Aluno nao encontrado!"),
            QString("Tal coleguinha nao esta no banco de dados.\n\n\n"
                     "DataBase responde: %1!.. " "\n\n\n"
                     "Click Cancel to exit.").arg(Error), QMessageBox::Cancel);
    } else
    {
        ui->LabelNome->setText(QString("Nome:     %1").arg(aluno.getNome()));
        ui->LabelCartao->setText(QString("Saldo Cartão:  R$ %1").arg(QString::number(aluno.getcreditsCard(),'f', 2)));
        ui->LabelMovel->setText(QString("Saldo Movel:   R$ %1").arg(QString::number(aluno.getcreditsMobile(),'f', 2)));

        ui->EditNome->setText("0.00");
        ui->ButtonSalvar->setEnabled(false);
        ui->radioCartao->setCheckable(false);
        ui->radioMovel->setCheckable(false);
        ui->radioCartao->setChecked(false);
        ui->radioMovel->setChecked(false);
        ui->radioCartao->setCheckable(true);
        ui->radioMovel->setCheckable(true);
        ui->groupBox->setVisible(true);
    }

}

void MainWindow::on_ButtonSalvar_clicked()
{
    QString Informative;
    float credito = ui->EditNome->text().toFloat();
    if (credito == 0)
    {
        QMessageBox::warning(0, qApp->tr("Valor inadequado"),
            QString("Coloque um valor que faça sentido.\n\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    if (ui->radioCartao->isChecked() && ui->radioCartao->isChecked())
        Informative = QString("Voce estará adicionando creditos no dispositivo Movel e no Cartão do %1.\n\n\n "
                              "Valor a ser creditado: R$ %2"
                              "Clique em Salvar para adicionar os creditos.").arg(aluno.getNome()).arg(2*credito);
    else if (ui->radioCartao->isChecked())
        Informative = QString("Voce estará adicionando creditos Cartão do %1.\n\n\n "
                              "Valor a ser creditado: R$ %2"
                              "Clique em Salvar para adicionar os creditos.").arg(aluno.getNome()).arg(credito);
    else
        Informative = QString("Voce estará adicionando creditos no dispositivo Movel do %1.\n\n\n "
                              "Valor a ser creditado: R$ %2\n\n\n\n"
                              "Clique em Salvar para adicionar os creditos.").arg(aluno.getNome()).arg(credito);

    QMessageBox askbox;
    askbox.setText(QString("Será adicionado Creditos ao %1").arg(aluno.getNome()));
    askbox.setInformativeText(Informative);
    askbox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    askbox.setDefaultButton(QMessageBox::Cancel);
    int ret = askbox.exec();

    if (ret == QMessageBox::Save)
    {
        if (ui->radioCartao->isChecked())
            aluno.setcreditsCard(aluno.getcreditsCard() + credito);

        if (ui->radioMovel->isChecked())
            aluno.setcreditsMobile(aluno.getcreditsMobile() + credito);

        QString Error;
        bool flagError = !socket.updateAluno(aluno, &Error);

        if (flagError)
        {
            QMessageBox::warning(0, qApp->tr("Não foi possível adicionar os creditos!"),
                QString("%1.\n\n\n"
                        "Click Cancel to exit.").arg(Error), QMessageBox::Cancel);

            return;
        } else
        {
            QMessageBox::warning(0, qApp->tr("Creditos adicionados corretamente!"),
                QString("Deu tudo certo!\n"
                         "\n\n\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);

        }

        ui->groupBox->setVisible(false);
    }

}

void MainWindow::on_ButtonSalvar_2_clicked()
{
    ui->groupBox->setVisible(false);
}

void MainWindow::on_radioMovel_clicked()
{
    if (ui->radioCartao->isChecked() || ui->radioMovel->isChecked())
        ui->ButtonSalvar->setEnabled(true);
    else
        ui->ButtonSalvar->setEnabled(false);
}

void MainWindow::on_radioCartao_clicked()
{
    if (ui->radioCartao->isChecked() || ui->radioMovel->isChecked())
        ui->ButtonSalvar->setEnabled(true);
    else
        ui->ButtonSalvar->setEnabled(false);
}
