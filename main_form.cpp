#include "main_form.h"
#include "ui_main_form.h"

#include <QSortFilterProxyModel>

QString updateRealTimeData(int)
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("[ hh:mm:ss ]");
}

MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::MainForm)
    , timer_(new QTimer(this))
    , time_count_(0)
    , setting_form_(new SettingForm(nullptr, tcpServerPort))

{
    ui_->setupUi(this);
    this->setWindowTitle("分布式工业节点与电机智能监测系统");

    // TCP初始化
    tcp_ = new tcpHandle(this ,ui_);
    tcp_->retrieveNativeIp();


    // UI初始化
    ui_->devices_tab->tabBar()->setTabButton(0, QTabBar::RightSide, nullptr);
    ui_->splitter_->setStretchFactor(0,2);
    ui_->splitter_->setStretchFactor(1,3);

    // devicesView初始化
    table_view_ = new TableView(this, ui_->devices_table_view_);

    //数据库初始化
    database_ = new DatabaseHandle();

    // 定时器
    timer_->start(1000);

    // Json解析器
    json_ = new jsonHandle();

    // 数据库
    DatabaseHandle sqldb;

    while(char tmep=sqldb.openDb())
    {
        switch (tmep) {
        case 0:break;
        case 1:return;
        case 2:exit(1);break;
        }
    }

    // 信号与槽
    connect(timer_,SIGNAL(timeout()), this, SLOT(oneSecondAction()));

    connect(ui_->start_server, &QPushButton::clicked, this, &MainForm::start_server_clicked);
    connect(ui_->save_button, &QPushButton::clicked, this, &MainForm::save_button_clicked);
    connect(ui_->test_button, &QPushButton::clicked, this, &MainForm::test_button_clicked);
    connect(ui_->setting_button, &QPushButton::clicked, this, &MainForm::setting_button_clicked);
    connect(ui_->devices_tab ,&QTabWidget::tabCloseRequested ,this ,&MainForm::devices_tab_close_requested);

    connect(tcp_, &tcpHandle::RequestAddDevice, this,&MainForm::AddDevice);

    connect(ui_->devices_table_view_, &QTableView::clicked, this, &MainForm::TableClicked);

    // connect(tcp_ ,&tcpHandle::RequestDataHandle ,json_ ,&jsonHandle::ReciveDataHandler);

}

MainForm::~MainForm()
{
    delete ui_;
}

void MainForm::AddDeviceView(QString ip)
{
    qDebug()<<"进入AddDeviceView()";



    if(std::get<0>(data_list) == '\0')
    {
        return;
    }

    if(device_list_.contains(std::get<0>(data_list)))
    {
        ui_->devices_tab->addTab(chart_view_->AddChart(),tr("设备ID：%0").arg(std::get<0>(data_list)));
        table_view_->addData(std::get<0>(data_list) ,ip);
        // qDebug()<<std::get<0>(list);
    }
}

void MainForm::AddDevice(QHostAddress current_ip)
{
    qDebug()<<"进入AddDevice()";

    data_list = json_->ReciveDataHandler(device_list_ ,tcp_->GetMessage());

    if(!online_device_list_.contains(current_ip))
    {
        qDebug()<<"进入online_device_list_判断";
        online_device_list_.append(current_ip);

        chart_view_object_map.insert(std::get<0>(data_list) ,chart_view_ = new ChartView(this));

        AddDeviceView(current_ip.toString());
    }
    connect(this ,&MainForm::SendDataToChart, chart_view_object_map.value(std::get<0>(data_list)) ,&ChartView::ReceiveDataToUpdate);

    qDebug()<<"数据点"<<std::get<1>(data_list)<<std::get<2>(data_list)<<std::get<3>(data_list)<<std::get<4>(data_list);
    emit SendDataToChart(std::get<1>(data_list) ,std::get<2>(data_list) ,std::get<3>(data_list) ,std::get<4>(data_list));
    disconnect(this ,&MainForm::SendDataToChart, chart_view_object_map.value(std::get<0>(data_list)) ,&ChartView::ReceiveDataToUpdate);
}

void MainForm::oneSecondAction()
{
    ui_->statusBar->showMessage("当前系统时间："+updateRealTimeData(1));
}

//UI按钮功能区
void MainForm::devices_tab_close_requested(int index)
{
    chart_view_ = qobject_cast<class ChartView *>(sender());
    delete chart_view_object_map.value(1);
    chart_view_object_map.remove(1);
    ui_->devices_tab->removeTab(index);
    delete chart_view_;
    // table_view_->deleteView(index);// 暂时取消设备列表的删除
}

void MainForm::start_server_clicked()
{
    if(ui_->start_server->text()==tr("启动服务器"))
    {
        tcp_->server_listening(server_status_ ,tcpServerPort);
        ui_->logBrowser->append(tr("当前服务器端口:") + QString::number(tcp_->GetPort()));
        ui_->start_server->setText(tr("关闭服务器"));
        return;
    }

    if(ui_->start_server->text()==tr("关闭服务器"))
    {
        tcp_->server_listening(server_status_ ,tcpServerPort);
        ui_->start_server->setText(tr("启动服务器"));
        return;
    }
}

void MainForm::save_button_clicked()
{
    qDebug()<<tr("保存按钮");
}

void MainForm::setting_button_clicked()
{
    qDebug()<<tr("设置界面");
    setting_form_->show();
}

void MainForm::test_button_clicked()
{
    qDebug()<<tr("测试按钮");
    ui_->logBrowser->clearHistory();
    ui_->logBrowser->clear();
    device_list_.clear();
    online_device_list_.clear();
    table_view_->DeleteModelData();
    ui_->devices_tab->removeTab(1);
}

void MainForm::TableClicked(const QModelIndex &index)
{
    QModelIndex index_data = table_view_->GetTableModel()->index(index.row(),0);
    int table_id = table_view_->GetTableModel()->data(index_data).toInt();
    for (int i = 0; i < ui_->devices_tab->count(); ++i)
    {
        if(ui_->devices_tab->tabText(i) == QString("设备ID：%0").arg(table_id))
        {
            ui_->devices_tab->setCurrentIndex(i);
        }
    }
}
