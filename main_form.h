#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QWidget>

// Charts
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QScatterSeries>


#include <QTimer>

#include <QStatusBar>

// TCP
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>

// 串口
#include <QSerialPortInfo>

// #include "mqtt_form.h"

#include "sqlite_handle.h"

#include "setting_form.h"

// 设备处理
#include "devices_view_handle.h"
#include "devices_data_handle.h"

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

    //返回当前时间
    void updateSeries(float point,unsigned char);

    // void updateChartData();

    void updateAxisRange();

    QList<int> device_list;

protected:


private:
    QStatusBar *statusBar;
    Ui::MainForm *ui;

    // TCP
    QTcpServer *tcpServer = new QTcpServer();
    QTcpSocket *tcpClient= new QTcpSocket();
    QTcpSocket *currentClient= new QTcpSocket();
    QList<QTcpSocket*> WhattcpClient;

    // 数据库
    DatabaseHandle *db;

    // 定时器
    QTimer *timer;
    QTimer *realTimeTimer;
    int timeCount;

    // 设备显示
    chartViewClass *chartView;
    tableViewClass *tableView;

    // 设置界面
    SettingForm *settingForm;

    // Json解析
    jsonHandle *json;

private slots:
    void on_startServer_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void oneSecondAction();

    QString ServerReadData();
    void NewConnectionSlot();

    void addView();

    void on_devicesTab_tabCloseRequested(int index);
};

static int tcpServerPort=8888;

#endif // MAIN_FORM_H
