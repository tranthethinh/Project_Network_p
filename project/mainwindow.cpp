#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::handleLoginButton);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::handleLogoutButton);
    connect(ui->receiveButton, &QPushButton::clicked, this, &MainWindow::handleReceiveButton);
    connect(ui->signupButton, &QPushButton::clicked, this, &MainWindow::handleSignupButton);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::handleBackButton);
    //Step 1: Construct socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);

    //Step 2: Specify server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    //Step 3: Request to connect server
    if (establishConnection(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0) {
        ui->outputTextEdit->append("Error! Can not connect to server! Client exit immediately!");
        return;
    }

    isLogin = false;
}
int MainWindow::establishConnection(int client_sock, struct sockaddr* server_addr, socklen_t addr_len)
{
    return ::connect(client_sock, server_addr, addr_len);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleLoginButton()
{
    int choice =1;

    if (isLogin) {
        ui->outputTextEdit->append("You are already logged in.");
        return;
    }else if (send(client_sock, &choice, sizeof(choice), 0) == -1) {
        perror("send() failed");
    }

    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Send username and password to server
    QString message = username + " " + password;
    QByteArray byteArray = message.toUtf8();
    const char* buff = byteArray.constData();
    int msg_len = strlen(buff);
    int bytes_sent = send(client_sock, buff, msg_len, 0);
    if (bytes_sent < 0)
        ui->outputTextEdit->append("Error sending data to server.");

    int k; // number received from server to know login results
    int bytes_received = recv(client_sock, &k, sizeof(k), 0);
    if (bytes_received < 0)
        ui->outputTextEdit->append("Error receiving data from server.");
    else if (bytes_received == 0)
        ui->outputTextEdit->append("Connection closed.");

    ui->outputTextEdit->append("Reply from server: ");

    if (k == 1) {
        ui->outputTextEdit->append("OK");
        isLogin = true;
        ui->stackedWidget->setCurrentIndex(1);
    } else if (k == 0) {
        ui->outputTextEdit->append("Account not ready");
    } else if (k == 2) {
        ui->outputTextEdit->append("Not OK");
    }
}
void MainWindow::handleBackButton(){
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}
void MainWindow::handleLogoutButton()
{
    int choice =2;
    if (!isLogin) {
        ui->outputTextEdit->append("You are not logged in.");
        return;
    }else if (send(client_sock, &choice, sizeof(choice), 0) == -1) {
        perror("send() failed");
        }

    isLogin = false;
    ui->outputTextEdit->append("Logged out");
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::handleReceiveButton()
{
    int choice =3;
    if (!isLogin) {
        ui->outputTextEdit->append("You are not logged in.");
        return;
    }else if (send(client_sock, &choice, sizeof(choice), 0) == -1) {
        perror("send() failed");
        }

    char buff[BUFF_SIZE + 1];
    int bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
    if (bytes_received == -1) {
        ui->outputTextEdit->append("Error receiving data from server.");
        return;
    } else if (bytes_received == 0) {
        ui->outputTextEdit->append("Server closed the connection.");
        return;
    }

    buff[bytes_received] = '\0';
    ui->stackedWidget->setCurrentIndex(2);
    ui->TextQuestion->append(QString(buff));
}

void MainWindow::handleSignupButton()
{
    int choice =4;
    if (isLogin) {
        ui->outputTextEdit->append("You are already logged in.");
        return;
    }else if (send(client_sock, &choice, sizeof(choice), 0) == -1) {
        perror("send() failed");
        }

    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Send username and password to server
    QString message = username + " " + password;
    QByteArray byteArray = message.toUtf8();
    const char* buff = byteArray.constData();
    int msg_len = strlen(buff);
    int bytes_sent = send(client_sock, buff, msg_len, 0);
    if (bytes_sent < 0)
        ui->outputTextEdit->append("Error sending data to server.");

    int k; // number received from server to know login results
    int bytes_received = recv(client_sock, &k, sizeof(k), 0);
    if (bytes_received < 0)
        ui->outputTextEdit->append("Error receiving data from server.");
    else if (bytes_received == 0)
        ui->outputTextEdit->append("Connection closed.");

    ui->outputTextEdit->append("Reply from server: ");

    if (k == 1) {
        ui->outputTextEdit->append("Signup OK");
        isLogin = false;
    } else if (k == 0) {
        ui->outputTextEdit->append("Account existed");
    }
}
