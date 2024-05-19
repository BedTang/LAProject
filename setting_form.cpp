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

void SettingForm::on_pushButton_clicked()
{
    port=ui->lineEdit->text().toInt();
}

