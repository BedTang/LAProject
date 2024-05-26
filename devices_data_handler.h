#ifndef DEVICES_DATA_HANDLER_H
#define DEVICES_DATA_HANDLER_H

#include <QWidget>

#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>

class jsonHandle : public QWidget
{
    Q_OBJECT
public:
    jsonHandle();
    ~jsonHandle();
    // int datahandleJson(QList<int>, QString str = NULL);
    // std::tuple<int, int, int, int, int ,int> DataHandler(QList<int>&, QString str = NULL);

private:

public slots:
    std::tuple<int, int, int, int, int ,int> ReciveDataHandler(QList<int>&, QString str = NULL);

signals:
    void updatedata(int temperature ,int humidity ,int smoke ,int light);


};

#endif // DEVICES_DATA_HANDLER_H
