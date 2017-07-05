#include "cardinfo.h"
#include "ui_cardinfo.h"

CardInfo::CardInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardInfo)
{
    ui->setupUi(this);
}

CardInfo::~CardInfo()
{
    delete ui;
}
void CardInfo::on_pushButton_2_clicked()
{
    hide();
}

void CardInfo::on_pushButton_clicked()
{
    hide();
}
