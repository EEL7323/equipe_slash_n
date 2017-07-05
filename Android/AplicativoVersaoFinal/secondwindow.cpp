#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}

void SecondWindow::SecondConstructor()
{
    QString aux;
    aux.setNum(aluno.getCreditsCard(),'g', 4);
    ui->labelCreditsCard->setText(aux);
    aux.setNum(aluno.getCreditsMobile(),'g', 4);
    ui->labelCreditsMobile->setText(aux);
    ui->labelRUUser->setText("?");
    ui->warningLabelRU->clear();

    registerCard = new CardInfo(this);
    addCreditsMobile = new AddCredits(this, int(aluno.getMatricula()));
    addCreditsCard = new AddCredits(this, int(aluno.getMatricula()));
    appInfo = new ExtraInfo(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_toolButton_clicked()
{
    if(!registerCard->isVisible()){
        registerCard->show();
    }
}

void SecondWindow::on_pushButton_clicked()
{
    if(!addCreditsMobile->isVisible() ){
        addCreditsMobile->setIsCard(false);
        addCreditsMobile->setCartao(getCard());
        addCreditsMobile->show();
        QString Error;
        bool ErrorOccurs;
        aluno = socket.SearchAluno(aluno.getMatricula(), &Error, ErrorOccurs);
        SecondConstructor();
    }
}

void SecondWindow::on_pushButton_2_clicked()
{
    if(!addCreditsCard->isVisible()){
        addCreditsCard->setIsCard(true);
        addCreditsCard->setCartao(getCard());
        addCreditsCard -> show();
        QString Error;
        bool ErrorOccurs;
        aluno = socket.SearchAluno(aluno.getMatricula(), &Error, ErrorOccurs);
        SecondConstructor();
    }
}

void SecondWindow::on_toolButton_2_clicked()
{
    if(appInfo->isVisible()){
        appInfo -> hide();
    }else{
        appInfo -> show();
    }
}

CardData SecondWindow::getCard()
{
    return cartao;
}

void SecondWindow::setCard(CardData cardAux)
{
    cartao.setCardNumber(cardAux.getCardNumber());
    cartao.setMonthDeadline(cardAux.getMonthDeadline());
    cartao.setYearDeadline(cardAux.getYearDeadline());
    cartao.setSafeCard(cardAux.getSafeCard());
}

void SecondWindow::setLedInput(int aux)
{
    ledInput = aux;
}

void SecondWindow::setAluno(AlunoApp aux)
{
    aluno = aux;
}

int SecondWindow::getLedInput()
{
    return ledInput;
}

AlunoApp SecondWindow::getAluno()
{
    return aluno;
}

void SecondWindow::on_pushButton_3_clicked()
{
    bool ledInputAux [6];
    int i = 0, ledAux2 = 0;

    ledInputAux[0] = ui->LED0->isChecked();
    ledInputAux[1] = ui->LED1->isChecked();
    ledInputAux[2] = ui->LED2->isChecked();
    ledInputAux[3] = ui->LED3->isChecked();
    ledInputAux[4] = ui->LED4->isChecked();
    ledInputAux[5] = ui->LED5->isChecked();

    for (i = 0; i < 6; )
    {
        int aux = pow(2,i) ;
        ledAux2 += (int(ledInputAux[i])*aux);
        i++;
    }

    setLedInput(ledAux2);

    QString Error;
    bool ok;
    ui->labelRUUser->setText(QString::number(socketESP.requestOccupants()));
    socketESP.requestAccess(aluno.getMatricula(), getLedInput(), &Error, ok);

    if(ok != true)
    {
        aluno.setCreditsMobile(aluno.getCreditsMobile()-1.5);
        ui->warningLabelRU->clear();
        QString aux;
        aux.setNum(aluno.getCreditsMobile(),'g', 4);
        ui->labelCreditsMobile->setText(aux);
    }
    else{
        ui->warningLabelRU->setText("Algo deu errado!");
    }

}
