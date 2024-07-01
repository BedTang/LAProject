#include "sqlite_handler.h"
#include "qdebug.h"

extern void DebugOut(QString);

SqlDataHandler::SqlDataHandler()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database_ = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        //建立连接
        database_ = QSqlDatabase::addDatabase("QSQLITE");// 数据库名称
        //设置文件名
        database_.setDatabaseName("LAProject.db");
    }
}

// 打开数据库
bool SqlDataHandler::OpenDatabase()
{
    if(!database_.open())
    {
        DebugOut(database_.lastError().text());
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle(tr("Error initializing database"));
        msgBox.setText(tr("Can't open the database!"));
        QPushButton *retry = msgBox.addButton(tr("Retry"), QMessageBox::AcceptRole);
        QPushButton *ignore = msgBox.addButton(tr("Ignore"), QMessageBox::AcceptRole);
        QPushButton *exit = msgBox.addButton(tr("Exit"), QMessageBox::AcceptRole);
        msgBox.exec();
        if(msgBox.clickedButton() == retry)
        {
            OpenDatabase();
        }
        if(msgBox.clickedButton() == ignore)
        {
            return 1;
        }
        if(msgBox.clickedButton() == exit)
        {
            return 2;
        }
    }
    QSqlQuery db_query(database_);
}

// 检查默认数据表
void SqlDataHandler::CheckDefaultTable()
{
    QString table = "setting";
    if(IsTableExist(table) == false)
    {
    QuerySql("create table setting (tcp_server_port_ int);");
    QuerySql("insert into setting (tcp_server_port_) values(8080)");
    }
    DebugOut("Default table create successed");
}

// 判断数据表是否存在
bool SqlDataHandler::IsTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 查询数据表
void SqlDataHandler::QuertTable()
{
    QSqlQuery sqlQuery;

    if(!sqlQuery.exec("SELECT * FROM {xxx}"))
    {
        DebugOut(tr("ERROR: Fail to query table."));
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            int age = sqlQuery.value(2).toInt();
            DebugOut(tr("%1 %2 %3").arg(id).arg(name).arg(age));
        }
    }
}

// 插入单条数据
void SqlDataHandler::signleDataInsert(device_data &singleData)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("");
    // sqlQuery.bindValue("xxx",xxx);
    if(!sqlQuery.exec())
    {
        DebugOut(tr("ERROR: Fail to insert data.") + sqlQuery.lastError().text());
    }
    else
    {
    }
}

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

int SqlDataHandler::QuertSqlData(QString column , QString table)
{
    QSqlQuery query;
    query.exec(QString("select %0 from %1").arg(column).arg(table));
    query.next();
    return query.value(0).toInt();
}

// 插入多条数据
void SqlDataHandler::MoreInsertData(int device_id ,QList<int> data_list)
{
    QString str =QString("device_%0").arg(device_id);
    if(IsTableExist(str) == false)
    {
        QuerySql(QString("create table device_%0 (id int,temperature int,humidity int,smoke_density int,light_intensity int,battery_level int,x_speed int,x_acceleration int,x_displacement int,y_speed int,y_acceleration int,y_displacement int,z_speed int,z_acceleration int,z_displacement int,current int,timestamp int);").arg(device_id));
    }
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
    query.exec(); // 进行批处理，如果出错就输出错误
}

// 修改数据
void SqlDataHandler::ModifyData(int id, QString name, int age)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE student SET name=?,age=? WHERE id=?");
    sqlQuery.addBindValue(name);
    sqlQuery.addBindValue(age);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        DebugOut(sqlQuery.lastError().text());
    }
    else
    {
        DebugOut(tr("updated data success!"));
    }
}

// 删除数据
void SqlDataHandler::DeleteData(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM student WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        DebugOut(sqlQuery.lastError().text());
    }
    else
    {
        DebugOut(tr("Deleted data success!"));
    }
}

// 删除数据表
void SqlDataHandler::DeleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        DebugOut(sqlQuery.lastError().text());
    }
    else
    {
        DebugOut(tr("Deleted table success"));
    }
}

// 关闭数据库
void SqlDataHandler::CloseDatabase(void)
{
    database_.close();
}
