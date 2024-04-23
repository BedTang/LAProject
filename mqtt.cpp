#include "mqtt.h"
#include "qhostaddress.h"



MQTT::MQTT(QWidget *parent)
    : QWidget(parent)
{
    client=new QMqttClient(this);
    QString mqttAddress("iot-06z00hbczg65rf0.mqtt.iothub.aliyuncs.com");

    client->setHostname("iot-06z00hbczg65rf0.mqtt.iothub.aliyuncs.com");
    qDebug()<<client->hostname();
    client->setPort(static_cast<quint16>(1883));
    qDebug()<<client->port();
    client->setClientId("Node1|securemode=2,signmethod=hmacsha1,timestamp=1713795492750|");
    client->setUsername("Node1&k14suPxlVyQ");
    client->setPassword("9A6711EB8A8E9505ED2C72FDFBA4EEB8E6B19F78");
    client->setProtocolVersion(QMqttClient::ProtocolVersion::MQTT_3_1_1);
    client->setKeepAlive(60);
    client->connectToHost();
    qDebug()<<"!";




    connect(client,SIGNAL(connected()),this,SLOT(client_connected()));
    connect(client,SIGNAL(subscribed(QString,quint8)),this,SLOT(client_subscribled(QString,quint8)));
    connect(client,SIGNAL(received(QMQTT::Message)),this,SLOT(client_receivemessage(QMQTT::Message)));
    connect(client,SIGNAL(unsubscribed(QString)),this,SLOT(client_unsubscrbled(QString)));
    connect(client,SIGNAL(error(QMQTT::ClientError)),this,SLOT(client_mqtterror(QMQTT::ClientError)));
    connect(client,SIGNAL(disconnected()),this,SLOT(client_disconnected()));
    qDebug()<<QMqttClient::ClientState();

}

MQTT::~MQTT()
{
    qDebug()<<"123";
}

void MQTT::client_connected()
{
    qDebug()<<"这是来着MQTT类的测试消息!";
    // ui->textBrowser->append("这是来着MQTT类的测试消息!");
    qDebug()<<QMqttClient::ClientState();
}

void MQTT::client_subscribled(QString, quint8)
{

}

void MQTT::client_receivemessage(QMqttMessage)
{

}

void MQTT::client_unsubscrbled(QString)
{

}

void MQTT::client_mqtterror(QMqttClient::ClientError)
{

}

void MQTT::clietn_disconnected()
{

}

void MQTT::on_pushButton4_clicked()
{

}

