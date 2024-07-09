#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QWidget>
#include <QTimer>
#include <QStatusBar>

// 数据库处理
#include "sqlite_handler.h"

// 设置界面
#include "setting_form.h"

// 设备处理
#include "devices_chart_handler.h"
#include "devices_data_handler.h"
#include "devices_table_handler.h"

// TCP处理
#include "tcp_handle.h"

#include "history_form.h"

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

    TcpHandle *tcp_;

    SqlDataHandler *sqldb_;

    QTimer *timer_;
    QTimer *real_time_timer_;
    QTimer *online_check_timer_;
    int time_count_;

    ChartView *chart_view_;
    TableView *table_view_;

    SettingForm *setting_form_;

    HistoryForm *history_form_;

    QMap<int ,ChartView*> chart_view_object_map_;

    JsonHandler *json_;

    bool server_status_ = false;

    QList<int> data_list_;

    // static int tcp_server_port_;

public slots:
    void AddNewDeviceToTab(QString ip);
    void AddDevice(QHostAddress);

private slots:
    void TimeMessage();
    void DeviceTabCloseTabBtnClicked(int index);
    void StartServerBtnClicked();
    void SaveBtnClicked();
    void SettingBtnClicked();
    void CleanDataBtnClicked();
    void TableClicked(const QModelIndex &);

signals:
    void SendDataToChart(QList<int>);
};
#endif // MAIN_FORM_H
