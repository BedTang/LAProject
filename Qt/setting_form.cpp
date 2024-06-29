#include "setting_form.h"
#include "ui_setting_form.h"

SettingForm::SettingForm(QWidget *parent, int port)
    : QWidget(parent)
    , ui(new Ui::SettingForm)
    , port(port)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");
    setAttribute(Qt::WA_QuitOnClose,false);
    ui->lineEdit->setText(QString::number(port));
    mqttform = new MqttForm();
}

SettingForm::~SettingForm()
{
    delete ui;
}

MqttForm *SettingForm::GetMqttPoint()
{
    return mqttform;
}


void SettingForm::on_MQTTFormBtn_clicked()
{
    mqttform->show();
}


void SettingForm::on_SerialFormBtn_clicked()
{
    SerialForm *serialform=new SerialForm;
    serialform->show();
}

void SettingForm::on_pushButton_clicked()
{
    port=ui->lineEdit->text().toInt();
}

