#include "sqlite_handler.h"

extern void DebugOut(QString);

SqlDataHandler::SqlDataHandler()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        database_ = QSqlDatabase::database("qt_sql_default_connection");
    else
    {
        //建立连接
        database_ = QSqlDatabase::addDatabase("QSQLITE");// 数据库名称
        //设置文件名
        database_.setDatabaseName("LAProject.db");
    }
}

// 打开数据库
int SqlDataHandler::OpenDatabase()
{
    if(!database_.open())
    {
        DebugOut(database_.lastError().text());
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle(tr("Error initializing database"));
        msgBox.setText(tr("Can't open the database!"));
        QPushButton *retry = msgBox.addButton(tr("重试"), QMessageBox::AcceptRole);
        QPushButton *ignore = msgBox.addButton(tr("忽略"), QMessageBox::AcceptRole);
        QPushButton *exit = msgBox.addButton(tr("退出"), QMessageBox::AcceptRole);
        msgBox.exec();
        if(msgBox.clickedButton() == retry)
            OpenDatabase();
        if(msgBox.clickedButton() == ignore)
            return 1;
        if(msgBox.clickedButton() == exit)
            return 2;
    }
    // QSqlQuery db_query(database_);
}

// 检查默认数据表是否存在
void SqlDataHandler::CheckDefaultTable()
{
    QString table = "setting";
    if(IsTableExist(table) == false)
    {
    QuerySql("create table setting (tcp_server_port_ int);");
    QuerySql("insert into setting (tcp_server_port_) values(8000)");
    }
    DebugOut("Default table create successed");
}

// 判断数据表是否存在
bool SqlDataHandler::IsTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
        return true;
    else
        return false;
}

// 数据库操作
bool SqlDataHandler::QuerySql(QString extern_query)
{
    QSqlQuery query;
    if(query.exec(extern_query))
    {
        DebugOut("Sql query successed! [" + query.lastQuery() + "]");
        return true;
    }
    else
    {
        DebugOut("Sql query failed! " \
                 "Error statement:" + query.lastQuery() + \
                 "Error reason:" + query.lastError().text());
        return false;
    }
}

// TCP服务器端口查询
int SqlDataHandler::QuertTcpPort(QString column , QString table)
{
    QSqlQuery query;
    query.exec(QString("select %0 from %1").arg(column).arg(table));
    query.next();
    return query.value(0).toInt();
}

// 返回历史数据表格
void SqlDataHandler::GetHistoryData(int index ,QStandardItemModel *table_model_ ,QTableView *table)
{
    QStringList header;
    header<<tr("ID")
           <<tr("温度")
           <<tr("湿度")
           <<tr("烟雾")
           <<tr("光照")
           <<tr("电量")
           <<tr("X轴速度")
           <<tr("X轴加速度")
           <<tr("X轴位移")
           <<tr("Y轴速度")
           <<tr("Y轴加速度")
           <<tr("Y轴位移")
           <<tr("Z轴速度")
           <<tr("Z轴加速度")
           <<tr("Z轴位移")
           <<tr("电流")
           <<tr("时间");
    table_model_->setHorizontalHeaderLabels(header);
    table->setModel(table_model_);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setHighlightSections(false);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);// 禁止修改
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table_model_->removeRows(0, table_model_->rowCount());
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(QString("select * from device_%0").arg(index)))
        DebugOut(tr("ERROR: Fail to query table."));
    else
    {
        while(sqlQuery.next())
        {
            QList<QStandardItem*> add_items;
            add_items << new QStandardItem(sqlQuery.value(0).toString())
                      << new QStandardItem(sqlQuery.value(1).toString())
                      << new QStandardItem(sqlQuery.value(2).toString())
                      << new QStandardItem(sqlQuery.value(3).toString())
                      << new QStandardItem(sqlQuery.value(4).toString())
                      << new QStandardItem(sqlQuery.value(5).toString())
                      << new QStandardItem(sqlQuery.value(6).toString())
                      << new QStandardItem(sqlQuery.value(7).toString())
                      << new QStandardItem(sqlQuery.value(8).toString())
                      << new QStandardItem(sqlQuery.value(9).toString())
                      << new QStandardItem(sqlQuery.value(10).toString())
                      << new QStandardItem(sqlQuery.value(11).toString())
                      << new QStandardItem(sqlQuery.value(12).toString())
                      << new QStandardItem(sqlQuery.value(13).toString())
                      << new QStandardItem(sqlQuery.value(14).toString())
                      << new QStandardItem(sqlQuery.value(15).toString())
                      << new QStandardItem(sqlQuery.value(16).toString());
            table_model_->appendRow(add_items);
        }
        table->resizeColumnsToContents();
    }
}

