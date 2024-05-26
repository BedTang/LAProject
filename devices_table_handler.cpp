#include "devices_table_handler.h"

extern QString updateRealTimeData();

// QString updateRealTimeData()
// {
//     QDateTime dateTime= QDateTime::currentDateTime();
//     return dateTime.toString("hh:mm:ss:z");
// }

TableView::TableView(QWidget *parent, QTableView *table)
    : QWidget(parent)
    ,table_(table)
{
    table_model_ = new QStandardItemModel(table);

    initTable(table);

    qDebug()<<tr("tableViewClass()<<class tableview created successfully!");
}

QStandardItemModel* TableView::GetTableModel()
{
    return table_model_;
}

void TableView::addData(int device_id ,QString ip)
{
    QList<QStandardItem*> add_items;
    // QStandardItem *item = new QStandardItem();
    add_items << new QStandardItem(QString("%0").arg(device_id))
              << new QStandardItem(QString("%0").arg(ip))
              // << new QStandardItem("deviceType")
              << new QStandardItem("在线")
              << new QStandardItem(updateRealTimeData())
              << new QStandardItem(updateRealTimeData());
    table_model_->appendRow(add_items);
    table_->resizeColumnsToContents();
}

void TableView::deleteView(int index)
{
    table_model_->removeRows(index, index);
}

void TableView::DeleteModelData()
{
    table_model_->clear();
}

void TableView::initTable(QTableView *table)
{
    QStringList header;
    header<<tr("名称")
           <<tr("地址")
           // <<tr("类型")
           <<tr("状态")
           <<tr("上线时间")
           <<tr("最后在线时间");
    table_model_->setHorizontalHeaderLabels(header);
    table->setModel(this->GetTableModel());
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setHighlightSections(false);
    table->verticalHeader()->setVisible(false);
    // table->horizontalHeader()->setFont(QFont(QFont::defaultFamily(),14))
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);// 禁止修改
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}
