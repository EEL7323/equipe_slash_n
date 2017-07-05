#include "cardinfo.h"
#include "ui_cardinfo.h"

CardInfo::CardInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardInfo)
{
    ui->setupUi(this);
    ui->lineWarning->clear();
}

CardInfo::~CardInfo()
{
    delete ui;
}
void CardInfo::on_pushButton_2_clicked()
{
    CardData cartaoAux;
    QString storeAux;

    //Salvando dados do cartão
    bool okMesAux, okYearAux, okSafeAux;

    storeAux = ui->lineCardNumber->text();
    cartaoAux.setCardNumber(storeAux.toStdString().c_str());

    storeAux = ui->lineValidMonth->text();
    cartaoAux.setMonthDeadline(storeAux.toShort(&okMesAux,10));
    if((cartaoAux.getMonthDeadline() == 0) || (cartaoAux.getMonthDeadline() > 12))
    {
        okMesAux = false;
    }

    storeAux = ui->lineValidYear->text();
    cartaoAux.setYearDeadline(storeAux.toShort(&okYearAux,10));
    if(cartaoAux.getYearDeadline() > 99)
    {
        okYearAux = false;
    }

    storeAux = ui->lineSafeCode->text();
    cartaoAux.setSafeCard(storeAux.toShort(&okSafeAux,10));
    if(cartaoAux.getSafeCard() > 999)
    {
        okSafeAux = false;
    }

    if (okMesAux && okYearAux && okSafeAux)
    {
        hide();
    } else{
        ui->lineWarning->setText("Você digitou algo errado!");
    }

}

void CardInfo::on_pushButton_clicked()
{
    hide();
}

CardData CardInfo::getCard()
{
    return cartao;
}

void CardInfo::setCard(CardData cardAux)
{
    cartao.setCardNumber(cardAux.getCardNumber());
    cartao.setMonthDeadline(cardAux.getMonthDeadline());
    cartao.setYearDeadline(cardAux.getYearDeadline());
    cartao.setSafeCard(cardAux.getSafeCard());
}

void CardInfo::on_lineCardNumber_returnPressed()
{
}
