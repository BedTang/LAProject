#ifndef TCP_HANDLE_H
#define TCP_HANDLE_H

#include "ui_main_form.h"
#include <QWidget>

// TCP
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>

class TcpHandle : public QWidget
{
    Q_OBJECT
public:
    TcpHandle(QWidget *parent = nullptr ,Ui::MainForm *ui_ = nullptr);
    void RetrieveNativeIp();
    // QString serverReadData();
    void ServerListening(bool &status ,int port);
    int GetPort();
    QHostAddress GetIp();
    QString GetMessage();

private:
    // TCP
    QTcpServer *tcp_server_ = new QTcpServer();
    QTcpSocket *tcp_client_= new QTcpSocket();
    QTcpSocket *current_client_= new QTcpSocket();

    QList<QTcpSocket*> tcp_client_list_;

    QString current_client_msg_;

    Ui::MainForm *ui_;

private slots:
    void NewConnectionSlot();
    void DisconnectedSlot();
    void ReadServerData();

signals:
    void RequestAddDevice(QHostAddress);
    void RequestDataHandle(QString);
};
#endif // TCP_HANDLE_H
