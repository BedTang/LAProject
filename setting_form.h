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

private slots:
    void on_MQTTFormBtn_clicked();

    void on_SerialFormBtn_clicked();


    void on_pushButton_clicked();

private:
    Ui::SettingForm *ui;

    int port;
};

#endif // SETTING_FORM_H
