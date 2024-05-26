#ifndef DEVICES_TABLE_HANDLER_H
#define DEVICES_TABLE_HANDLER_H

#include <QWidget>

#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>

#include <QDateTime>
#include <QDebug>

class TableView : public QWidget
{
    Q_OBJECT

public:
    TableView(QWidget *parent = nullptr, QTableView *table = nullptr);
    QStandardItemModel* GetTableModel();

    void addData(int device_id ,QString ip);
    void deleteView(int index);
    void DeleteModelData();

private:
    void initTable(QTableView*);

    QStandardItemModel *table_model_;
    QTableView *table_;

private slots:
};
#endif // DEVICES_TABLE_HANDLER_H
