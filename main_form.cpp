#include "main_form.h"
#include "ui_main_form.h"
// #include "mqtt.h"

QString updateRealTimeData()
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("[ hh:mm:ss:z ]");
}

QString updateRealTimeData(int)
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("[ hh:mm:ss ]");
}

MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
    , timer(new QTimer(this))
    , timeCount(0)
    , settingForm(new SettingForm(nullptr, tcpServerPort))

{
    ui->setupUi(this);
    this->setWindowTitle("分布式工业节点与电机智能监测系统");

    // UI初始化
    ui->devicesTab->tabBar()->setTabButton(0, QTabBar::RightSide, nullptr);
    ui->splitter->setStretchFactor(0,2);
    ui->splitter->setStretchFactor(1,3);

    // devicesView初始化
    tableView = new tableViewClass(this, ui->devicesView);

    //数据库初始化
    db = new DatabaseHandle();

    // 定时器
    timer->start(1000);

    // Json解析器
    json = new jsonHandle();

    // 数据库
    DatabaseHandle sqldb;
    while(char tmep=sqldb.openDb())
    {
        switch (tmep) {
        case 0:break;
        case 1:return;
        case 2:exit(1);break;
        }
    }

    // 网卡信息
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
                    ui->logBrowser->append("本机IP地址："+entry.ip().toString());
            }
        }
    }



    // 信号与槽
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
    connect(timer,SIGNAL(timeout()), this, SLOT(oneSecondAction()));
}

MainForm::~MainForm()
{
    delete ui;
}

QString MainForm::ServerReadData()
{
    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    for(int i=0; i<WhattcpClient.length(); i++)
    {
        QByteArray buffer = WhattcpClient[i]->readAll();
        if(buffer.isEmpty())
        {
            continue;
        }

        static QString IP_Port, IP_Port_Pre;
        IP_Port = tr("[%1:%2]:").arg(WhattcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                      .arg(WhattcpClient[i]->peerPort());

        // 若此次消息的地址与上次不同，则需显示此次消息的客户端地址
        if(IP_Port != IP_Port_Pre)
            ui->logBrowser->append(IP_Port);

        //处理接收到的数据
        QString str=buffer;
        str=str.simplified();
        // qDebug()<<std::get<0>(json->dataHandle(device_list, str)); //device_list,
        ui->logBrowser->append(updateRealTimeData()+str);

        //更新ip_port
        IP_Port_Pre = IP_Port;
        return str;
    }
}

void MainForm::NewConnectionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
    WhattcpClient.append(currentClient);
    // ui->textBrowser->append(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1]).arg(currentClient->peerPort()));
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(addView()));
    // connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}

void MainForm::addView()
{
    chartView = new chartViewClass(this);
    // qDebug()<< std::get<0>(json->dataHandle(device_list, ServerReadData()));

    std::tuple<int,int,int,int,int> list;
    list = json->dataHandle(device_list, ServerReadData());

    if(std::get<0>(list) == NULL)
    {
        return;
    }
    qDebug()<<"list:id:"<<std::get<0>(list);
    qDebug()<<"device_list:id:"<<device_list.at(0);
    if(device_list.contains(std::get<0>(list)))
    {
        ui->devicesTab->addTab(chartView->addChart(),tr("设备ID：%0").arg(std::get<0>(list)));
        tableView->addData();
    }

}

void MainForm::oneSecondAction()
{
    ui->statusBar->showMessage("当前系统时间："+updateRealTimeData(1));
}

//UI按钮功能区
void MainForm::on_startServer_clicked()
{
    if(ui->startServer->text()==tr("启动服务器"))
    {
        tcpServer->listen(QHostAddress::Any, tcpServerPort);
        qDebug()<<tcpServer->serverPort();
        ui->logBrowser->append(tr("当前服务器端口:") + QString::number(tcpServer->serverPort()));
        ui->startServer->setText(tr("关闭服务器"));
        return;
    }

    if(ui->startServer->text()==tr("关闭服务器"))
    {
        for(int i=0; i<WhattcpClient.length(); i++)//断开所有连接
        {
            WhattcpClient[i]->disconnectFromHost();
            bool ok = WhattcpClient[i]->waitForDisconnected(1000);
            if(!ok)
            {
                // 处理异常
            }
            WhattcpClient.removeAt(i);  //从保存的客户端列表中取去除
        }
        tcpServer->close();     //不再监听端口

        //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
        for(int i=0; i<WhattcpClient.length(); i++)
        {
            if(WhattcpClient[i]->state() == QAbstractSocket::UnconnectedState)
            {
                // 删除存储在combox中的客户端信息
                // ui->cbxConnection->removeItem(ui->cbxConnection->findText(tr("%1:%2")
                //                                                               .arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])
                //                                                               .arg(tcpClient[i]->peerPort())));
                // 删除存储在tcpClient列表中的客户端信息
                WhattcpClient[i]->destroyed();
                WhattcpClient.removeAt(i);
            }
        }
        ui->startServer->setText(tr("启动服务器"));
    }
}

void MainForm::on_pushButton2_clicked()
{
    ui->logBrowser->append(updateRealTimeData()+"测试2");
}

void MainForm::on_pushButton3_clicked()
{
    ui->logBrowser->append(updateRealTimeData()+"测试3");
    // MQTTForm *a=new MQTTForm();
    addView();
}

void MainForm::on_pushButton4_clicked()
{
    // ui->logBrowser->append(updateRealTimeData()+"测试4");
    qDebug()<<tr("打开设置界面");
    settingForm->show();
}

void MainForm::on_devicesTab_tabCloseRequested(int index)
{
    chartView = qobject_cast<class chartViewClass *>(sender());
    ui->devicesTab->removeTab(index);
    delete chartView;
    tableView->deleteView(index);
}



void MainForm::updateSeries(float point,unsigned char n)
{
    timeCount++;

    QPointF p1(QDateTime::currentMSecsSinceEpoch(),point);
}

void MainForm::updateAxisRange()
{
}
