#ifndef MQTT_FORM_H
#define MQTT_FORM_H

#include <QWidget>

#include <qmqttclient.h>
#include <qmqttmessage.h>
#include <qmqtttopicname.h>

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

    void SetJsonMessage(QString);

private:
    Ui::MqttForm *ui_;
    QMqttClient *mqtt_client_;
    QMqttTopicName topic_;
    QByteArray message_;

    JsonHandler *jsoner;

    QList<int> data_list_in_mqtt;

    QString json_message;

    void GetDevcieData(QList<int>);
    QList<int> ReturnDeviceData();

    void InitMqttServer();

    void IsServerOnline();

    void PublishMessage();

private slots:
    void client_connected();

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
