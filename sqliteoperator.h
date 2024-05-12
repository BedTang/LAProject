#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QObject>


typedef struct
{
    int id;
    QString name;
    int age;
}w2dba;


class SqliteOperator:QObject
{
public:
    SqliteOperator();
    void closeDb(void);
    void deleteData(int id);
    void deleteTable(QString& tableName);
    void createTable();
    bool isTableExist(QString&);
    void modifyData(int id, QString name, int age);
    void moreInsertData(QList<w2dba> &moreData);
    bool openDb();
    void quertTable();
    void signleDataInsert(w2dba &singleData);






private:
    QSqlDatabase database;
    QString queryString;

};

#endif // SQLITEOPERATOR_H
