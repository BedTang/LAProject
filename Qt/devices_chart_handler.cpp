#include "devices_chart_handler.h"
#include <QDebug>

extern QString updateRealTimeData();

QString updateRealTimeData()
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("hh:mm:ss:z");
}

ChartView::ChartView(QWidget *parent ,TableView *table_object ,int device_id)
    : QWidget(parent)
    , timer(new QTimer(this))
    , point_value_label_(new QLabel(parent))
{
    internal_table_model_ = table_object;

    online_check_timer_ = new QTimer(this);
    online_check_timer_->start(5000);

    device_id_ = device_id;

    stacked_widget_ = new QStackedWidget(parent);
    stacked_widget_->setContentsMargins(0,0,0,0);

    chart_part_ = new QChart();
    chart_part_->setMargins(QMargins(0 ,0 ,0 ,0));
    chart_part_->layout()->setContentsMargins(0 ,0 ,0 ,0);

    chart_part1_ = new QChart();
    chart_part1_->setMargins(QMargins(0 ,0 ,0 ,0));
    chart_part1_->layout()->setContentsMargins(0 ,0 ,0 ,0);

    chart_part2_ = new QChart();
    chart_part2_->setMargins(QMargins(0 ,0 ,0 ,0));
    chart_part2_->layout()->setContentsMargins(0 ,0 ,0 ,0);

    chart_part3_ = new QChart();
    chart_part3_->setMargins(QMargins(0 ,0 ,0 ,0));
    chart_part3_->layout()->setContentsMargins(0 ,0 ,0 ,0);

    chart_part4_ = new QChart();
    chart_part4_->setMargins(QMargins(0 ,0 ,0 ,0));
    chart_part4_->layout()->setContentsMargins(0 ,0 ,0 ,0);

    // widget_part_list
    for (int i = 0; i < 5; ++i)
    {
        widget_part_ = new QWidget(this);
        widget_part_->setContentsMargins(0,0,0,0);
        QHBoxLayout* pLayout = new QHBoxLayout();
        pLayout->setContentsMargins(0,0,0,0);
        pLayout->setSpacing(0);
        // switch_next_chart_button_list
        QSizePolicy sizePolice(QSizePolicy::Preferred, QSizePolicy::Preferred);

        switch_next_chart_button_ = new QPushButton(this);
        switch_next_chart_button_->setFixedWidth(20);
        switch_next_chart_button_->setContentsMargins(0,0,0,0);
        switch_next_chart_button_->setSizePolicy(sizePolice);
        switch_next_chart_button_->setText(">>");
        switch_next_chart_button_list.append(switch_next_chart_button_);
        connect(switch_next_chart_button_ ,&QPushButton::clicked ,this ,&ChartView::SwitchNextChartSlot);

        // chart_view_list
        chart_view_part_ = new QChartView(this);
        chart_view_part_->setContentsMargins(0,0,0,0);
        // chart_view_part_->set
        chart_view_part_->setSizePolicy(sizePolice);
        // chart_view_part_->setMargins
        chart_view_list.append(chart_view_part_);

        // switch_previous_chart_button_list
        switch_previous_chart_button_ = new QPushButton(this);
        switch_previous_chart_button_->setFixedWidth(20);
        switch_previous_chart_button_->setContentsMargins(0,0,0,0);
        switch_previous_chart_button_->setSizePolicy(sizePolice);
        switch_previous_chart_button_->setText("<<");
        switch_previous_chart_button_list.append(switch_previous_chart_button_);
        connect(switch_previous_chart_button_,&QPushButton::clicked ,this ,&ChartView::SwitchPreviousChartSlot);

        pLayout->addWidget(switch_previous_chart_button_);
        pLayout->addWidget(chart_view_part_);
        pLayout->addWidget(switch_next_chart_button_);

        widget_part_->setLayout(pLayout);
        widget_part_list.append(widget_part_);
    }

    InitStackedWidget();

    timer->start(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(TimeOut()));
    connect(online_check_timer_ ,SIGNAL(timeout()), this, SLOT(OnlineCheckSlot()));
}

