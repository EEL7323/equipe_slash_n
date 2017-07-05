/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLineEdit *EditMatricula;
    QLabel *label_2;
    QLineEdit *EditNome;
    QLabel *label_3;
    QLineEdit *EditCartao;
    QLabel *label_4;
    QLineEdit *EditMovel;
    QPushButton *ButtonSearch;
    QPushButton *ButtonSalvar;
    QPushButton *ButtonDeletar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 81, 16));
        EditMatricula = new QLineEdit(centralWidget);
        EditMatricula->setObjectName(QStringLiteral("EditMatricula"));
        EditMatricula->setGeometry(QRect(20, 30, 113, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 81, 16));
        EditNome = new QLineEdit(centralWidget);
        EditNome->setObjectName(QStringLiteral("EditNome"));
        EditNome->setGeometry(QRect(20, 80, 113, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 110, 81, 16));
        EditCartao = new QLineEdit(centralWidget);
        EditCartao->setObjectName(QStringLiteral("EditCartao"));
        EditCartao->setGeometry(QRect(20, 130, 113, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 160, 81, 16));
        EditMovel = new QLineEdit(centralWidget);
        EditMovel->setObjectName(QStringLiteral("EditMovel"));
        EditMovel->setGeometry(QRect(20, 180, 113, 20));
        ButtonSearch = new QPushButton(centralWidget);
        ButtonSearch->setObjectName(QStringLiteral("ButtonSearch"));
        ButtonSearch->setGeometry(QRect(220, 30, 75, 23));
        ButtonSalvar = new QPushButton(centralWidget);
        ButtonSalvar->setObjectName(QStringLiteral("ButtonSalvar"));
        ButtonSalvar->setGeometry(QRect(220, 60, 75, 23));
        ButtonDeletar = new QPushButton(centralWidget);
        ButtonDeletar->setObjectName(QStringLiteral("ButtonDeletar"));
        ButtonDeletar->setGeometry(QRect(220, 90, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Matricula", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Nome", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Saldo Cartao", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Saldo Movel", Q_NULLPTR));
        ButtonSearch->setText(QApplication::translate("MainWindow", "Procurar", Q_NULLPTR));
        ButtonSalvar->setText(QApplication::translate("MainWindow", "Salvar", Q_NULLPTR));
        ButtonDeletar->setText(QApplication::translate("MainWindow", "Deletar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
