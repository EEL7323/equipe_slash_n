#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "cardinfo.h"
#include "addcredits.h"
#include "extrainfo.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = 0);
    ~SecondWindow();

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

private:
    Ui::SecondWindow *ui;
};

#endif // SECONDWINDOW_H
