#include "mqttform.h"
#include "ui_mqttform.h"

#include "qhostaddress.h"



MQTTForm::MQTTForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MQTTForm)
{
    setAttribute(Qt::WA_QuitOnClose,false);
    ui->setupUi(this);
    this->setWindowTitle("MQTT工具");
    client=new QMqttClient(this);
    connect(client,SIGNAL(connected()),this,SLOT(client_connected()));
    connect(client,SIGNAL(subscribed(QString,quint8)),this,SLOT(client_subscribled(QString,quint8)));
    connect(client,SIGNAL(messageReceived(QByteArray,QMqttTopicName)),this,SLOT(client_receivemessage(QByteArray,QMqttTopicName)));
    connect(client,SIGNAL(unsubscribed(QString)),this,SLOT(client_unsubscrbled(QString)));
    connect(client,SIGNAL(error(QMQTT::ClientError)),this,SLOT(client_mqtterror(QMQTT::ClientError)));
    connect(client,SIGNAL(disconnected()),this,SLOT(client_disconnected()));

}

MQTTForm::~MQTTForm()
{
    delete ui;
    qDebug()<<"123";
}

void MQTTForm::client_connected()
{
    // qDebug()<<"这是来着MQTT类的测试消息!";
    ui->LogBrowser->append("[ "+updateRealTimeData()+" ]"+"云平台连接成功！");
    // qDebug()<<client->is
}

void MQTTForm::client_subscribled(QString, quint8)
{
    const QString content = QDateTime::currentDateTime().toString()
                            + QLatin1String(" Received Topic: ")
                            + topic.name()
                            + QLatin1String(" Message: ")
                            + message
                            + QLatin1Char('\n');
    ui->LogBrowser->insertPlainText(content);
}

void MQTTForm::client_receivemessage(const QByteArray &message, const QMqttTopicName &topic)
{
    ui->LogBrowser->append(message);

}

void MQTTForm::client_unsubscrbled(QString)
{

}

void MQTTForm::client_mqtterror(QMqttClient::ClientError)
{

}

void MQTTForm::clietn_disconnected()
{
    ui->LogBrowser->append("连接断开!");
}


void MQTTForm::on_ConnectBtn_clicked()
{

    // QString mqttAddress("iot-06z00hbczg65rf0.mqtt.iothub.aliyuncs.com");
    client->setHostname(ui->ServerIPLine->text());
    qDebug()<<client->hostname();
    client->setPort((ui->ServerPortLine->text().toInt()));
    qDebug()<<client->port();
    client->setClientId(ui->ClientIDLine->text());
    client->setUsername(ui->UserLine->text());
    client->setPassword(ui->PasswordLine->text());
    client->setProtocolVersion(QMqttClient::ProtocolVersion::MQTT_3_1_1);
    client->setKeepAlive(60);
    client->connectToHost();
}


void MQTTForm::on_SubscribeBtn_clicked()
{
    auto subscriton=client->subscribe(ui->TopicLine->text(),0);
    if(!subscriton)
    {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
}


void MQTTForm::on_PublishBtn_clicked()
{
    topic=*new QMqttTopicName("/sys/k14suPxlVyQ/Node1/thing/service/property/set");
    client->publish(topic,"Hello MQTT!");
}

