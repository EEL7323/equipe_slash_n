#ifndef CARDINFO_H
#define CARDINFO_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include "CardData.h"

namespace Ui {
class CardInfo;
}

class CardInfo : public QDialog
{
    Q_OBJECT

public:
    explicit CardInfo(QWidget *parent = 0);
    ~CardInfo();

    CardData getCard();
    void setCard(CardData cardAux);
private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineCardNumber_returnPressed();

private:
    Ui::CardInfo *ui;
    CardData cartao;
};

#endif // CARDINFO_H
