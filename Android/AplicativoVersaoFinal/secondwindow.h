#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAbstractButton>
#include "cardinfo.h"
#include "carddata.h"
#include "addcredits.h"
#include "alunoapp.h"
#include "extrainfo.h"
#include "sockettcpru.h"
#include "socketesp.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = 0);
    ~SecondWindow();

    CardData getCard();
    SocketTcpRU socket;
    SocketESP socketESP;

    void SecondConstructor();
    void setCard(CardData cardAux);
    void setLedInput(int aux);
    void setAluno(AlunoApp aux);

    int getLedInput(void);
    AlunoApp getAluno(void);
    Ui::SecondWindow *ui;

protected:
    CardInfo *registerCard;
    AddCredits *addCreditsMobile;
    AddCredits *addCreditsCard;
    ExtraInfo *appInfo;

public slots:
    void on_toolButton_clicked();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    CardData cartao;
    int ledInput;
    AlunoApp aluno;

};

#endif // SECONDWINDOW_H
