#ifndef DEVICES_DATA_HANDLE_H
#define DEVICES_DATA_HANDLE_H

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
    std::tuple<int, int, int, int, int> dataHandle(QList<int>&, QString str = NULL);

private:

};

#endif // DEVICES_DATA_HANDLE_H
