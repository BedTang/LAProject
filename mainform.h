#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

//Charts类
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QScatterSeries>


#include <QDateTime>
#include <QTimer>

#include <QMessageBox>

#include <QStatusBar>

//QT TCP
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>

//Qt SQL


#include <QSerialPortInfo>

#include "mqttform.h"

#include "TimeFunc.h"

#include "sqliteoperator.h"

#include <QLabel>

#include "dataviewoperator.h"


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

protected:
    Ui::MainForm *ui;

private:
    QStatusBar *statusBar;

    //TCP
    QTcpServer *tcpServer = new QTcpServer();
    QTcpSocket *tcpClient= new QTcpSocket();
    QTcpSocket *currentClient= new QTcpSocket();
    QList<QTcpSocket*> WhattcpClient;

    QTimer *timer;
    QTimer *realTimeTimer;

    int timeCount;

    chartView *chartView;

    tableView *tableView;



    //数据库
    // QString queryString;
    // char openDb();
    // void addDb();
    // void deleteDb();
    // void updateDb();
    // void selectDb();
    // void fastAddDb();
    // QSqlDatabase DB;

public slots:
    void pointHoverd(const QPointF &point, bool state);

private slots:
    void on_pushButton_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_IPpushButton_clicked();

    void on_IPpushButton2_clicked();

    // void pointHoverd(const QPointF &point, bool state);

    void oneSecondAction();

    //TCP客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    int ServerReadData();
    void NewConnectionSlot();

    void addTab();


    void on_devicesTabWidget_tabCloseRequested(int index);
};

    static int mainPort=8080;

#endif // MAINFORM_H
