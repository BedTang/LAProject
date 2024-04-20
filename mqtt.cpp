#include "mqtt.h"

MQTT::MQTT(QWidget *parent)
    : QWidget(parent)
{
    mqttclient=new QMqttClient(this);
}

MQTT::~MQTT()
{

}
