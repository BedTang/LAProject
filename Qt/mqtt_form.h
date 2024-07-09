#ifndef MQTT_FORM_H
#define MQTT_FORM_H

#include <QWidget>

#ifdef Q_OS_WIN
    #include <qmqttclient.h>
    #include <qmqttmessage.h>
    #include <qmqtttopicname.h>
#else
    #include </root/qtmqtt-5.15.2/src/mqtt/qmqttclient.h>
    #include </root/qtmqtt-5.15.2/src/mqtt/qmqttmessage.h>
    #include </root/qtmqtt-5.15.2/src/mqtt/qmqtttopicname.h>
#endif

#include <QNetworkRequest>
#include <QMessageBox>
#include <QProcess>

#include "devices_data_handler.h"

namespace Ui {
class MqttForm;
}

class MqttForm : public QWidget
{
    Q_OBJECT
public:
    MqttForm(QWidget *parent = nullptr);
    ~MqttForm();

    void SetJsonMessage(QString ,int);
    void InitMqttServer();

private:
    Ui::MqttForm *ui_;
    QMqttClient *mqtt_client_;
    QMqttClient *mqtt_client_2;
    QMqttClient *mqtt_client_3;
    QMqttTopicName topic_;
    QByteArray message_;

    JsonHandler *jsoner;

    QList<int> data_list_in_mqtt;

    QString json_message;

    void GetDevcieData(QList<int>);
    QList<int> ReturnDeviceData();



    void IsServerOnline();

    void PublishMessage(int);

private slots:
    void MqttClientConnected();

    void client_mqtterror(QMqttClient::ClientError);
    void clietn_disconnected();

    void PingButtonSlot();
    void ConnectButtonSlot();
    void SubscribeButtonSlot();
    void PublishButtonSlot();
    void UnsubscribeButtonSlot();
    void ReceiveClientMessages(const QByteArray &, const QMqttTopicName &);
    void on_pushButton_clicked();
};

#endif // MQTT_FORM_H
