#ifndef DEVICES_DATA_HANDLER_H
#define DEVICES_DATA_HANDLER_H

#include <QWidget>

#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>

#include <QDateTime>

class JsonHandler : public QWidget
{
    Q_OBJECT
public:
    QString PackageDeviceDataToJson(QList<int>);

private:

public slots:
    QList<int> ReciveDataHandler(QList<int>&, QString str = NULL);

signals:
    void UpdateData(int temperature ,int humidity ,int smoke ,int light);

};

#endif // DEVICES_DATA_HANDLER_H
