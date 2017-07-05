#include "addcredits.h"
#include "ui_addcredits.h"

AddCredits::AddCredits(QWidget *parent, int matriculaAux) :
    QDialog(parent),
    ui(new Ui::AddCredits)
{
    ui->setupUi(this);
    ui->lineAmount->setMaxLength(16);

    int *left = 0, *top = 0, *bottom = 0, *right = 0;
    int *leftContents = 0, *topContents = 0, *rightContents = 0, *bottomContents = 0;
    QFontMetrics fm(font());

    ui->lineAmount->getContentsMargins(leftContents, topContents, rightContents, bottomContents);
    ui->lineAmount->getTextMargins(left, top, right, bottom);

    int T = qMax(fm.height(), 14);
    int h = T;

    //ui->lineAmount->setMinimumHeight(h);
    ui->lineWarning->clear();
    matricula = matriculaAux;
}

AddCredits::~AddCredits()
{
    delete ui;
}

void AddCredits::setAmount(float amountAux)
{
    amount = amountAux;
}

void AddCredits::setIsCard(bool aux)
{
    isCard = aux;
}

void AddCredits::setCartao(CardData aux)
{
    cartao = aux;
}

float AddCredits::getAmount()
{
    return amount;
}

CardData AddCredits::getCartao()
{
    return cartao;
}

bool AddCredits::getIsCard()
{
    return isCard;
}

void AddCredits::on_okButton_clicked()
{
    QString storeAux = ui->lineAmount->text();
    bool ok;
    float amountAux = storeAux.toFloat(&ok);
    if(ok && (amountAux > 0)){
        setAmount(amountAux);
        QDialog::hide();

        QString Error;
        if(getIsCard() == false)
        {
            socket.addCreditMobile(matricula, getAmount(), cartao, &Error);
        } else
        {
            socket.addCreditCard(matricula, getAmount(), cartao, &Error);
        }
    } else {
        ui->lineWarning->setText("O valor deve ser como: 10.50, maior do que 0");
    }
}

void AddCredits::setMatricula(int aux)
{
    matricula = aux;
}

void AddCredits::on_cancelButton_clicked()
{
    QDialog::hide();
}

void AddCredits::on_lineAmount_returnPressed()
{
    AddCredits::on_okButton_clicked();
}
