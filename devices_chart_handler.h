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

#include <QPushButton>

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

    QChartView *chart_view_ = new QChartView;

    QTimer *timer;

    QChart *chart_;
    QDateTimeAxis *axisX_;
    QValueAxis *axisY_;
    QLineSeries *temperature_line_;
    QLineSeries *humidity_line_;
    QLineSeries *smoke_density_line_;
    QLineSeries *light_intensity_line_;

    QPushButton *chart_switch_button_;

    QLabel *valueLabel;
    QPoint curPos;

    virtual void resizeEvent(QResizeEvent *event) override;

    bool Event(QEvent *event);

    // QGraphicsView *ChartView;
public slots:
    void PointHoverd(const QPointF &point, bool state);
    void ReceiveDataToUpdate(int ,int ,int ,int);

private slots:
    // void pointHoverd(const QPointF &point, bool state);
    void TimeOut();
};
#endif // INTERFACE_H
