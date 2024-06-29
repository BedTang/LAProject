#include "sqlite_handler.h"

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
        qDebug()<<database_.lastError();
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

// 创建数据表
void SqlDataHandler::createTable()
{
    // 执行sql语句的对象
    QSqlQuery sqlQuery;
    // 执行sql语句的字符串
    QString createSql = QString("CREATE TABLE {xxx} (\
                                ");
    sqlQuery.prepare(createSql);
    if(!sqlQuery.exec())
    {
        qDebug()<<tr("ERROR: Fail to create table.") << sqlQuery.lastError();
    }
    else
    {
        qDebug()<<tr("Create table successfully!");
    }
}

// 判断数据包是否存在
bool SqlDataHandler::isTableExist(QString& tableName)
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
void SqlDataHandler::quertTable()
{
    QSqlQuery sqlQuery;

    if(!sqlQuery.exec("SELECT * FROM {xxx}"))
    {
        qDebug() << tr("ERROR: Fail to query table.");
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            int age = sqlQuery.value(2).toInt();
            qDebug()<<tr("%1 %2 %3").arg(id).arg(name).arg(age);
        }
    }
}

// 插入单条数据
void SqlDataHandler::signleDataInsert(w2dba &singleData)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("");
    // sqlQuery.bindValue("xxx",xxx);
    if(!sqlQuery.exec())
    {
        qDebug()<< tr("ERROR: Fail to insert data.") << sqlQuery.lastError();
    }
    else
    {
        //
    }
}

// 插入多条数据
void SqlDataHandler::moreInsertData(QList<w2dba>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO student VALUES(?,?,?)");
    QVariantList idList,nameList,ageList;
    for(int i=0; i< moredb.size(); i++)
    {
        idList <<  moredb.at(i).id;
        nameList << moredb.at(i).name;
        ageList << moredb.at(i).age;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(nameList);
    sqlQuery.addBindValue(ageList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
}

// 修改数据
void SqlDataHandler::modifyData(int id, QString name, int age)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE student SET name=?,age=? WHERE id=?");
    sqlQuery.addBindValue(name);
    sqlQuery.addBindValue(age);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << tr("updated data success!");
    }
}

// 删除数据
void SqlDataHandler::deleteData(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM student WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug() << tr("Deleted data success!");
    }
}

// 删除数据表
void SqlDataHandler::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << tr("Deleted table success");
    }
}

// 关闭数据库
void SqlDataHandler::CloseDatabase(void)
{
    database_.close();
}
