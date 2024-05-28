#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QWidget>

#include <QTimer>

#include <QStatusBar>

// 串口
// #include <QSerialPortInfo>

#include "sqlite_handler.h"

#include "setting_form.h"

// 设备处理
#include "devices_chart_handler.h"
#include "devices_data_handler.h"
#include "devices_table_handler.h"

// TCP
#include "tcp_handle.h"

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui {
class MainForm;
}
QT_END_NAMESPACE

class MainForm : public QWidget
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();

    QList<int> device_list_;
    QList<QHostAddress> online_device_list_;

private:
    QStatusBar *status_bar_;
    Ui::MainForm *ui_;

    // TCP
    tcpHandle *tcp_;

    // 数据库
    SqlDataHandler *database_;

    // 定时器
    QTimer *timer_;
    QTimer *real_time_timer_;
    int time_count_;

    // 设备显示
    ChartView *chart_view_;
    TableView *table_view_;

    // 设置界面
    SettingForm *setting_form_;

    QMap<int ,ChartView*> chart_view_object_map;

    // Json解析
    jsonHandle *json_;

    bool server_status_ = false;

    std::tuple<int ,int ,int ,int ,int ,int> data_list;

public slots:
    void AddDeviceView(QString ip);
    void AddDevice(QHostAddress);

private slots:
    void oneSecondAction();
    void devices_tab_close_requested(int index);
    void start_server_clicked();
    void save_button_clicked();
    void setting_button_clicked();
    void test_button_clicked();
    void TableClicked(const QModelIndex &);

signals:
    void SendDataToChart(int ,int ,int ,int);
};

static bool send_data_to_chart_status;
static int tcpServerPort=8080;

#endif // MAIN_FORM_H
