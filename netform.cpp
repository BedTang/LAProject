#include "netform.h"
#include "ui_netform.h"
#include <QTimer>

#include "timefunc.h"

NetForm::NetForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetFrom)
    ,timer(new QTimer(this))
{
    ui->setupUi(this);

    textdefault.setForeground(Qt::black);
    textdefault.setBackground(Qt::white);

    foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
    {
        // qDebug()<<interface.humanReadableName();
        if(interface.humanReadableName().contains("VMware") || interface.humanReadableName().contains("Virtual"))
            continue;
            // 根据协议版本，来过滤掉ipv6地址
        foreach(auto entry ,interface.addressEntries())
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                ui->comboBox->addItem(entry.ip().toString());
                // return entry.ip();
        }
    }
    if(ui->checkBox->checkState())
    {
        ui->pushButton_2->setText("开始发送");
    }

    cursor=ui->textEdit->textCursor();
    scrollbar = ui->textEdit->verticalScrollBar();

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
    connect(timer,SIGNAL(timeout()), this, SLOT(timerOperation()));


}

NetForm::~NetForm()
{
    delete ui;
}


void NetForm::on_pushButton_clicked()
{
    QString cfile=QFileDialog::getOpenFileName(
        this,
        "选择文件",
        "/",
        "文本文件(*.txt)");
    qDebug()<<cfile;
    ui->lineEdit->setText(cfile);
    QFile sfile(cfile);
    if(sfile.exists())
    {
        ui->textBrowser_2->append(updateRealTimeData()+"文件打开成功!");
        sfile.open(QIODevice::ReadOnly | QIODevice::Text);
    }
    else
    {
        ui->textBrowser_2->append(updateRealTimeData()+"打开文件失败！");
        return;
    }
    QTextStream in(&sfile);
    while (!in.atEnd())
    {
        int num = in.readLine().indexOf("数据:");      //整行读取
        QString str=in.readLine().remove(0,num+3);
        QJsonParseError error;
        QJsonDocument jsonDoc=QJsonDocument::fromJson(str.toUtf8(),&error);
        if(error.error != QJsonParseError::NoError)
        {
            // qDebug()<<jsonDoc;
            continue;
        }
        ui->textEdit->append(str);
    }
    cursor.movePosition(QTextCursor::Start);
    scrollbar->setSliderPosition(0);
}


void NetForm::on_pushButton_2_clicked()
{
    if(ui->checkBox->isChecked())
    {
        timer->start(ui->doubleSpinBox->value()*1000);
    }

}


void NetForm::on_pushButton_3_clicked()
{


    if(ui->pushButton_3->text()=="启动服务器")
    {
        qDebug()<<"1";
        tcpServer->listen(QHostAddress(ui->comboBox->currentText()), ui->spinBox_2->value());
        qDebug()<<"2";
        qDebug()<<tcpServer->serverPort();
        ui->textBrowser_2->append("IP地址:" + tcpServer->serverAddress().toString());
        ui->textBrowser_2->append("当前服务器端口:" + QString::number(tcpServer->serverPort()));
        ui->pushButton_3->setText("关闭服务器");
        return;
    }

    if(ui->pushButton_3->text()=="关闭服务器")
    {
        for(int i=0; i<clientList.length(); i++)
        {
            clientList[i]->disconnectFromHost();
            bool ok = clientList[i]->waitForDisconnected(1000);
            if(!ok)
            {
                qDebug()<<"断连失败";
            }
            clientList.removeAt(i);
        }
        tcpServer->close();

        for(int i=0; i<clientList.length(); i++)
        {
            if(clientList[i]->state() == QAbstractSocket::UnconnectedState)
            {
                clientList[i]->destroyed();
                clientList.removeAt(i);
            }
        }
        ui->pushButton_3->setText("启动服务器");
    }
}


void NetForm::NewConnectionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
    clientList.append(currentClient);
    // ui->textBrowser->append(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1]).arg(currentClient->peerPort()));
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ServerReadData()));
    // connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}

void NetForm::timerOperation()
{
    cursor.mergeCharFormat(textdefault);
    cursor.movePosition(QTextCursor::Down);
    cursor.select(QTextCursor::BlockUnderCursor);
    QString curTxt=cursor.selectedText();
    qDebug()<<curTxt;
    //全部连接
    QString data = curTxt;
    for(int i=0; i<clientList.length(); i++)
    {
        clientList[i]->write(data.toLatin1()); //qt5除去了.toAscii()
        if(clientList[i]->waitForBytesWritten(10))
            ui->textBrowser_2->append(updateRealTimeData()+":"+curTxt);
    }
    highlight.setForeground(Qt::white);
    highlight.setBackground(Qt::red);
    cursor.mergeCharFormat(highlight);
    qDebug()<<"color";

}



void NetForm::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked())
    {
        ui->pushButton_2->setText("开始发送");
    }
    if(!ui->checkBox->isChecked())
    {
        ui->pushButton_2->setText("发送");
    }
}


void NetForm::on_textEdit_cursorPositionChanged()
{

}


void NetForm::on_checkBox_2_stateChanged(int arg1)
{

}

