#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <netinet/in.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLoginButton();
    void handleLogoutButton();
    void handleReceiveButton();
    void handleSignupButton();
    int establishConnection(int client_sock, struct sockaddr* server_addr, socklen_t addr_len);


private:
    Ui::MainWindow *ui;
    int client_sock;
    struct sockaddr_in server_addr;
    bool isLogin;
};

#endif // MAINWINDOW_H
