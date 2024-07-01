#include "mqtt_form.h"
#include "ui_mqtt_form.h"

extern QString GetCurrentStringTime();
extern void DebugOut(QString);

MqttForm::MqttForm(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::MqttForm)
{
    setAttribute(Qt::WA_QuitOnClose,false);

    ui_->setupUi(this);
    this->setWindowTitle("MQTT工具");

    mqtt_client_=new QMqttClient(this);

    connect(ui_->connect_button_ ,&QPushButton::clicked ,this ,&MqttForm::ConnectButtonSlot);
    connect(ui_->ping_button_ ,&QPushButton::clicked ,this ,&MqttForm::PingButtonSlot);
    connect(ui_->subscribe_topic_button_ ,&QPushButton::clicked ,this ,&MqttForm::SubscribeButtonSlot);
    connect(ui_->publish_button_ ,&QPushButton::clicked ,this ,&MqttForm::PublishButtonSlot);
    connect(ui_->unsubscribe_topic_button_ ,&QPushButton::clicked ,this ,&MqttForm::UnsubscribeButtonSlot);
    connect(mqtt_client_ ,&QMqttClient::messageReceived ,this ,&MqttForm::ReceiveClientMessages);
    connect(mqtt_client_ ,&QMqttClient::connected ,this ,&MqttForm::MqttClientConnected);
    connect(mqtt_client_ ,&QMqttClient::disconnected ,this ,&MqttForm::clietn_disconnected);
    connect(mqtt_client_ ,&QMqttClient::errorChanged ,this ,&MqttForm::client_mqtterror);

    jsoner = new JsonHandler();
}

MqttForm::~MqttForm()
{
    delete ui_;
}

void MqttForm::SetJsonMessage(QString message)
{
    DebugOut("MqttForm::SetJsonMessage()<<");
    json_message = message;
    PublishMessage();
}

void MqttForm::GetDevcieData(QList<int> list)
{
    data_list_in_mqtt = list;
}

QList<int> MqttForm::ReturnDeviceData()
{
    return data_list_in_mqtt;
}

void MqttForm::InitMqttServer()
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

void MqttForm::IsServerOnline()
{
    // 预计废弃
}

void MqttForm::PublishMessage()
{
    DebugOut("MqttForm::PublishMessage()<<");
    mqtt_client_->setHostname(ui_->server_host_line_->text());
    mqtt_client_->setPort((ui_->server_port_line_->text().toInt()));
    mqtt_client_->setClientId(ui_->client_id_line_->text());
    mqtt_client_->setUsername(ui_->client_user_line_->text());
    mqtt_client_->setPassword(ui_->client_password_line_->text());
    mqtt_client_->setProtocolVersion(QMqttClient::ProtocolVersion::MQTT_3_1_1);
    mqtt_client_->setKeepAlive(60);
    mqtt_client_->connectToHost();
    topic_=*new QMqttTopicName("$sys/zdgol22rNA/Node1/thing/property/post");
    mqtt_client_->publish(topic_ ,json_message.toUtf8());
}

void MqttForm::MqttClientConnected()   //连接成功
{
    DebugOut("MqttForm::MqttClientConnected()<<MQTT connection successful!");
    ui_->log_browser_->append(GetCurrentStringTime()+"云平台连接成功！");
    ui_->mqtt_clinet_list_->addItem(ui_->client_id_line_->text());
}

void MqttForm::ReceiveClientMessages(const QByteArray &message, const QMqttTopicName &topic)    //消息接收
{
    const QString content = GetCurrentStringTime()
                            + " 主题Topic : "
                            + topic.name().toUtf8()
                            + "\n消息 : "
                            + message;
    ui_->log_browser_->append(content);
}

void MqttForm::client_mqtterror(QMqttClient::ClientError)   //Error
{

}

void MqttForm::clietn_disconnected()    //断开连接
{
    ui_->log_browser_->append("连接断开!");
}

void MqttForm::PingButtonSlot()
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

void MqttForm::ConnectButtonSlot()  //连接
{
    InitMqttServer();
    ui_->log_browser_->append(GetCurrentStringTime()+
                              tr("服务器地址：%0\n").arg(mqtt_client_->hostname())+
                              tr("服务器端口：%0\n").arg(mqtt_client_->port())+
                              tr("ClientID：%0\n").arg(mqtt_client_->clientId())+
                              tr("用户名：%0\n").arg(mqtt_client_->username())+
                              tr("密码：%0").arg(mqtt_client_->password()));
}

void MqttForm::SubscribeButtonSlot()    //订阅
{
    qDebug()<<"订阅按钮";
    auto subscriton=mqtt_client_->subscribe(ui_->subscribe_topic_line_->text(),0);
    if(!subscriton)
    {
        QMessageBox::critical(this,tr("Error"),tr("订阅失败！请查看是否连接？"));
        return;
    }
    const QString content = GetCurrentStringTime()
                            + " 订阅的主题 : "
                            + ui_->subscribe_topic_line_->text();
    ui_->log_browser_->append(content);
}

void MqttForm::PublishButtonSlot()  //发布消息
{
    qDebug()<<tr("PublishButtonSlot()");
    topic_=*new QMqttTopicName(ui_->publish_topic_line_->text());
    mqtt_client_->publish(topic_ ,ui_->message_text_->toPlainText().toUtf8());

}

void MqttForm::UnsubscribeButtonSlot()  //取消订阅按钮
{
    qDebug()<<tr("UnsubscribeButtonSlot()");
    mqtt_client_->unsubscribe(ui_->subscribe_topic_line_->text());
    const QString content = GetCurrentStringTime()
                            + " 取消订阅的主题 : "
                            + ui_->subscribe_topic_line_->text();
    ui_->log_browser_->append(content);
}

void MqttForm::on_pushButton_clicked()
{
    jsoner->PackageDeviceDataToJson(ReturnDeviceData());
}

