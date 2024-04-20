#ifndef SERIALASSISTANTFORM_H
#define SERIALASSISTANTFORM_H

#include <QWidget>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QTimer>

namespace Ui {
class SerialAssistantForm;
}

class SerialAssistantForm : public QWidget
{
    Q_OBJECT

public:
    explicit SerialAssistantForm(QWidget *parent = nullptr);
    ~SerialAssistantForm();
    int Times,portTiem,lineEditData;


private:
    Ui::SerialAssistantForm *ui;

    QSerialPort *serial;//串口端口

    QTimer *timer;//定时器

    QByteArray sendBuffer,ReceiveBuffer;//发送、接收缓冲区

    long int sendByte,ReceiveByte;//发送、接收字符数


private slots:
    void serialPort_readyRead();
    void TimerEvent();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_serialOpenBT_clicked();
    void on_scanSerialBT_clicked();
};

#endif // SERIALASSISTANTFORM_H
