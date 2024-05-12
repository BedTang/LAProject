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
    connect(client,SIGNAL(messageReceived(QByteArray,QMqttTopicName)),this,SLOT(client_receivemessage(QByteArray,QMqttTopicName)));
    connect(client,SIGNAL(error(QMQTT::ClientError)),this,SLOT(client_mqtterror(QMQTT::ClientError)));
    connect(client,SIGNAL(disconnected()),this,SLOT(client_disconnected()));

}

MQTTForm::~MQTTForm()
{
    delete ui;
}


void MQTTForm::client_connected()   //连接成功
{
    // qDebug()<<"这是来着MQTT类的测试消息!";
    ui->LogBrowser->append(updateRealTimeData()+"云平台连接成功！");
    // qDebug()<<client->is
}


void MQTTForm::client_receivemessage(const QByteArray &message, const QMqttTopicName &topic)    //消息接收
{
    const QString content = updateRealTimeData()
                            + " 主题Topic : "
                            + topic.name().toUtf8()
                            + "\n消息 : "
                            + message;
    ui->LogBrowser->append(content);
}


void MQTTForm::client_mqtterror(QMqttClient::ClientError)   //Error
{

}

void MQTTForm::clietn_disconnected()    //断开连接
{
    ui->LogBrowser->append("连接断开!");
}


void MQTTForm::on_ConnectBtn_clicked()  //连接
{

    // QString mqttAddress("iot-06z00hbczg65rf0.mqtt.iothub.aliyuncs.com");
    client->setHostname(ui->ServerIPLine->text());
    // qDebug()<<client->hostname();
    client->setPort((ui->ServerPortLine->text().toInt()));
    // qDebug()<<client->port();
    client->setClientId(ui->ClientIDLine->text());
    client->setUsername(ui->UserLine->text());
    client->setPassword(ui->PasswordLine->text());
    client->setProtocolVersion(QMqttClient::ProtocolVersion::MQTT_3_1_1);
    client->setKeepAlive(60);
    client->connectToHost();
}


void MQTTForm::on_SubscribeBtn_clicked()    //订阅
{
    qDebug()<<"订阅按钮";
    auto subscriton=client->subscribe(ui->SubTopicLine->text(),0);
    if(!subscriton)
    {
        QMessageBox::critical(this,tr("Error"),tr("订阅失败！请查看是否连接？"));
        return;
    }
    const QString content = "\n"
                            + updateRealTimeData()
                            + " 订阅的主题 : "
                            + ui->SubTopicLine->text();
    ui->LogBrowser->insertPlainText(content);
}


void MQTTForm::on_PublishBtn_clicked()  //发布
{
    // topic=*new QMqttTopicName("/sys/k14suPxlVyQ/Node1/thing/service/property/set");
    topic=*new QMqttTopicName(ui->MesTopicLine->text());
    client->publish(topic,ui->MessageEdit->toPlainText().toUtf8());
}


void MQTTForm::on_UnSubscribeBtn_clicked()  //取消订阅按钮
{
    qDebug() << "取消订阅按钮";
    client->unsubscribe(ui->SubTopicLine->text());
    const QString content = "\n"
                            + updateRealTimeData()
                            + " 取消订阅的主题 : "
                            + ui->SubTopicLine->text();
    ui->LogBrowser->insertPlainText(content);
}

