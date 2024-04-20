#ifndef MQTT_H
#define MQTT_H


#include <QWidget>

#include <QtMqtt/qmqttclient.h>

class MQTT : public QWidget
{
    Q_OBJECT
public:
    MQTT(QWidget *parent = nullptr);
    ~MQTT();


private:
    QMqttClient *mqttclient;

};

#endif // MQTT_H
