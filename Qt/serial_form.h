#ifndef SERIAL_FORM_H
#define SERIAL_FORM_H

#include <QWidget>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QMessageBox>

#include <QTimer>

#include <QButtonGroup>

namespace Ui {
class SerialForm;
}

class SerialForm : public QWidget
{
    Q_OBJECT

public:
    SerialForm(QWidget *parent = nullptr);
    ~SerialForm();
    int Times,portTiem,lineEditData;


private:
    Ui::SerialForm *ui;

    QSerialPort *serial;//串口端口

    QTimer *timer;//定时器

    // QByteArray sendBuffer,recvBuffer;//发送、接收缓冲区

    long int sendNum,receiveNum;//发送、接收字符数


private slots:
    void serialPort_readyRead();
    void TimerEvent();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_serialSwitchBtn_clicked();
    void on_scanSerialBtn_clicked();
    void on_dataSendBtn_clicked();
};

#endif // SERIAL_FORM_H
