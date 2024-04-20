#include "serialassistantform.h"
#include "ui_serialassistantform.h"

SerialAssistantForm::SerialAssistantForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialAssistantForm)
{
    ui->setupUi(this);

    serial=new QSerialPort;

    sendByte=0;ReceiveByte=0;

    connect(serial,SIGNAL(readyRead()),             //信号与槽函数
            this,SLOT(serialPort_readyRead()));

    timer=new QTimer();
    timer->start(1);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(serialPort_readyRead()));
}

SerialAssistantForm::~SerialAssistantForm()
{
    delete ui;
}

void SerialAssistantForm::serialPort_readyRead()
{

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


void SerialAssistantForm::on_serialOpenBT_clicked()
{
    if(ui->serialOpenBT->text()=="打开串口")
    {
        //设置串口名
        // serial->setPortName();
    }
}


void SerialAssistantForm::on_scanSerialBT_clicked()
{
    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        qDebug()<<"serialPortName : "<<info.portName();
    }
    ui->comboBox->clear();//
    ui->comboBox->addItems(m_serialPortName);
}


