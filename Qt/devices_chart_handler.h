#ifndef INTERFACE_H
#define INTERFACE_H

#include <QHBoxLayout>
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

// #include <QList>

#include <QTimer>// 测试用
#include <QRandomGenerator>

#include <QStackedWidget>
#include <QGraphicsLayout>

#include "devices_table_handler.h"

QT_CHARTS_USE_NAMESPACE


class ChartView : public QWidget
{
    Q_OBJECT

public:
    ChartView(QWidget *parent = nullptr ,TableView *table = nullptr ,int device_id = 0);
    ~ChartView();

    QChartView* GetChartViewObject();
    QChartView* DeleteChart();

    static int dataViewCount;

    // Public Stacked Widget Related Initialization
    QStackedWidget* GetStackedWidgetObject();
    bool GetOnlineFlag();

private:
    QList<int> data_list_;
    QTimer *timer;
    QTimer *online_check_timer_;

    TableView * internal_table_model_;

    int device_id_ = 0;

    QList<QChartView*> chart_view_list;
    QList<QWidget*> widget_part_list;
    QList<QHBoxLayout*> hbox_layout_list;
    QList<QPushButton*> switch_next_chart_button_list;
    QList<QPushButton*> switch_previous_chart_button_list;

    QWidget *widget_part_ =new QWidget();
    QWidget *widget_part1_ =new QWidget();
    QWidget *widget_part2_ =new QWidget();
    QWidget *widget_part3_ =new QWidget();
    QWidget *widget_part4_ =new QWidget();

    QChartView *chart_view_part_ = new QChartView;
    QChartView *chart_view_part1_ = new QChartView;
    QChartView *chart_view_part2_ = new QChartView;
    QChartView *chart_view_part3_ = new QChartView;
    QChartView *chart_view_part4_ = new QChartView;

    QChart *chart_part_;
    QChart *chart_part1_;
    QChart *chart_part2_;
    QChart *chart_part3_;
    QChart *chart_part4_;

    QLabel *point_value_label_;

    QLineSeries *temperature_line_;
    QLineSeries *humidity_line_;
    QLineSeries *smoke_density_line_;
    QLineSeries *light_intensity_line_;

    QLineSeries *current_line_;

    QLineSeries *x_speed_line_;
    QLineSeries *x_acceleration_line_;
    QLineSeries *x_displacement_line_;

    QLineSeries *y_speed_line_;
    QLineSeries *y_acceleration_line_;
    QLineSeries *y_displacement_line_;

    QLineSeries *z_speed_line_;
    QLineSeries *z_acceleration_line_;
    QLineSeries *z_displacement_line_;

    QPushButton *switch_next_chart_button_;
    QPushButton *switch_previous_chart_button_;

    QPoint curPos;

    // Private Stacked Widget Related Initialization
    void InitStackedWidget();
    QStackedWidget *stacked_widget_;

    void InitChartPart();// Common Sensors
    void InitChartPart1();// Fundamental Wave And Harmoonics Wave
    void InitChartPart2();// X
    void InitChartPart3();// Y
    void InitChartPart4();// Z

    bool online_flag_;

    // QGraphicsView *ChartView;
public slots:
    void PointHoverd(const QPointF &point, bool state);
    void ReceiveDataToUpdate(QList<int>);

    void SwitchNextChartSlot();
    void SwitchPreviousChartSlot();

private slots:
    // void pointHoverd(const QPointF &point, bool state);
    void TimeOut();
    void OnlineCheckSlot();
};
#endif // INTERFACE_H
