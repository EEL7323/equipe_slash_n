#include "addcredits.h"
#include "ui_addcredits.h"

AddCredits::AddCredits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCredits)
{
    ui->setupUi(this);
}

AddCredits::~AddCredits()
{
    delete ui;
}

void AddCredits::on_pushButton_2_clicked()
{
    hide();
}

void AddCredits::on_pushButton_clicked()
{
    hide();
}
