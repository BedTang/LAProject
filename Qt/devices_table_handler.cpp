#include "devices_table_handler.h"

extern QString GetCurrentStringTime();
extern void DebugOut(QString);

TableView::TableView(QWidget *parent, QTableView *table)
    : QWidget(parent)
    ,table_(table)
{
    table_model_ = new QStandardItemModel(table);
    initTable(table);
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
              << new QStandardItem("在线")
              << new QStandardItem(GetCurrentStringTime())
              << new QStandardItem(GetCurrentStringTime());
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

QStandardItemModel* TableView::GetModelObject()
{
    return table_model_;
}

void TableView::initTable(QTableView *table)
{
    QStringList header;
    header<<tr("名称")
           <<tr("地址")
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

void TableView::UpdateTableContent(int device_id)
{
    DebugOut("TableView::UpdateTableContent()<<");
    for (int i = 0; i < table_model_->rowCount(); ++i) {
        QModelIndex index;
        index = table_model_->index(i,0);
        qDebug()<<tr(QString(table_model_->data(index).toString()).toUtf8());
        if(table_model_->data(index).toInt() == device_id)
        {
            qDebug()<<"OK";
            index = table_model_->index(i ,4);
            // table_model_->data(index).toString() = updateRealTimeData();
            table_model_->setData(index ,GetCurrentStringTime());
        }
    }
}

void TableView::ModifyOnlineStatus(bool online_flag, int device_id)
{
    for (int i = 0; i < table_model_->rowCount(); ++i) {
        QModelIndex index;
        index = table_model_->index(i,0);
        if(table_model_->data(index).toInt() == device_id)
        {
            qDebug()<<online_flag;
            index = table_model_->index(i ,2);
            if(online_flag == true)
            {
                table_model_->setData(index ,tr("在线"));
            }
            else if(online_flag == false)
            {
                table_model_->setData(index ,tr("离线"));
            }
        }
    }
}
