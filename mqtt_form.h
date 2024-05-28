
#ifndef MQTT_FORM_H
#define MQTT_FORM_H


#include <QWidget>

#include <QtMqtt/qmqttclient.h>
#include <qmqttmessage.h>
#include <qmqtttopicname.h>

#include <QNetworkRequest>
#include <QMessageBox>
#include <QProcess>

#include "clock_control.h"


extern QString updateRealTimeData();

namespace Ui {
class MQTTForm;
}

class MQTTForm : public QWidget
{
    Q_OBJECT
public:
    MQTTForm(QWidget *parent = nullptr);
    ~MQTTForm();


private:
    Ui::MQTTForm *ui_;
    QMqttClient *mqtt_client_;
    QMqttTopicName topic_;
    QByteArray message_;

    void InitMqttServer();

    void IsServerOnline();

private slots:
    void client_connected();

    void client_receivemessage(const QByteArray &, const QMqttTopicName &);

    void client_mqtterror(QMqttClient::ClientError);
    void clietn_disconnected();

    void PingButtonSlot();
    void ConnectButtonSlot();
    void SubscribeButtonSlot();
    void PublishButtonSlot();
    void UnsubscribeButtonSlot();
};

#endif // MQTT_FORM_H
