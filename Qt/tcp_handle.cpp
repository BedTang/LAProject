#include "tcp_handle.h"
#include "main_form.h"

extern QString GetCurrentStringTime();
extern void DebugOut(QString);

TcpHandle::TcpHandle(QWidget *parent, Ui::MainForm *ui_)
    : QWidget(parent)
    ,ui_(ui_)
{
    connect(tcp_server_, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
}

void TcpHandle::RetrieveNativeIp()
{
    foreach (QNetworkInterface interface,QNetworkInterface::allInterfaces())
    {
        // qDebug()<<interface.humanReadableName();
        // 1. 首先判断是不是以太网，过滤WiFi
        // if ( interface.hardwareAddress())
        //     continue;

        // if (interface.type() != QNetworkInterface::Ethernet)
        //     interface.hardwareAddress();
        //     continue;

        // 通过匹配关键字"VMware"，过滤虚拟网卡
        if (interface.humanReadableName().contains("VMware") || interface.humanReadableName().contains("Virtual"))
            continue;

        if (interface.humanReadableName().contains("WLAN") || interface.humanReadableName().contains("eth0") || interface.humanReadableName().contains("eth1"))
        {
            // 滤掉ipv6地址
            foreach (auto entry ,interface.addressEntries())
            {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)   
                {
                    ui_->logBrowser_->append("本机IP地址："+entry.ip().toString());
                    // ui_->host_ip_box->addItem(entry.ip().toString());
                }
            }
        }
    }
}

void TcpHandle::ReadServerData()
{
    DebugOut("TcpHandle::ReadServerData()<<");
    // 遍历所有客户端
    for(int i=0; i<tcp_client_list_.length(); i++)
    {
        // 对缓冲区消息判定
        QByteArray buffer = tcp_client_list_[i]->readAll();
        if(buffer.isEmpty())
        {
            continue;
        }

        // 缓存消息地址
        static QString ip_port, ip_port_pre;
        ip_port = tr("[%1:%2]:").arg(tcp_client_list_[i]->peerAddress().toString().split("::ffff:")[1])\
                      .arg(tcp_client_list_[i]->peerPort());

        // 若地址与上次消息地址不同，则需显示此次消息的客户端地址
        // if(ip_port != ip_port_pre)
        {
            // ui_->logBrowser->append(ip_port);
            // ui_->logBrowser->insertPlainText(current_client_msg_);
        }
        // 处理接收到的数据
        current_client_msg_= buffer;
        current_client_msg_= current_client_msg_.simplified();
        ui_->logBrowser_->insertPlainText(ip_port+current_client_msg_+"\n");

        DebugOut("ReadServerData()<<Request to add a device.");
        DebugOut("ReadServerData()<<Current ip address:"+tcp_client_list_[i]->peerAddress().toString().split("::ffff:")[1]);
        emit RequestAddDevice(QHostAddress(tcp_client_list_[i]->peerAddress().toString().split("::ffff:")[1])); // Slots -> MainForm::AddDevice()

        // 更新ip_port
        ip_port_pre = ip_port;
    }
}

void TcpHandle::DisconnectedSlot()
{

}

void TcpHandle::ServerListening(bool &status ,int port) // TCP服务器监听（参照）
{
    if(status == false)
    {
        tcp_server_->listen(QHostAddress::Any, port);
        // qDebug()<<tr("服务器地址：")<<tcp_server_->serverAddress();
        // ui_->logBrowser->append(tr("服务器地址：")+tcp_server_->serverAddress().toString());

        DebugOut(QString("监听端口：%0").arg(tcp_server_->serverPort()));
        status = true;
        return;
    }
    if(status == true)
    {
        for(int i=0; i<tcp_client_list_.length(); i++)//断开所有连接
        {
            tcp_client_list_[i]->disconnectFromHost();
            bool ok = tcp_client_list_[i]->waitForDisconnected(1000);
            if(!ok)
            {
                // 处理异常
            }
            tcp_client_list_.removeAt(i);  //从保存的客户端列表中取去除
        }
        tcp_server_->close();     //不再监听端口

        //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
        for(int i=0; i<tcp_client_list_.length(); i++)
        {
            if(tcp_client_list_[i]->state() == QAbstractSocket::UnconnectedState)
            {
                // 删除存储在combox中的客户端信息
                // ui->cbxConnection->removeItem(ui->cbxConnection->findText(tr("%1:%2")
                //                                                               .arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])
                //                                                               .arg(tcpClient[i]->peerPort())));
                // 删除存储在tcpClient列表中的客户端信息
                // tcp_client_list_[i]->destroyed();
                tcp_client_list_.removeAt(i);
            }
        }
        status = false;
        return;
    }
}

int TcpHandle::GetPort()
{
    return tcp_server_->serverPort();
}

QHostAddress TcpHandle::GetIp()
{
    // return tcp_client_list_;
    return QHostAddress();
}

QString TcpHandle::GetMessage()
{
    return current_client_msg_;
}

void TcpHandle::NewConnectionSlot()
{
    current_client_ = tcp_server_->nextPendingConnection();
    tcp_client_list_.append(current_client_);
    // ui->textBrowser->append(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1]).arg(currentClient->peerPort()));
    connect(current_client_, SIGNAL(readyRead()), this, SLOT(ReadServerData()));
    connect(current_client_, SIGNAL(disconnected()), this, SLOT(DisconnectedSlot()));
}
