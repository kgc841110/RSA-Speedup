/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Dec 19 15:53:46 2021
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *key_pushButton;
    QTextEdit *origin_textEdit;
    QTextEdit *crt_textEdit;
    QTextEdit *new_textEdit;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *p_textEdit;
    QLabel *label_3;
    QTextEdit *c_textEdit;
    QLabel *label_4;
    QPushButton *enc_pushButton;
    QLabel *label_5;
    QPushButton *dec1_pushButton;
    QPushButton *dec2_pushButton;
    QPushButton *dec3_pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(874, 496);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        key_pushButton = new QPushButton(centralWidget);
        key_pushButton->setObjectName(QString::fromUtf8("key_pushButton"));
        key_pushButton->setGeometry(QRect(740, 20, 111, 51));
        origin_textEdit = new QTextEdit(centralWidget);
        origin_textEdit->setObjectName(QString::fromUtf8("origin_textEdit"));
        origin_textEdit->setGeometry(QRect(10, 190, 261, 171));
        crt_textEdit = new QTextEdit(centralWidget);
        crt_textEdit->setObjectName(QString::fromUtf8("crt_textEdit"));
        crt_textEdit->setGeometry(QRect(300, 190, 261, 171));
        new_textEdit = new QTextEdit(centralWidget);
        new_textEdit->setObjectName(QString::fromUtf8("new_textEdit"));
        new_textEdit->setGeometry(QRect(590, 190, 261, 171));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 370, 191, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(360, 370, 181, 31));
        p_textEdit = new QTextEdit(centralWidget);
        p_textEdit->setObjectName(QString::fromUtf8("p_textEdit"));
        p_textEdit->setGeometry(QRect(100, 10, 261, 171));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(380, 70, 71, 51));
        c_textEdit = new QTextEdit(centralWidget);
        c_textEdit->setObjectName(QString::fromUtf8("c_textEdit"));
        c_textEdit->setGeometry(QRect(450, 10, 261, 171));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 70, 71, 51));
        enc_pushButton = new QPushButton(centralWidget);
        enc_pushButton->setObjectName(QString::fromUtf8("enc_pushButton"));
        enc_pushButton->setGeometry(QRect(740, 110, 111, 51));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(640, 370, 181, 31));
        dec1_pushButton = new QPushButton(centralWidget);
        dec1_pushButton->setObjectName(QString::fromUtf8("dec1_pushButton"));
        dec1_pushButton->setGeometry(QRect(80, 410, 111, 31));
        dec2_pushButton = new QPushButton(centralWidget);
        dec2_pushButton->setObjectName(QString::fromUtf8("dec2_pushButton"));
        dec2_pushButton->setGeometry(QRect(370, 410, 111, 31));
        dec3_pushButton = new QPushButton(centralWidget);
        dec3_pushButton->setObjectName(QString::fromUtf8("dec3_pushButton"));
        dec3_pushButton->setGeometry(QRect(680, 410, 111, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 874, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        key_pushButton->setText(QApplication::translate("MainWindow", "\354\227\264\354\207\240\354\203\235\354\204\261", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\353\263\265\355\230\270\353\254\270(\354\233\220\353\236\230 \353\260\251\354\213\235)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\353\263\265\355\230\270\353\254\270(CRT\353\260\251\354\213\235)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\354\225\224\355\230\270\353\254\270", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "\355\217\211\353\254\270", 0, QApplication::UnicodeUTF8));
        enc_pushButton->setText(QApplication::translate("MainWindow", "\354\225\224\355\230\270\355\231\224", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\353\263\265\355\230\270\353\254\270(\354\203\210 \353\260\251\354\213\235)", 0, QApplication::UnicodeUTF8));
        dec1_pushButton->setText(QApplication::translate("MainWindow", "\353\263\265\355\230\270\355\231\2241", 0, QApplication::UnicodeUTF8));
        dec2_pushButton->setText(QApplication::translate("MainWindow", "\353\263\265\355\230\270\355\231\2242", 0, QApplication::UnicodeUTF8));
        dec3_pushButton->setText(QApplication::translate("MainWindow", "\353\263\265\355\230\270\355\231\2243", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
