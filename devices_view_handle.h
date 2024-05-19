#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
// Charts相关类
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QScatterSeries>
#include <QLegendMarker>

// Table相关类
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>

#include <QFont>

#include <QDateTime>

#include <QLabel>


#include <QTimer>// 测试用
#include <QRandomGenerator>

QT_CHARTS_USE_NAMESPACE

class chartViewClass : public QWidget
{
    Q_OBJECT
public:
    chartViewClass(QWidget *parent = nullptr);
    ~chartViewClass();
    QChartView* addChart();

    QChartView* deleteChart();
    QScatterSeries *scatter;
    QScatterSeries *scatter_2;

    static int dataViewCount;


private:

    void initChart();

    QChartView *chartView = new QChartView;

    QTimer *timer;

    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QLineSeries *line;

    QStandardItemModel *tableModel;


    QLabel *valueLabel;
    QPoint curPos;



    // QGraphicsView *chartViewClass;
public slots:
    void pointHoverd(const QPointF &point, bool state);

private slots:
    // void pointHoverd(const QPointF &point, bool state);
    void timeOut();
};

class tableViewClass : public QWidget
{
    Q_OBJECT
public:
    tableViewClass(QWidget *parent = nullptr, QTableView *table = nullptr);
    QStandardItemModel* addTable();

    void addData();
    void deleteView(int index);


private:
    void initTable(QTableView *table);
    QStandardItemModel *tableModel;
    QTableView *table;

private slots:

};

#endif // INTERFACE_H
