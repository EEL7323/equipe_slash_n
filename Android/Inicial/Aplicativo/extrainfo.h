#ifndef EXTRAINFO_H
#define EXTRAINFO_H

#include <QDialog>

namespace Ui {
class ExtraInfo;
}

class ExtraInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ExtraInfo(QWidget *parent = 0);
    ~ExtraInfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ExtraInfo *ui;
};

#endif // EXTRAINFO_H
