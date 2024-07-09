#ifndef SQLITE_HANDLER_H
#define SQLITE_HANDLER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QMessageBox>
#include <QPushButton>
#include <QObject>
#include <QVariant>

#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>

typedef struct
{
    int device_id_value_;
    int temperature_value_;
    int humidity_value_;
    int smoke_density_value_;
    int light_intensity_value_;
    int battery_level_value_;
    int x_speed_value_;
    int x_acceleration_value_;
    int x_displacement_value_;
    int y_speed_value_;
    int y_acceleration_value_;
    int y_displacement_value_;
    int z_speed_value_;
    int z_acceleration_value_;
    int z_displacement_value_;
    int current_value_;
}device_data;

class SqlDataHandler:QObject
{
public:
    SqlDataHandler();

    int QuertTcpPort(QString ,QString);
    bool IsTableExist(QString&);
    int OpenDatabase();
    bool QuerySql(QString);
    void MoreInsertData(int ,QList<int>);
    void WriteDataToSql();
    void GetHistoryData(int ,QStandardItemModel* ,QTableView*);
    void WipeHistoryData(int);
    void CloseDatabase(void);
    void CheckDefaultTable();
    // void DeleteData(int id);
    // void DeleteTable(QString& tableName);
    // void ModifyData(int id, QString name, int age);

private:
    QSqlDatabase database_;

};

#endif // SQLITE_HANDLER_H
