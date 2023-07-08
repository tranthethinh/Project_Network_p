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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QLineEdit *usernameLineEdit;
    QLabel *label_2;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *signupButton;
    QTextEdit *outputTextEdit;
    QWidget *page_2;
    QPushButton *logoutButton;
    QPushButton *receiveButton;
    QWidget *page_3;
    QTextEdit *TextQuestion;
    QPushButton *backButton;
    QPushButton *nextQues;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(430, 538);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 20, 391, 511));
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 110, 91, 16));
        usernameLineEdit = new QLineEdit(page);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setGeometry(QRect(120, 110, 151, 20));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 150, 71, 16));
        passwordLineEdit = new QLineEdit(page);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(120, 150, 151, 21));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(page);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(70, 220, 75, 23));
        signupButton = new QPushButton(page);
        signupButton->setObjectName("signupButton");
        signupButton->setGeometry(QRect(210, 220, 75, 23));
        outputTextEdit = new QTextEdit(page);
        outputTextEdit->setObjectName("outputTextEdit");
        outputTextEdit->setGeometry(QRect(0, 330, 381, 131));
        outputTextEdit->setReadOnly(true);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        logoutButton = new QPushButton(page_2);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(150, 190, 75, 23));
        receiveButton = new QPushButton(page_2);
        receiveButton->setObjectName("receiveButton");
        receiveButton->setGeometry(QRect(150, 120, 75, 23));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        TextQuestion = new QTextEdit(page_3);
        TextQuestion->setObjectName("TextQuestion");
        TextQuestion->setGeometry(QRect(50, 60, 291, 301));
        backButton = new QPushButton(page_3);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(10, 10, 89, 25));
        nextQues = new QPushButton(page_3);
        nextQues->setObjectName("nextQues");
        nextQues->setGeometry(QRect(160, 410, 89, 25));
        stackedWidget->addWidget(page_3);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Client", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        signupButton->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        receiveButton->setText(QCoreApplication::translate("MainWindow", "Receive", nullptr));
        backButton->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        nextQues->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