// 删除历史数据
void SqlDataHandler::WipeHistoryData(int index)
{
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(QString("delete from device_%0").arg(index)))
        DebugOut(tr("ERROR: Fail to delete table."));
}

// 多数据写入数据库
void SqlDataHandler::MoreInsertData(int device_id ,QList<int> data_list)
{
    QString str =QString("device_%0").arg(device_id);
    if(IsTableExist(str) == false)
        QuerySql(QString("create table device_%0 (ID int,Temperature int,Humidity int,Smoke int,Light int,Battery int,X_V int,X_A int,X_D int,Y_V int,Y_A int,Y_D int,Z_V int,Z_A int,Z_D int,Current int,Time int);").arg(device_id));

    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery query;
    query.prepare(QString("insert into device_%0 values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,strftime('%Y-%m-%d %H:%M:%f'))").arg(device_id));

    query.addBindValue(data_list.at(0));
    query.addBindValue(data_list.at(1));
    query.addBindValue(data_list.at(2));
    query.addBindValue(data_list.at(3));
    query.addBindValue(data_list.at(4));
    query.addBindValue(data_list.at(5));
    query.addBindValue(data_list.at(6));
    query.addBindValue(data_list.at(7));
    query.addBindValue(data_list.at(8));
    query.addBindValue(data_list.at(9));
    query.addBindValue(data_list.at(10));
    query.addBindValue(data_list.at(11));
    query.addBindValue(data_list.at(12));
    query.addBindValue(data_list.at(13));
    query.addBindValue(data_list.at(14));
    query.addBindValue(data_list.at(15));
    if(!query.exec())
        DebugOut("Error"); // 进行批处理，如果出错就输出错误
}

// 关闭数据库
void SqlDataHandler::CloseDatabase(void)
{
    database_.close();
}

// 修改数据 xxxx
// void SqlDataHandler::ModifyData(int id, QString name, int age)
// {
//     QSqlQuery sqlQuery;
//     sqlQuery.prepare("UPDATE student SET name=?,age=? WHERE id=?");
//     sqlQuery.addBindValue(name);
//     sqlQuery.addBindValue(age);
//     sqlQuery.addBindValue(id);
//     if(!sqlQuery.exec())
//     {
//         DebugOut(sqlQuery.lastError().text());
//     }
//     else
//     {
//         DebugOut(tr("updated data success!"));
//     }
// }

// 删除数据 xxxx
// void SqlDataHandler::DeleteData(int id)
// {
//     QSqlQuery sqlQuery;

//     sqlQuery.exec(QString("DELETE FROM student WHERE id = %1").arg(id));
//     if(!sqlQuery.exec())
//     {
//         DebugOut(sqlQuery.lastError().text());
//     }
//     else
//     {
//         DebugOut(tr("Deleted data success!"));
//     }
// }

// 删除数据表 xxxx
// void SqlDataHandler::DeleteTable(QString& tableName)
// {
//     QSqlQuery sqlQuery;

//     sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
//     if(sqlQuery.exec())
//     {
//         DebugOut(sqlQuery.lastError().text());
//     }
//     else
//     {
//         DebugOut(tr("Deleted table success"));
//     }
// }
