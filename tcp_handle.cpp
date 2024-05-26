#include "tcp_handle.h"
#include "main_form.h"

extern QString updateRealTimeData();


tcpHandle::tcpHandle(QWidget *parent, Ui::MainForm *ui_)
    : QWidget(parent)
    ,ui_(ui_)
{
    connect(tcp_server_, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));

}

void tcpHandle::retrieveNativeIp()
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

        if (interface.humanReadableName().contains("WLAN"))
        {
            // 滤掉ipv6地址
            foreach (auto entry ,interface.addressEntries())
            {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                    ui_->logBrowser->append("本机IP地址："+entry.ip().toString());
            }
        }
    }
}

void tcpHandle::serverReadData()
{
    qDebug()<<"serverReadData()<<serverReadData";

    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    for(int i=0; i<tcp_client_list_.length(); i++)
    {
        QByteArray buffer = tcp_client_list_[i]->readAll();

        if(buffer.isEmpty())
        {
            continue;
        }

        static QString IP_Port, IP_Port_Pre;
        IP_Port = tr("[%1:%2]:").arg(tcp_client_list_[i]->peerAddress().toString().split("::ffff:")[1])\
                      .arg(tcp_client_list_[i]->peerPort());

        // 若此次消息的地址与上次不同，则需显示此次消息的客户端地址
        if(IP_Port != IP_Port_Pre)
            ui_->logBrowser->append(IP_Port);

        //处理接收到的数据
        current_client_msg_=buffer;
        current_client_msg_=current_client_msg_.simplified();
        // qDebug()<<std::get<0>(json->dataHandle(device_list, str)); //device_list,
        ui_->logBrowser->append(updateRealTimeData()+current_client_msg_);

        // qDebug()<<QHostAddress(tcp_client_list_[i]->peerAddress().toString().split("::ffff:")[1]);
        emit RequestAddDevice(QHostAddress(tcp_client_list_[i]->peerAddress().toString().split("::ffff:")[1]));
        qDebug()<<"请求添加设备";
        // emit RequestDataHandle(current_client_msg_);

        //更新ip_port
        IP_Port_Pre = IP_Port;
    }
}

void tcpHandle::disconnectedSlot()
{

}

void tcpHandle::server_listening(bool &status ,int port)
{
    if(status == false)
    {
        tcp_server_->listen(QHostAddress::Any, port);
        qDebug()<<tr("监听端口：")<<tcp_server_->serverPort();
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

int tcpHandle::GetPort()
{
    return tcp_server_->serverPort();
}

QHostAddress tcpHandle::GetIp()
{
    // return tcp_client_list_;
}

QString tcpHandle::GetMessage()
{
    return current_client_msg_;
}

void tcpHandle::newConnectionSlot()
{
    current_client_ = tcp_server_->nextPendingConnection();
    tcp_client_list_.append(current_client_);
    // ui->textBrowser->append(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1]).arg(currentClient->peerPort()));
    connect(current_client_, SIGNAL(readyRead()), this, SLOT(serverReadData()));
    qDebug()<<"serverReadData connect 触发后";
    connect(current_client_, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}
