#include "serialassistantform.h"
#include "ui_serialassistantform.h"

SerialAssistantForm::SerialAssistantForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialAssistantForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);

    serial=new QSerialPort;

    sendNum=0;receiveNum=0;


    ui->dataSendBtn->setEnabled(false);

    connect(serial,SIGNAL(readyRead()),             //信号与槽函数
            this,SLOT(serialPort_readyRead()));

    timer=new QTimer();
    // timer->start(1);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(serialPort_readyRead()));


}

SerialAssistantForm::~SerialAssistantForm()
{
    delete ui;
}

void SerialAssistantForm::serialPort_readyRead()    //串口接收
{
    QByteArray receiveBuf;
    receiveBuf=serial->readAll();

    receiveNum+=receiveBuf.size();

    if(ui->textReceiveRadioBtn->isChecked())
    {
        ui->receiveEdit->insertPlainText(receiveBuf);
    }
    else if(ui->hexReceiveRadioBtn->isChecked())
    {
        QString str=receiveBuf.toHex().toUpper();
        QString str2;
        for(int i=0;i<receiveBuf.size();i+=2)
        {
            str2+=str.mid(i,2);
            str2+=" ";
        }
        ui->receiveEdit->insertPlainText(str2);
    }



}

void SerialAssistantForm::TimerEvent()
{

}

void SerialAssistantForm::on_pushButton_clicked()
{

}


void SerialAssistantForm::on_pushButton_2_clicked()
{

}



void SerialAssistantForm::on_serialSwitchBtn_clicked()  //开关串口
{
    if(ui->serialSwitchBtn->text()=="打开串口")
    {
        //设置端口名
        serial->setPortName(ui->serialPortList->currentText());
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(ui->baudRateList->currentText().toInt());
        //设置数据位
        switch (ui->dataBitsList->currentIndex()) {
        case 5:
            serial->setDataBits(QSerialPort::Data5);
            break;
        case 6:
            serial->setDataBits(QSerialPort::Data6);
            break;
        case 7:
            serial->setDataBits(QSerialPort::Data7);
            break;
        case 8:
            serial->setDataBits(QSerialPort::Data8);
            break;
        default:
            serial->setDataBits(QSerialPort::UnknownDataBits);
            break;
        }
        //设置奇偶校验位
        switch (ui->parityList->currentIndex()) {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        case 1:
            serial->setParity(QSerialPort::OddParity);
            break;
        case 2:
            serial->setParity(QSerialPort::EvenParity);
            break;
        case 3:
            serial->setParity(QSerialPort::MarkParity);
            break;
        case 4:
            serial->setParity(QSerialPort::SpaceParity);
            break;
        default:
            serial->setParity(QSerialPort::UnknownParity);
            break;
        }
        //设置停止位
        switch (ui->stopBitsList->currentIndex()) {
        case 0:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            serial->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            serial->setStopBits(QSerialPort::UnknownStopBits);
            break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //打开串口
        if(!serial->isOpen())
        {
            QMessageBox::about(NULL,"提示","打开串口失败");
            qDebug()<<"11";
        }

        //组合框失能
        ui->serialPortList->setEnabled(false);
        ui->baudRateList->setEnabled(false);
        ui->dataBitsList->setEnabled(false);
        ui->parityList->setEnabled(false);
        ui->stopBitsList->setEnabled(false);
        ui->scanSerialBtn->setEnabled(false);

        ui->serialSwitchBtn->setText(tr("关闭串口"));
        ui->dataSendBtn->setEnabled(true);
    }
    else
    {
        serial->close();

        ui->serialPortList->setEnabled(true);
        ui->baudRateList->setEnabled(true);
        ui->dataBitsList->setEnabled(true);
        ui->parityList->setEnabled(true);
        ui->stopBitsList->setEnabled(true);
        ui->scanSerialBtn->setEnabled(true);

        ui->serialSwitchBtn->setText(tr("打开串口"));
        ui->dataSendBtn->setEnabled(false);
    }
}


void SerialAssistantForm::on_scanSerialBtn_clicked()
{
    ui->serialPortList->clear();
    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        qDebug()<<"serialPortName : "<<info.portName();
    }
    ui->serialPortList->clear();
    ui->serialPortList->addItems(m_serialPortName);
}


void SerialAssistantForm::on_dataSendBtn_clicked()
{
    QByteArray sendBuf;

    if(ui->textSendRadioBtn->isChecked())
    {
        sendBuf=ui->sendEdit->toPlainText().toUtf8().data();
    }
    else
    {
        sendBuf=QByteArray::fromHex(ui->sendEdit->toPlainText().toUtf8().data());
    }
    serial->write(sendBuf);
}

