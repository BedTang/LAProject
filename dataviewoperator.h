#ifndef DATAVIEWOPERATOR_H
#define DATAVIEWOPERATOR_H

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

#include <QDateTime>

#include <QLabel>


#include <QTimer>// 测试用
#include <QRandomGenerator>

QT_CHARTS_USE_NAMESPACE

class chartView : public QWidget
{
    Q_OBJECT
public:
    chartView(QWidget *parent = nullptr, QWidget *table = nullptr);
    ~chartView();
    QChartView* addChart();

    QChartView* deleteChart();
    QScatterSeries *scatter;
    QScatterSeries *scatter_2;


private:
    QChartView *m_chartView = new QChartView;


    QTimer *timer;

    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QLineSeries *line;

    QStandardItemModel *tableModel;


    QLabel *m_valueLabel;
    QPoint curPos;



    // QGraphicsView *chartView;
public slots:
    void pointHoverd(const QPointF &point, bool state);

private slots:
    // void pointHoverd(const QPointF &point, bool state);
    void timeOut();
};

class tableView : public QWidget
{
    Q_OBJECT
public:
    tableView(QWidget *parent = nullptr, QWidget *table = nullptr);
    QStandardItemModel* addTable();


private:

    QStandardItemModel *tableModel;

private slots:

};

#endif // DATAVIEWOPERATOR_H