ChartView::~ChartView()
{
    qDebug()<<tr("销毁chartView");
}

QChartView* ChartView::DeleteChart()
{
    return NULL;
}

inline void ChartView::InitStackedWidget()
{
    qDebug()<<"InitStackedWidget()";
    InitChartPart();
    InitChartPart1();
    InitChartPart2();
    InitChartPart3();
    InitChartPart4();


    stacked_widget_->addWidget(widget_part_list.at(0));
    stacked_widget_->addWidget(widget_part_list.at(1));
    stacked_widget_->addWidget(widget_part_list.at(2));
    stacked_widget_->addWidget(widget_part_list.at(3));
    stacked_widget_->addWidget(widget_part_list.at(4));

    qDebug()<<stacked_widget_->count();
}

void ChartView::InitChartPart()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis(this);
    QValueAxis *axisY_ = new QValueAxis(this);

    temperature_line_ = new QLineSeries(this);
    humidity_line_ = new QLineSeries(this);
    smoke_density_line_ = new QLineSeries(this);
    light_intensity_line_ = new QLineSeries(this);
    chart_part_scatter_  = new QScatterSeries(this);
    chart_part_scatter2_  = new QScatterSeries(this);

    chart_part_->addAxis(axisX_, Qt::AlignBottom);
    chart_part_->addAxis(axisY_, Qt::AlignLeft);
    chart_part_->addSeries(temperature_line_);
    chart_part_->addSeries(humidity_line_);
    chart_part_->addSeries(smoke_density_line_);
    chart_part_->addSeries(light_intensity_line_);
    chart_part_->addSeries(chart_part_scatter_);
    chart_part_->addSeries(chart_part_scatter2_);

    // 设置X轴
    axisX_->setTickCount(7);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    // axisX_->setTitleText(tr("时间"));// 名称
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,300);
    axisY_->setGridLineVisible(true);
    axisY_->setTickCount(6);
    axisY_->setMinorTickCount(5);

    // 温度
    temperature_line_->setName(tr("温度"));
    temperature_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    temperature_line_->attachAxis(axisY_);
    temperature_line_->setPointsVisible(true);


    // 湿度
    humidity_line_->setName(tr("湿度"));
    humidity_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    humidity_line_->attachAxis(axisY_);
    humidity_line_->setPointsVisible(true);

    // 烟雾浓度
    smoke_density_line_->setName(tr("烟雾浓度"));
    smoke_density_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    smoke_density_line_->attachAxis(axisY_);
    smoke_density_line_->setPointsVisible(true);

    // 光照强度
    light_intensity_line_->setName(tr("光照强度"));
    light_intensity_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    light_intensity_line_->attachAxis(axisY_);
    light_intensity_line_->setPointsVisible(true);

    chart_view_list.at(0)->setChart(chart_part_);
    chart_view_list.at(0)->setRenderHint(QPainter::Antialiasing);

    // 散点图（边框）
    chart_part_scatter_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part_scatter_->setBorderColor(QColor(21, 100, 255)); // 离散点边框颜色
    chart_part_scatter_->setBrush(QBrush(QColor(21, 100, 255)));// 离散点背景色
    chart_part_scatter_->setMarkerSize(7); // 离散点大小
    chart_part_scatter_->attachAxis(axisX_);
    chart_part_scatter_->attachAxis(axisY_);

    // 散点图（中心）
    chart_part_scatter2_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part_scatter2_->setMarkerSize(3);// 点大小
    chart_part_scatter2_->attachAxis(axisX_);
    chart_part_scatter2_->attachAxis(axisY_);

    chart_part_->legend()->markers(chart_part_scatter_).first()->setVisible(false);// 隐藏图例
    chart_part_->legend()->markers(chart_part_scatter2_).first()->setVisible(false);

    // 数据点显示
    point_value_label_->setStyleSheet(QString("QLabel{color:#1564FF;"
                                      "font-family:\"Microsoft Yahei\";"
                                      "font-size:12px; font-weight:bold;"
                                      "background-color:rgba(21, 100, 255, 51);"
                                      "border-radius:4px;"
                                      "text-align:center;}"));
    point_value_label_->setFixedSize(60, 35);
    point_value_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    point_value_label_->hide();

    connect(chart_part_scatter_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    // connect(humidity_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    // connect(smoke_density_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    // connect(light_intensity_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::InitChartPart1()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis();
    QValueAxis *axisY_ = new QValueAxis();

    current_line_ = new QLineSeries();
    chart_part1_scatter_  = new QScatterSeries();
    chart_part1_scatter2_  = new QScatterSeries();

    chart_part1_->addAxis(axisX_, Qt::AlignBottom);
    chart_part1_->addAxis(axisY_, Qt::AlignLeft);
    chart_part1_->addSeries(current_line_);

    chart_part1_->addSeries(chart_part1_scatter_);
    chart_part1_->addSeries(chart_part1_scatter2_);

    // 设置X轴
    axisX_->setTickCount(5);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,300);
    axisY_->setGridLineVisible(true);
    axisY_->setTickCount(6);
    axisY_->setMinorTickCount(5);

    // Fundamental Wave Line
    current_line_->setName(tr("电流"));
    current_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    current_line_->attachAxis(axisY_);
    current_line_->setPointsVisible(true);


    // 散点图（边框）
    chart_part1_scatter_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part1_scatter_->setBorderColor(QColor(21, 100, 255)); // 离散点边框颜色
    chart_part1_scatter_->setBrush(QBrush(QColor(21, 100, 255)));// 离散点背景色
    chart_part1_scatter_->setMarkerSize(8); // 离散点大小
    chart_part1_scatter_->attachAxis(axisX_);
    chart_part1_scatter_->attachAxis(axisY_);

    // 散点图（中心）
    chart_part1_scatter2_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part1_scatter2_->setMarkerSize(4);// 点大小
    chart_part1_scatter2_->attachAxis(axisX_);
    chart_part1_scatter2_->attachAxis(axisY_);

    chart_part1_->legend()->markers(chart_part1_scatter_).first()->setVisible(false);// 隐藏图例
    chart_part1_->legend()->markers(chart_part1_scatter2_).first()->setVisible(false);

    chart_view_list.at(1)->setChart(chart_part1_);
    chart_view_list.at(1)->setRenderHint(QPainter::Antialiasing);

    // 数据点显示
    point_value_label_->setStyleSheet(QString("QLabel{color:#1564FF;"
                                              "font-family:\"Microsoft Yahei\";"
                                              "font-size:12px; font-weight:bold;"
                                              "background-color:rgba(21, 100, 255, 51);"
                                              "border-radius:4px;"
                                              "text-align:center;}"));
    point_value_label_->setFixedSize(60, 35);
    point_value_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    point_value_label_->hide();

    connect(current_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    // connect(harmonics_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::InitChartPart2()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis(this);
    QValueAxis *axisY_ = new QValueAxis(this);

    x_speed_line_ = new QLineSeries(this);
    x_acceleration_line_ = new QLineSeries(this);
    x_displacement_line_ = new QLineSeries(this);
    chart_part2_scatter_  = new QScatterSeries(this);
    chart_part2_scatter2_  = new QScatterSeries(this);

    chart_part2_->addAxis(axisX_, Qt::AlignBottom);
    chart_part2_->addAxis(axisY_, Qt::AlignLeft);
    chart_part2_->addSeries(x_speed_line_);
    chart_part2_->addSeries(x_acceleration_line_);
    chart_part2_->addSeries(x_displacement_line_);
    chart_part2_->addSeries(chart_part2_scatter_);
    chart_part2_->addSeries(chart_part2_scatter2_);

    // 设置X轴
    axisX_->setTickCount(7);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    // axisX_->setTitleText(tr("时间"));// 名称
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,300);
    axisY_->setGridLineVisible(true);
    axisY_->setTickCount(6);
    axisY_->setMinorTickCount(5);
    // Speed Line
    x_speed_line_->setName(tr("X轴速度"));
    x_speed_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    x_speed_line_->attachAxis(axisY_);
    x_speed_line_->setPointsVisible(true);

    // Acceleration Line
    x_acceleration_line_->setName(tr("X轴加速度"));
    x_acceleration_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    x_acceleration_line_->attachAxis(axisY_);
    x_acceleration_line_->setPointsVisible(true);

    // Displacement Line
    x_displacement_line_->setName(tr("X轴位移"));
    x_displacement_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    x_displacement_line_->attachAxis(axisY_);
    x_displacement_line_->setPointsVisible(true);

    // 散点图（边框）
    chart_part2_scatter_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part2_scatter_->setBorderColor(QColor(21, 100, 255)); // 离散点边框颜色
    chart_part2_scatter_->setBrush(QBrush(QColor(21, 100, 255)));// 离散点背景色
    chart_part2_scatter_->setMarkerSize(7); // 离散点大小
    chart_part2_scatter_->attachAxis(axisX_);
    chart_part2_scatter_->attachAxis(axisY_);

    // 散点图（中心）
    chart_part2_scatter2_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part2_scatter2_->setMarkerSize(3);// 点大小
    chart_part2_scatter2_->attachAxis(axisX_);
    chart_part2_scatter2_->attachAxis(axisY_);

    chart_part2_->legend()->markers(chart_part2_scatter_).first()->setVisible(false);// 隐藏图例
    chart_part2_->legend()->markers(chart_part2_scatter2_).first()->setVisible(false);

    chart_view_list.at(2)->setChart(chart_part2_);
    chart_view_list.at(2)->setRenderHint(QPainter::Antialiasing);

    // 数据点显示
    point_value_label_->setStyleSheet(QString("QLabel{color:#1564FF;"
                                              "font-family:\"Microsoft Yahei\";"
                                              "font-size:12px; font-weight:bold;"
                                              "background-color:rgba(21, 100, 255, 51);"
                                              "border-radius:4px;"
                                              "text-align:center;}"));
    point_value_label_->setFixedSize(60, 35);
    point_value_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    point_value_label_->hide();

    connect(x_speed_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(x_acceleration_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(x_displacement_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::InitChartPart3()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis(this);
    QValueAxis *axisY_ = new QValueAxis(this);

    y_speed_line_ = new QLineSeries(this);
    y_acceleration_line_ = new QLineSeries(this);
    y_displacement_line_ = new QLineSeries(this);
    chart_part3_scatter_  = new QScatterSeries(this);
    chart_part3_scatter2_  = new QScatterSeries(this);

    chart_part3_->addAxis(axisX_, Qt::AlignBottom);
    chart_part3_->addAxis(axisY_, Qt::AlignLeft);
    chart_part3_->addSeries(y_speed_line_);
    chart_part3_->addSeries(y_acceleration_line_);
    chart_part3_->addSeries(y_displacement_line_);
    chart_part3_->addSeries(chart_part3_scatter_);
    chart_part3_->addSeries(chart_part3_scatter2_);

    // 设置X轴
    axisX_->setTickCount(7);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    // axisX_->setTitleText(tr("时间"));// 名称
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,300);
    axisY_->setGridLineVisible(true);
    axisY_->setTickCount(6);
    axisY_->setMinorTickCount(5);

    // Speed Line
    y_speed_line_->setName(tr("Y轴速度"));
    y_speed_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    y_speed_line_->attachAxis(axisY_);
    y_speed_line_->setPointsVisible(true);

    // Acceleration Line
    y_acceleration_line_->setName(tr("Y轴加速度"));
    y_acceleration_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    y_acceleration_line_->attachAxis(axisY_);
    y_acceleration_line_->setPointsVisible(true);

    // Displacement Line
    y_displacement_line_->setName(tr("Y轴位移"));
    y_displacement_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    y_displacement_line_->attachAxis(axisY_);
    y_displacement_line_->setPointsVisible(true);

    // 散点图（边框）
    chart_part3_scatter_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part3_scatter_->setBorderColor(QColor(21, 100, 255)); // 离散点边框颜色
    chart_part3_scatter_->setBrush(QBrush(QColor(21, 100, 255)));// 离散点背景色
    chart_part3_scatter_->setMarkerSize(7); // 离散点大小
    chart_part3_scatter_->attachAxis(axisX_);
    chart_part3_scatter_->attachAxis(axisY_);

    // 散点图（中心）
    chart_part3_scatter2_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part3_scatter2_->setMarkerSize(3);// 点大小
    chart_part3_scatter2_->attachAxis(axisX_);
    chart_part3_scatter2_->attachAxis(axisY_);

    chart_part3_->legend()->markers(chart_part3_scatter_).first()->setVisible(false);// 隐藏图例
    chart_part3_->legend()->markers(chart_part3_scatter2_).first()->setVisible(false);

    chart_view_list.at(3)->setChart(chart_part3_);
    chart_view_list.at(3)->setRenderHint(QPainter::Antialiasing);

    // 数据点显示
    point_value_label_->setStyleSheet(QString("QLabel{color:#1564FF;"
                                              "font-family:\"Microsoft Yahei\";"
                                              "font-size:12px; font-weight:bold;"
                                              "background-color:rgba(21, 100, 255, 51);"
                                              "border-radius:4px;"
                                              "text-align:center;}"));
    point_value_label_->setFixedSize(60, 35);
    point_value_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    point_value_label_->hide();

    connect(chart_part3_scatter_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::InitChartPart4()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis(this);
    QValueAxis *axisY_ = new QValueAxis(this);

    z_speed_line_ = new QLineSeries(this);
    z_acceleration_line_ = new QLineSeries(this);
    z_displacement_line_ = new QLineSeries(this);
    chart_part4_scatter_  = new QScatterSeries(this);
    chart_part4_scatter2_  = new QScatterSeries(this);

    chart_part4_->addAxis(axisX_, Qt::AlignBottom);
    chart_part4_->addAxis(axisY_, Qt::AlignLeft);
    chart_part4_->addSeries(z_speed_line_);
    chart_part4_->addSeries(z_acceleration_line_);
    chart_part4_->addSeries(z_displacement_line_);
    chart_part4_->addSeries(chart_part4_scatter_);
    chart_part4_->addSeries(chart_part4_scatter2_);

    // 设置X轴
    axisX_->setTickCount(7);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    // axisX_->setTitleText(tr("时间"));// 名称
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,300);
    axisY_->setGridLineVisible(true);
    axisY_->setTickCount(6);
    axisY_->setMinorTickCount(5);

    // Speed Line
    z_speed_line_->setName(tr("Z轴速度"));
    z_speed_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    z_speed_line_->attachAxis(axisY_);
    z_speed_line_->setPointsVisible(true);

    // Acceleration Line
    z_acceleration_line_->setName(tr("Z轴加速度"));
    z_acceleration_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    z_acceleration_line_->attachAxis(axisY_);
    z_acceleration_line_->setPointsVisible(true);

    // Displacement Line
    z_displacement_line_->setName(tr("Z轴位移"));
    z_displacement_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    z_displacement_line_->attachAxis(axisY_);
    z_displacement_line_->setPointsVisible(true);

    // 散点图（边框）
    chart_part4_scatter_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part4_scatter_->setBorderColor(QColor(21, 100, 255)); // 离散点边框颜色
    chart_part4_scatter_->setBrush(QBrush(QColor(21, 100, 255)));// 离散点背景色
    chart_part4_scatter_->setMarkerSize(7); // 离散点大小
    chart_part4_scatter_->attachAxis(axisX_);
    chart_part4_scatter_->attachAxis(axisY_);

    // 散点图（中心）
    chart_part4_scatter2_->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    chart_part4_scatter2_->setMarkerSize(3);// 点大小
    chart_part4_scatter2_->attachAxis(axisX_);
    chart_part4_scatter2_->attachAxis(axisY_);

    chart_part4_->legend()->markers(chart_part4_scatter_).first()->setVisible(false);// 隐藏图例
    chart_part4_->legend()->markers(chart_part4_scatter2_).first()->setVisible(false);

    chart_view_list.at(4)->setChart(chart_part4_);
    chart_view_list.at(4)->setRenderHint(QPainter::Antialiasing);

    // 数据点显示
    point_value_label_->setStyleSheet(QString("QLabel{color:#1564FF;"
                                              "font-family:\"Microsoft Yahei\";"
                                              "font-size:12px; font-weight:bold;"
                                              "background-color:rgba(21, 100, 255, 51);"
                                              "border-radius:4px;"
                                              "text-align:center;}"));
    point_value_label_->setFixedSize(60, 35);
    point_value_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    point_value_label_->hide();

    connect(chart_part4_scatter_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::OnlineCheckSlot()
{
    // qDebug()<<"OnlineCheckSlot";
    if(online_flag_ == true)
    {
        internal_table_model_->ModifyOnlineStatus(online_flag_ ,device_id_);
        online_flag_ = false;
    }
    else if(online_flag_ == false)
    {
        internal_table_model_->ModifyOnlineStatus(online_flag_ ,device_id_);
    }
}

QStackedWidget *ChartView::GetStackedWidgetObject()
{
    return stacked_widget_;
}

bool ChartView::GetOnlineFlag()
{
    return online_flag_;
}

void ChartView::PointHoverd(const QPointF &point, bool state)
{
    QDateTime time = QDateTime::currentDateTime();
    if (state)
    {
        point_value_label_->setText(QString::asprintf(time.toString("hh:mm:ss").toUtf8()+"\n%1.0f", point.y()));

        QPoint curPos = mapFromGlobal(QCursor::pos());
        point_value_label_->move(curPos.x() - point_value_label_->width() / 2, curPos.y() - point_value_label_->height() * 1.5);//移动数值
        point_value_label_->show();//显示出来
    }
    else
        point_value_label_->hide();//进行隐藏
}

void ChartView::ReceiveDataToUpdate(QList<int> data_list)
{
    qDebug()<<"增添数据点";
    temperature_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(1));
    humidity_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(2));
    smoke_density_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(3));
    light_intensity_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(4));
    chart_part_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(1));
    chart_part_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(2));
    chart_part_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(3));
    chart_part_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(4));
    chart_part_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(1));
    chart_part_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(2));
    chart_part_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(3));
    chart_part_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(4));

    current_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(15));
    chart_part1_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(15));
    chart_part1_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(15));

    x_speed_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(6));
    x_acceleration_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(7));
    x_displacement_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(8));
    chart_part2_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(6));
    chart_part2_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(7));
    chart_part2_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(8));
    chart_part2_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(6));
    chart_part2_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(7));
    chart_part2_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(8));



    y_speed_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(9));
    y_acceleration_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(10));
    y_displacement_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(11));
    chart_part3_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(9));
    chart_part3_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(10));
    chart_part3_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(11));
    chart_part3_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(9));
    chart_part3_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(10));
    chart_part3_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(11));


    z_speed_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(12));
    z_acceleration_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(13));
    z_displacement_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(14));
    chart_part4_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(12));
    chart_part4_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(13));
    chart_part4_scatter_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(14));
    chart_part4_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(12));
    chart_part4_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(13));
    chart_part4_scatter2_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(14));

    online_flag_ = true;
    internal_table_model_->ModifyOnlineStatus(true ,device_id_);
}

void ChartView::SwitchNextChartSlot()
{
    stacked_widget_->setCurrentIndex(stacked_widget_->currentIndex()+1);
}

void ChartView::SwitchPreviousChartSlot()
{
    stacked_widget_->setCurrentIndex(stacked_widget_->currentIndex()-1);
}

void ChartView::TimeOut()
{
    // qreal y_range = line->;
    // qDebug()<< y_range;
    chart_part_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    chart_part1_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    chart_part2_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    chart_part3_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    chart_part4_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
}

