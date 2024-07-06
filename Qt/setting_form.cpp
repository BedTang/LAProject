#include "setting_form.h"
#include "ui_setting_form.h"

SettingForm::SettingForm(QWidget *parent, int port)
    : QWidget(parent,Qt::WindowStaysOnTopHint)
    , ui_(new Ui::SettingForm)
    , port_(port)
{
    ui_->setupUi(this);
    this->setWindowTitle("设置");
    setAttribute(Qt::WA_QuitOnClose,false);
    ui_->PortLineEdit->setText(QString::number(port));
    mqtt_form_ = new MqttForm();
    mqtt_form_->InitMqttServer();
    connect(ui_->PortBtn, &QPushButton::clicked, this ,&SettingForm::PortBtn);
    connect(ui_->MQTTFormBtn, &QPushButton::clicked, this ,&SettingForm::MqttFormBtn);
}

SettingForm::~SettingForm()
{
    delete ui_;
}

MqttForm *SettingForm::GetMqttPoint()
{
    return mqtt_form_;
}

void SettingForm::PortBtn()
{
    emit ChangePort(ui_->PortLineEdit->text().toInt());
}

void SettingForm::MqttFormBtn()
{
    mqtt_form_->show();
}


void SettingForm::on_pushButton_clicked()
{
    exit(0);
}

