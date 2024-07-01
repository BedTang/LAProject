#include "main_form.h"

#include <QSortFilterProxyModel>

inline QString GetCurrentStringTime()
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("[ hh:mm:ss ]");
}

inline void DebugOut(QString message)
{
    QDateTime Time= QDateTime::currentDateTime();
    qDebug()<<Time.toString("[ hh:mm:ss ] ")+message;
}

MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::MainForm)
    , timer_(new QTimer(this))
    , time_count_(0)
{
    // UI初始化
    ui_->setupUi(this);
    this->setWindowTitle(tr("分布式工业节点与电机智能监测系统"));

    ui_->devices_tab->tabBar()->setTabButton(0 ,QTabBar::RightSide ,nullptr);
    ui_->devices_tab->setContentsMargins(0,0,0,0);
    // ui_->tab->setStyleSheet("border-image:url(:/0.jpg)");

    ui_->splitter_->setStretchFactor(0,2);
    ui_->splitter_->setStretchFactor(1,3);

    // TCP初始化
    tcp_ = new TcpHandle(this ,ui_);
    tcp_->RetrieveNativeIp();

    // devicesView初始化
    table_view_ = new TableView(this, ui_->devices_table_view_);

    // 数据库初始化
    sqldb_ = new SqlDataHandler();
    sqldb_->OpenDatabase();
    sqldb_->CheckDefaultTable();

    setting_form_ = new SettingForm(nullptr, sqldb_->QuertSqlData("tcp_server_port_" ,"setting"));

    // 定时器
    online_check_timer_ = new QTimer(this);
    timer_->start(1000);

    // Json解析器
    json_ = new JsonHandler();

    // 状态栏
    ui_->statusBar->setSizeGripEnabled(false);

    // 信号与槽
    connect(timer_,SIGNAL(timeout()), this, SLOT(TimeMessage()));
    connect(ui_->start_server, &QPushButton::clicked, this, &MainForm::StartServerBtnClicked);
    connect(ui_->save_button, &QPushButton::clicked, this, &MainForm::SaveBtnClicked);
    connect(ui_->test_button, &QPushButton::clicked, this, &MainForm::CleanDataBtnClicked);
    connect(ui_->setting_button, &QPushButton::clicked, this, &MainForm::SettingBtnClicked);
    connect(ui_->devices_tab ,&QTabWidget::tabCloseRequested ,this ,&MainForm::DeviceTabCloseTabBtnClicked);
    connect(ui_->devices_table_view_, &QTableView::clicked, this, &MainForm::TableClicked);
    connect(tcp_, &TcpHandle::RequestAddDevice, this,&MainForm::AddDevice);
    // connect(tcp_ ,&tcpHandle::RequestDataHandle ,json_ ,&jsonHandle::ReciveDataHandler);
}

MainForm::~MainForm()
{
    delete ui_;
}

void MainForm::AddNewDeviceToTab(QString ip) // 创建新的设备标签
{
    DebugOut("MainForm::AddNewDeviceToTab()<<");

    if(data_list_.at(0) == '\0')
    {
        DebugOut("AddNewDeviceToTab()<<if(data_list_.at(0) == '\0')");
        return;
    }
    if(device_list_.contains(data_list_.at(0)))
    {
        DebugOut("AddNewDeviceToTab()<<if(device_list_.contains(data_list_.at(0)))");
        ui_->devices_tab->addTab(chart_view_->GetStackedWidgetObject(),tr("设备ID：%0").arg(data_list_.at(0)));
        table_view_->addData(data_list_.at(0) ,ip);
    }
}

void MainForm::AddDevice(QHostAddress current_ip) // 添加设备
{
    DebugOut("MainForm::AddDevice()<<");
    data_list_ = json_->ReciveDataHandler(device_list_ ,tcp_->GetMessage());
    sqldb_->MoreInsertData(data_list_.at(0) ,data_list_);
    QString mqtt_json = json_->PackageDeviceDataToJson(data_list_);
    setting_form_->GetMqttPoint()->SetJsonMessage(mqtt_json);
    if(!online_device_list_.contains(current_ip))
    {
        online_device_list_.append(current_ip);
        chart_view_object_map_.insert(data_list_.at(0) ,chart_view_ = new ChartView(this ,table_view_ ,data_list_.at(0)));
        AddNewDeviceToTab(current_ip.toString());
    }

    connect(this ,&MainForm::SendDataToChart, chart_view_object_map_.value(data_list_.at(0)) ,&ChartView::ReceiveDataToUpdate);
    emit SendDataToChart(data_list_);
    table_view_->UpdateTableContent(data_list_.at(0));
    disconnect(this ,&MainForm::SendDataToChart, chart_view_object_map_.value(data_list_.at(0)) ,&ChartView::ReceiveDataToUpdate);
}

void MainForm::TimeMessage() // 更新状态栏时间
{
    ui_->statusBar->showMessage("当前系统时间："+GetCurrentStringTime());
}

void MainForm::DeviceTabCloseTabBtnClicked(int index) // 关闭指定设备标签页
{
    chart_view_ = qobject_cast<class ChartView *>(sender());
    delete chart_view_object_map_.value(1);
    chart_view_object_map_.remove(1);
    ui_->devices_tab->removeTab(index);
    delete chart_view_;
    // table_view_->deleteView(index);// 暂时取消设备列表的删除
}

void MainForm::StartServerBtnClicked() // TCP服务器控制
{
    if(ui_->start_server->text()==tr("启动服务器"))
    {
        tcp_->ServerListening(server_status_ ,sqldb_->QuertSqlData("tcp_server_port_" ,"setting"));
        ui_->logBrowser->append(tr("当前服务器端口:") + QString::number(tcp_->GetPort()));
        ui_->start_server->setText(tr("关闭服务器"));
        return;
    }
    if(ui_->start_server->text()==tr("关闭服务器"))
    {
        tcp_->ServerListening(server_status_ ,sqldb_->QuertSqlData("tcp_server_port_" ,"setting"));
        ui_->start_server->setText(tr("启动服务器"));
        return;
    }
}

void MainForm::SaveBtnClicked() // 数据保存
{
    DebugOut("SaveBtnClicked()<<");
}

void MainForm::SettingBtnClicked() // 显示设置界面
{
    DebugOut("SettingBtnClicked()<<");
    setting_form_->show();
}

void MainForm::CleanDataBtnClicked() // 清空数据
{
    DebugOut("CleanDataBtnClicked()<<");
    ui_->logBrowser->clearHistory();
    ui_->logBrowser->clear();
    device_list_.clear();
    online_device_list_.clear();
    table_view_->DeleteModelData();
    ui_->devices_tab->removeTab(1);
}

void MainForm::TableClicked(const QModelIndex &index) // 设备列表向设备标签页跳转
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
