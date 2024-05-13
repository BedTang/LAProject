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

    //节点一
    QChart *chart=new QChart();
    QLineSeries *series=new QLineSeries;
    QLineSeries *series_2=new QLineSeries;

    //节点二
    QChart *chart2=new QChart();
    QLineSeries *series2=new QLineSeries;

    //节点三

    // QScatterSeries *scaseries3 = (QScatterSeries *)ui->graphicsView3->chart()->series().at(0);

    QChart *chart3=new QChart();
    QChart *chart3_2=new QChart();
    QLineSeries *series3=new QLineSeries;
    QScatterSeries *scaseries3 = new QScatterSeries();
    QScatterSeries *scaseries3_1 = new QScatterSeries();
    QDateTimeAxis *axisXDate3 = new QDateTimeAxis();
    QValueAxis *axisY3=new QValueAxis();
    QLabel *m_valueLabel;

    //TCP
    QTcpServer *tcpServer = new QTcpServer();
    QTcpSocket *tcpClient= new QTcpSocket();
    QTcpSocket *currentClient= new QTcpSocket();
    QList<QTcpSocket*> WhattcpClient;

    QTimer *timer;
    QTimer *realTimeTimer;

    int timeCount;


    //数据库
    // QString queryString;
    // char openDb();
    // void addDb();
    // void deleteDb();
    // void updateDb();
    // void selectDb();
    // void fastAddDb();
    // QSqlDatabase DB;

private slots:
    void on_pushButton_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_IPpushButton_clicked();

    void on_IPpushButton2_clicked();

    void pointHoverd(const QPointF &point, bool state);

    void oneSecondAction();

    //TCP客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    int ServerReadData();
    void NewConnectionSlot();


};

    static int mainPort=8080;

#endif // MAINFORM_H
