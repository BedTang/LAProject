#include "settingform.h"
#include "ui_settingform.h"

#include "serialform.h"
#include "mqttform.h"

SettingForm::SettingForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingForm)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");
    setAttribute(Qt::WA_QuitOnClose,false);
}

SettingForm::~SettingForm()
{
    delete ui;
}


void SettingForm::on_MQTTFormBtn_clicked()
{
    MQTTForm *mqttform=new MQTTForm;
    mqttform->show();
}


void SettingForm::on_SerialFormBtn_clicked()
{
    SerialForm *serialform=new SerialForm;
    serialform->show();
}

