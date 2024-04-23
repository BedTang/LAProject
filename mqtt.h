#ifndef MQTT_H
#define MQTT_H


#include <QWidget>
#include <QtCharts/QChartView>
QT_CHARTS_USE_NAMESPACE
#include "ui_mainform.h"


#include <QtMqtt/qmqttclient.h>

class MQTT : public QWidget
{
    Q_OBJECT
public:
    MQTT(QWidget *parent = nullptr);
    ~MQTT();


private:
    Ui::MainForm *ui;
    QMqttClient *client;

private slots:
    void client_connected();
    void client_subscribled(QString,quint8);
    void client_receivemessage(QMqttMessage);
    void client_unsubscrbled(QString);
    void client_mqtterror(QMqttClient::ClientError);
    void clietn_disconnected();

    void on_pushButton4_clicked();
};

#endif // MQTT_H
