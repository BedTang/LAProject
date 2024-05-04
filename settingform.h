#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QWidget>

namespace Ui {
class SettingForm;
}

class SettingForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingForm(QWidget *parent = nullptr);
    ~SettingForm();

private slots:
    void on_MQTTFormBtn_clicked();

    void on_SerialFormBtn_clicked();

    void on_NetForm_clicked();

private:
    Ui::SettingForm *ui;
};

#endif // SETTINGFORM_H
