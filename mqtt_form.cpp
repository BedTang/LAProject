#include "mqtt_form.h"
#include "ui_mqtt_form.h"

MQTTForm::MQTTForm(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::MQTTForm)
{
    setAttribute(Qt::WA_QuitOnClose,false);
    ui_->setupUi(this);
    this->setWindowTitle("MQTT工具");
    mqtt_client_=new QMqttClient(this);
    connect(mqtt_client_,SIGNAL(connected()),this,SLOT(client_connected()));
    connect(mqtt_client_,SIGNAL(messageReceived(QByteArray,QMqttTopicName)),this,SLOT(client_receivemessage(QByteArray,QMqttTopicName)));
    connect(mqtt_client_,SIGNAL(error(QMQTT::ClientError)),this,SLOT(client_mqtterror(QMQTT::ClientError)));
    connect(mqtt_client_,SIGNAL(disconnected()),this,SLOT(client_disconnected()));

    connect(ui_->connect_button_ ,&QPushButton::clicked ,this ,&MQTTForm::ConnectButtonSlot);
    connect(ui_->ping_button_ ,&QPushButton::clicked ,this ,&MQTTForm::PingButtonSlot);
    connect(ui_->subscribe_topic_button_ ,&QPushButton::clicked ,this ,&MQTTForm::SubscribeButtonSlot);
    connect(ui_->publish_button_ ,&QPushButton::clicked ,this ,&MQTTForm::PublishButtonSlot);
    connect(ui_->unsubscribe_topic_button_ ,&QPushButton::clicked ,this ,&MQTTForm::UnsubscribeButtonSlot);

}

MQTTForm::~MQTTForm()
{
    delete ui_;
}

void MQTTForm::InitMqttServer()
{
    mqtt_client_->setHostname(ui_->server_host_line_->text());
    mqtt_client_->setPort((ui_->server_port_line_->text().toInt()));
    mqtt_client_->setClientId(ui_->client_id_line_->text());
    mqtt_client_->setUsername(ui_->client_user_line_->text());
    mqtt_client_->setPassword(ui_->client_password_line_->text());
    mqtt_client_->setProtocolVersion(QMqttClient::ProtocolVersion::MQTT_3_1_1);
    mqtt_client_->setKeepAlive(60);
    mqtt_client_->connectToHost();
}

void MQTTForm::IsServerOnline()
{
    // 预计废弃
}

void MQTTForm::client_connected()   //连接成功
{
    ui_->log_browser_->append(updateRealTimeData()+"云平台连接成功！");
}

void MQTTForm::client_receivemessage(const QByteArray &message, const QMqttTopicName &topic)    //消息接收
{
    const QString content = updateRealTimeData()
                            + " 主题Topic : "
                            + topic.name().toUtf8()
                            + "\n消息 : "
                            + message;
    ui_->log_browser_->append(content);
}


void MQTTForm::client_mqtterror(QMqttClient::ClientError)   //Error
{

}

void MQTTForm::clietn_disconnected()    //断开连接
{
    ui_->log_browser_->append("连接断开!");
}

void MQTTForm::PingButtonSlot()
{
    QString host_address = ui_->server_host_line_->text();
    QProcess cmd;

#ifdef Q_OS_WIN
    QString cmd_string = QString("ping %0 -n 1 -w %1")
                             .arg(host_address).arg(1000);

#else
    QString cmd_string = QString("ping -s 1 -c 1 %1")
                                  .arg(host_address);
#endif
    cmd.start(cmd_string);
    cmd.waitForReadyRead(1000);
    cmd.waitForFinished(1000);

    QString ping_result = QString::fromLocal8Bit(cmd.readAll());
    qDebug()<<ping_result;
    if (ping_result.indexOf("TTL") == -1)
    {
        ui_->log_browser_->append(tr("服务器：%0，连接失败。") .arg(ui_->server_host_line_->text()));
    }
    else
    {
        ui_->log_browser_->append(tr("服务器：%0，连接成功。") .arg(ui_->server_host_line_->text()));
    }
}

void MQTTForm::ConnectButtonSlot()  //连接
{
    InitMqttServer();
    ui_->log_browser_->append(tr("服务器地址：%0\n").arg(mqtt_client_->hostname())+
                             tr("服务器端口：%0\n").arg(mqtt_client_->port())+
                             tr("ClientID：%0\n").arg(mqtt_client_->clientId())+
                             tr("用户名：%0\n").arg(mqtt_client_->username())+
                             tr("密码：%0").arg(mqtt_client_->password()));
}

void MQTTForm::SubscribeButtonSlot()    //订阅
{
    qDebug()<<"订阅按钮";
    auto subscriton=mqtt_client_->subscribe(ui_->subscribe_topic_line_->text(),0);
    if(!subscriton)
    {
        QMessageBox::critical(this,tr("Error"),tr("订阅失败！请查看是否连接？"));
        return;
    }
    const QString content = "\n"
                            + updateRealTimeData()
                            + " 订阅的主题 : "
                            + ui_->subscribe_topic_line_->text();
    ui_->log_browser_->insertPlainText(content);
}

void MQTTForm::PublishButtonSlot()  //发布
{
    qDebug()<<tr("PushButtonSlot()");
    // topic=*new QMqttTopicName("/sys/k14suPxlVyQ/Node1/thing/service/property/set");
    topic_=*new QMqttTopicName(ui_->publish_topic_line_->text());
    mqtt_client_->publish(topic_,ui_->message_text_->toPlainText().toUtf8());
}

void MQTTForm::UnsubscribeButtonSlot()  //取消订阅按钮
{
    qDebug()<<tr("UnsubscribeButtonSlot()");
    mqtt_client_->unsubscribe(ui_->subscribe_topic_line_->text());
    const QString content = "\n"
                            + updateRealTimeData()
                            + " 取消订阅的主题 : "
                            + ui_->subscribe_topic_line_->text();
    ui_->log_browser_->insertPlainText(content);
}

