#ifndef SQLITE_HANDLER_H
#define SQLITE_HANDLER_H

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

class SqlDataHandler:QObject
{
public:
    SqlDataHandler();
    void CloseDatabase(void);
    void deleteData(int id);
    void deleteTable(QString& tableName);
    void createTable();
    bool isTableExist(QString&);
    void modifyData(int id, QString name, int age);
    void moreInsertData(QList<w2dba> &moreData);
    bool OpenDatabase();
    void quertTable();
    void signleDataInsert(w2dba &singleData);

private:
    QSqlDatabase database_;
    QString queryString;

};

#endif // SQLITE_HANDLER_H
