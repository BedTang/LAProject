#ifndef SETTING_FORM_H
#define SETTING_FORM_H

#include <QWidget>

#include "serial_form.h"
#include "mqtt_form.h"

namespace Ui {
class SettingForm;
}

class SettingForm : public QWidget
{
    Q_OBJECT

public:
    SettingForm(QWidget *parent = nullptr,int port = 8888);
    ~SettingForm();

    MqttForm* GetMqttPoint();

private:
    Ui::SettingForm *ui_;

    MqttForm *mqtt_form_;

    int port_;

private slots:
    void PortBtn();
    void MqttFormBtn();

    void on_pushButton_clicked();

signals:
    void ChangePort(int);
};

#endif // SETTING_FORM_H
