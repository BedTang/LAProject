#include "devices_data_handler.h"

extern void DebugOut(QString);

QString JsonHandler::PackageDeviceDataToJson(QList<int> data_list)
{
    QJsonObject root_json;
    QJsonObject params_json;

    QJsonObject params_temperature_json;
    params_temperature_json.insert("value" ,data_list.at(1));

    QJsonObject params_humidity_json;
    params_humidity_json.insert("value" ,data_list.at(2));

    QJsonObject params_light_intensity_json;
    params_light_intensity_json.insert("value" ,data_list.at(4));

    QJsonObject params_smoke_density_json;
    params_smoke_density_json.insert("value" ,data_list.at(3));

    QJsonObject params_battery_level_json;
    params_battery_level_json.insert("value" ,data_list.at(5));


    QJsonObject params_x_speed_json;
    params_x_speed_json.insert("value" ,data_list.at(6));

    QJsonObject params_x_acceleration_json;
    params_x_acceleration_json.insert("value" ,data_list.at(7));

    QJsonObject params_x_displacement_json;
    params_x_displacement_json.insert("value" ,data_list.at(8));


    QJsonObject params_y_speed_json;
    params_y_speed_json.insert("value" ,data_list.at(9));

    QJsonObject params_y_acceleration_json;
    params_y_acceleration_json.insert("value" ,data_list.at(10));

    QJsonObject params_y_displacement_json;
    params_y_displacement_json.insert("value" ,data_list.at(11));


    QJsonObject params_z_speed_json;
    params_z_speed_json.insert("value" ,data_list.at(12));

    QJsonObject params_z_acceleration_json;
    params_z_acceleration_json.insert("value" ,data_list.at(13));

    QJsonObject params_z_displacement_json;
    params_z_displacement_json.insert("value" ,data_list.at(14));

    QJsonObject params_current_json;
    params_current_json.insert("value" ,data_list.at(15));

    params_json.insert("temperature" ,params_temperature_json);
    params_json.insert("humidity" ,params_humidity_json);
    params_json.insert("light_intensity" ,params_light_intensity_json);
    params_json.insert("smoke_density" ,params_smoke_density_json);

    params_json.insert("x_speed" ,params_x_speed_json);
    params_json.insert("x_acceleration" ,params_x_acceleration_json);
    params_json.insert("x_displacement" ,params_x_displacement_json);

    params_json.insert("y_speed" ,params_y_speed_json);
    params_json.insert("y_acceleration" ,params_y_acceleration_json);
    params_json.insert("y_displacement" ,params_y_displacement_json);

    params_json.insert("z_speed" ,params_z_speed_json);
    params_json.insert("z_acceleration" ,params_z_acceleration_json);
    params_json.insert("z_displacement" ,params_z_displacement_json);

    params_json.insert("current" ,params_current_json);

    root_json.insert("id" ,QString("%0").arg(QDateTime::currentSecsSinceEpoch()));

    root_json.insert("params" ,params_json);
    root_json.insert("version" ,"1.0");

    QJsonDocument json;
    json.setObject(root_json);
    QByteArray string = json.toJson(QJsonDocument::Compact);
    qDebug()<<"Parse Json Data to String:"+string;
    qDebug();
    return string;
}

QList<int> JsonHandler::ReciveDataHandler(QList<int> &list, QString str)
{
    QJsonParseError jsonError_;

    QJsonDocument doc_ = QJsonDocument::fromJson(str.toUtf8(), &jsonError_);
    if (jsonError_.error != QJsonParseError::NoError && !doc_.isNull())
    {
        qDebug() << tr("Json格式错误！") << jsonError_.error;
        exit(0);
    }

    list.clear();

    QJsonObject root_obj_ = doc_.object();

    QJsonValue device_id_value_ = root_obj_.value("id");
    QJsonValue temperature_value_ = root_obj_.value("temperature");
    QJsonValue humidity_value_ = root_obj_.value("humidity");
    QJsonValue smoke_density_value_ = root_obj_.value("smoke");
    QJsonValue light_intensity_value_ = root_obj_.value("Light_intensity");
    QJsonValue battery_level_value_ = root_obj_.value("battery_level");
    QJsonValue x_speed_value_ = root_obj_.value("x_speed");
    QJsonValue x_acceleration_value_ = root_obj_.value("x_acceleration");
    QJsonValue x_displacement_value_ = root_obj_.value("x_displacement");
    QJsonValue y_speed_value_ = root_obj_.value("y_speed");
    QJsonValue y_acceleration_value_ = root_obj_.value("y_acceleration");
    QJsonValue y_displacement_value_ = root_obj_.value("y_displacement");
    QJsonValue z_speed_value_ = root_obj_.value("z_speed");
    QJsonValue z_acceleration_value_ = root_obj_.value("z_acceleration");
    QJsonValue z_displacement_value_ = root_obj_.value("z_displacement");
    QJsonValue current_value_ = root_obj_.value("current");

    QList<int> return_data_list;
    return_data_list.append(device_id_value_.toInt());
    return_data_list.append(temperature_value_.toInt());
    return_data_list.append(humidity_value_.toInt());
    return_data_list.append(smoke_density_value_.toInt());
    return_data_list.append(light_intensity_value_.toInt());
    return_data_list.append(battery_level_value_.toInt());
    return_data_list.append(x_speed_value_.toInt());
    return_data_list.append(x_acceleration_value_.toInt());
    return_data_list.append(x_displacement_value_.toInt());
    return_data_list.append(y_speed_value_.toInt());
    return_data_list.append(y_acceleration_value_.toInt());
    return_data_list.append(y_displacement_value_.toInt());
    return_data_list.append(z_speed_value_.toInt());
    return_data_list.append(z_acceleration_value_.toInt());
    return_data_list.append(z_displacement_value_.toInt());
    return_data_list.append(current_value_.toInt());

    if(!list.contains(device_id_value_.toInt()))
    {
        list.append(device_id_value_.toInt());
        qDebug()<< tr("dataHandle()<<添加设备ID：%0").arg(device_id_value_.toInt());
        return return_data_list;
    }
    return_data_list[0]='\0';
    return return_data_list;
}


