#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//Charts类
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>

#include <QDateTime>
#include <QTime>

#include <QMessageBox>

//QT TCP
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //返回当前时间
    QString updateRealTimeData();

    void updateSeries(float point);

    void updateChartData();

    void updateAxisRange();



private slots:
    void on_pushButton_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_IPpushButton_clicked();

    void on_IPpushButton2_clicked();



    //TCP客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    int ServerReadData();
    void NewConnectionSlot();

private:
    Ui::Widget *ui;

    //节点一
    QChart *chart=new QChart();
    QLineSeries *series=new QLineSeries;
    QLineSeries *series_2=new QLineSeries;

    //节点二
    QChart *chart2=new QChart();
    QLineSeries *series2=new QLineSeries;

    //节点三
    QChart *chart3=new QChart();
    QLineSeries *series3=new QLineSeries;

    //TCP
    QTcpServer *tcpServer = new QTcpServer();
    QTcpSocket *tcpClient= new QTcpSocket();
    QTcpSocket *currentClient= new QTcpSocket();
    QList<QTcpSocket*> WhattcpClient;

    int timeCount;

};
#endif // WIDGET_H
