/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *logoutButton;
    QPushButton *receiveButton;
    QPushButton *signupButton;
    QTextEdit *outputTextEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 61, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 70, 61, 16));
        usernameLineEdit = new QLineEdit(centralwidget);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setGeometry(QRect(90, 30, 113, 20));
        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(90, 70, 113, 20));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(20, 110, 75, 23));
        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(110, 110, 75, 23));
        receiveButton = new QPushButton(centralwidget);
        receiveButton->setObjectName("receiveButton");
        receiveButton->setGeometry(QRect(200, 110, 75, 23));
        signupButton = new QPushButton(centralwidget);
        signupButton->setObjectName("signupButton");
        signupButton->setGeometry(QRect(290, 110, 75, 23));
        outputTextEdit = new QTextEdit(centralwidget);
        outputTextEdit->setObjectName("outputTextEdit");
        outputTextEdit->setGeometry(QRect(20, 150, 361, 131));
        outputTextEdit->setReadOnly(true);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Client", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        receiveButton->setText(QCoreApplication::translate("MainWindow", "Receive", nullptr));
        signupButton->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
