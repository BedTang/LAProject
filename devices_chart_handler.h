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

#include <QFont>

#include <QDateTime>

#include <QLabel>


#include <QTimer>// 测试用
#include <QRandomGenerator>

QT_CHARTS_USE_NAMESPACE


class ChartView : public QWidget
{
    Q_OBJECT

public:
    ChartView(QWidget *parent = nullptr);
    ~ChartView();

    QChartView* AddChart();
    QChartView* DeleteChart();

    static int dataViewCount;

private:
    void initChart();

    QChartView *chartView = new QChartView;

    QTimer *timer;

    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QLineSeries *line;
    QLineSeries *line2;
    QLineSeries *line3;
    QLineSeries *line4;

    QLabel *valueLabel;
    QPoint curPos;

    // QGraphicsView *ChartView;
public slots:
    void PointHoverd(const QPointF &point, bool state);
    void ReceiveDataToUpdate(int ,int ,int ,int);

private slots:
    // void pointHoverd(const QPointF &point, bool state);
    void TimeOut();
};
#endif // INTERFACE_H
