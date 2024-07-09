#include "history_form.h"
#include "ui_history_form.h"

#include "sqlite_handler.h"

HistoryForm::HistoryForm(QWidget *parent ,SqlDataHandler *object)
    : QWidget(parent ,Qt::WindowStaysOnTopHint)
    , ui_(new Ui::HistoryForm)
    , sql_object_(object)

{
    setAttribute(Qt::WA_QuitOnClose,false);
    ui_->setupUi(this);

    table_model_ = new QStandardItemModel(ui_->data_table_view_);
    this->setWindowTitle("历史数据");

    connect(ui_->load_data_button_, &QPushButton::clicked, this, &HistoryForm::LoadHistoryData);
    connect(ui_->wipe_data_button_, &QPushButton::clicked, this, &HistoryForm::WipeHistoryData);
}

HistoryForm::~HistoryForm()
{
    delete ui_;
}

void HistoryForm::LoadHistoryData()
{
    sql_object_->GetHistoryData(ui_->device_combobox_->currentIndex()+1 ,table_model_ ,ui_->data_table_view_);
}

void HistoryForm::WipeHistoryData()
{
    sql_object_->WipeHistoryData(ui_->device_combobox_->currentIndex()+1);
}
