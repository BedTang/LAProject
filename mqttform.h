
#ifndef MQTTFORM_H
#define MQTTFORM_H


#include <QWidget>
#include <QMessageBox>
#include <string.h>

#include <QtMqtt/qmqttclient.h>
#include <qmqttmessage.h>
#include <qmqtttopicname.h>

#include "TimeFunc.h"

namespace Ui {
class MQTTForm;
}

class MQTTForm : public QWidget
{
    Q_OBJECT
public:
    explicit MQTTForm(QWidget *parent = nullptr);
    ~MQTTForm();


private:
    Ui::MQTTForm *ui;
    QMqttClient *client;
    QMqttTopicName topic;
    QByteArray message;

private slots:
    void client_connected();
    void client_subscribled(QString,quint8);
    void client_receivemessage(const QByteArray &, const QMqttTopicName &);
    void client_unsubscrbled(QString);
    void client_mqtterror(QMqttClient::ClientError);
    void clietn_disconnected();
    void on_ConnectBtn_clicked();
    void on_SubscribeBtn_clicked();
    void on_PublishBtn_clicked();
    void on_UnSubscribeBtn_clicked();
};

#endif // MQTTFORM_H
