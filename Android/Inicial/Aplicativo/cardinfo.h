#ifndef CARDINFO_H
#define CARDINFO_H

#include <QDialog>

namespace Ui {
class CardInfo;
}

class CardInfo : public QDialog
{
    Q_OBJECT

public:
    explicit CardInfo(QWidget *parent = 0);
    ~CardInfo();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::CardInfo *ui;

};

#endif // CARDINFO_H
