#include "extrainfo.h"
#include "ui_extrainfo.h"

ExtraInfo::ExtraInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExtraInfo)
{
    ui->setupUi(this);
}

ExtraInfo::~ExtraInfo()
{
    delete ui;
}

void ExtraInfo::on_pushButton_clicked()
{
    hide();
}
