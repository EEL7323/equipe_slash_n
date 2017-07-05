#ifndef ADDCREDITS_H
#define ADDCREDITS_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include "sockettcpru.h"
#include "alunoapp.h"
#include "carddata.h"

namespace Ui {
class AddCredits;
}

class AddCredits : public QDialog
{
    Q_OBJECT

public:
    explicit AddCredits(QWidget *parent = 0, int matriculaAux = 0);
    ~AddCredits();
    void setAmount(float amountAux);
    void setIsCard(bool aux);
    void setCartao (CardData aux);
    void setMatricula(int);

    float getAmount(void);
    CardData getCartao(void);
    bool getIsCard(void);

    AlunoApp aluno;
    SocketTcpRU socket;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_lineAmount_returnPressed();

private:
    int matricula;
    CardData cartao;
    bool isCard;
    float amount;
    Ui::AddCredits *ui;

};

#endif // ADDCREDITS_H
