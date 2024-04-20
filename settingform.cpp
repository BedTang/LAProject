#include "settingform.h"
#include "ui_settingform.h"

#include "serialassistantform.h"

SettingForm::SettingForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingForm)
{
    ui->setupUi(this);
}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::on_pushButton_2_clicked()
{
    SerialAssistantForm *SerialAsstForm=new SerialAssistantForm;
    SerialAsstForm->show();
}

