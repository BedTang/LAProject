#include "devices_data_handle.h"

jsonHandle::jsonHandle()
{

}

jsonHandle::~jsonHandle()
{

}

std::tuple<int, int, int, int, int> jsonHandle::dataHandle(QList<int> &list, QString str)
{
    QJsonParseError jsonError_;

    QJsonDocument doc_ = QJsonDocument::fromJson(str.toUtf8(), &jsonError_);
    if (jsonError_.error != QJsonParseError::NoError && !doc_.isNull())
    {
        qDebug() << ("Json格式错误！") << jsonError_.error;
        exit(0);
    }

    QJsonObject root_obj_ = doc_.object();

    QJsonValue id_value_ = root_obj_.value("id");
    QJsonValue temperature_value_ = root_obj_.value("temperature");
    QJsonValue humidity_value_ = root_obj_.value("humidity");
    QJsonValue smoke_value_ = root_obj_.value("smoke");
    QJsonValue light_intensity_value_ = root_obj_.value("Light intensity");
    QJsonValue battery_level_value_ = root_obj_.value("battery level");

    if(!list.contains(id_value_.toInt()))
    {
        list.append(id_value_.toInt());
        qDebug()<< tr("添加设备ID：%0").arg(id_value_.toInt());
        return std::make_tuple(id_value_.toInt(), temperature_value_.toInt(), humidity_value_.toInt() ,light_intensity_value_.toInt() ,battery_level_value_.toInt());
    }

    // return list.at(id_value_.toInt()-1)<<
    //            id_value_.toInt()<<
    //            temperature_value_.toInt()<<
    //            humidity_value_.toInt()<<
    //        light_intensity_value_.toInt()<<
    //        battery_level_value_.toInt();
    return std::make_tuple(NULL, NULL, NULL, NULL, NULL);
}


