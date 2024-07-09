#include "devices_chart_handler.h"

extern void DebugOut(QString);

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
        chart_view_part_->setRubberBand(QChartView::RectangleRubberBand);
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
    DebugOut("Destroy ChartView()");
}

QChartView* ChartView::DeleteChart()
{
    return NULL;
}

inline void ChartView::InitStackedWidget()
{
    DebugOut("ChartView::InitStackedWidget()<<");
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
}

void ChartView::InitChartPart()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis(this);
    QValueAxis *axisY_left_ = new QValueAxis(this);
    QValueAxis *axisY_right_ = new QValueAxis(this);

    temperature_line_ = new QLineSeries(this);
    humidity_line_ = new QLineSeries(this);
    smoke_density_line_ = new QLineSeries(this);
    light_intensity_line_ = new QLineSeries(this);

    chart_part_->addAxis(axisX_, Qt::AlignBottom);
    chart_part_->addAxis(axisY_left_, Qt::AlignLeft);
    chart_part_->addAxis(axisY_right_, Qt::AlignRight);
    chart_part_->addSeries(temperature_line_);
    chart_part_->addSeries(humidity_line_);
    chart_part_->addSeries(smoke_density_line_);
    chart_part_->addSeries(light_intensity_line_);

    // 设置X轴
    axisX_->setTickCount(7);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    // axisX_->setTitleText(tr("时间"));// 名称
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_left_->setRange(0,100);
    axisY_left_->setGridLineVisible(true);
    axisY_left_->setTickCount(6);
    axisY_left_->setMinorTickCount(5);
    axisY_left_->setTitleText("温度\n湿度");

    axisY_right_->setRange(0,1000);
    axisY_right_->setGridLineVisible(true);
    axisY_right_->setTickCount(6);
    axisY_right_->setMinorTickCount(5);
    axisY_right_->setTitleText("烟雾\n光强");

    // 温度
    temperature_line_->setName(tr("温度"));
    temperature_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    temperature_line_->attachAxis(axisY_left_);
    temperature_line_->setPointsVisible(true);

    // 湿度
    humidity_line_->setName(tr("湿度"));
    humidity_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    humidity_line_->attachAxis(axisY_left_);
    humidity_line_->setPointsVisible(true);

    // 烟雾浓度
    smoke_density_line_->setName(tr("烟雾浓度"));
    smoke_density_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    smoke_density_line_->attachAxis(axisY_right_);
    smoke_density_line_->setPointsVisible(true);

    // 光照强度
    light_intensity_line_->setName(tr("光照强度"));
    light_intensity_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    light_intensity_line_->attachAxis(axisY_right_);
    light_intensity_line_->setPointsVisible(true);

    chart_view_list.at(0)->setChart(chart_part_);
    chart_view_list.at(0)->setRenderHint(QPainter::Antialiasing);


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

    connect(temperature_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(humidity_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(smoke_density_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(light_intensity_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::InitChartPart1()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis();
    QValueAxis *axisY_ = new QValueAxis();

    current_line_ = new QLineSeries();

    chart_part1_->addAxis(axisX_, Qt::AlignBottom);
    chart_part1_->addAxis(axisY_, Qt::AlignLeft);
    chart_part1_->addSeries(current_line_);


    // 设置X轴
    axisX_->setTickCount(5);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,1000);
    axisY_->setGridLineVisible(true);
    axisY_->setTickCount(6);
    axisY_->setMinorTickCount(5);

    // Fundamental Wave Line
    current_line_->setName(tr("电流"));
    current_line_->attachAxis(axisX_);// 将line附在 axisXDate 上
    current_line_->attachAxis(axisY_);
    current_line_->setPointsVisible(true);

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
}

void ChartView::InitChartPart2()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis(this);
    QValueAxis *axisY_ = new QValueAxis(this);

    x_speed_line_ = new QLineSeries(this);
    x_acceleration_line_ = new QLineSeries(this);
    x_displacement_line_ = new QLineSeries(this);

    chart_part2_->addAxis(axisX_, Qt::AlignBottom);
    chart_part2_->addAxis(axisY_, Qt::AlignLeft);
    chart_part2_->addSeries(x_speed_line_);
    chart_part2_->addSeries(x_acceleration_line_);
    chart_part2_->addSeries(x_displacement_line_);


    // 设置X轴
    axisX_->setTickCount(7);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,40);
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

    chart_part3_->addAxis(axisX_, Qt::AlignBottom);
    chart_part3_->addAxis(axisY_, Qt::AlignLeft);
    chart_part3_->addSeries(y_speed_line_);
    chart_part3_->addSeries(y_acceleration_line_);
    chart_part3_->addSeries(y_displacement_line_);

    // 设置X轴
    axisX_->setTickCount(7);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    // axisX_->setTitleText(tr("时间"));// 名称
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,40);
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

    connect(y_speed_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(y_acceleration_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(y_displacement_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::InitChartPart4()
{
    QDateTimeAxis *axisX_ = new QDateTimeAxis(this);
    QValueAxis *axisY_ = new QValueAxis(this);

    z_speed_line_ = new QLineSeries(this);
    z_acceleration_line_ = new QLineSeries(this);
    z_displacement_line_ = new QLineSeries(this);

    chart_part4_->addAxis(axisX_, Qt::AlignBottom);
    chart_part4_->addAxis(axisY_, Qt::AlignLeft);
    chart_part4_->addSeries(z_speed_line_);
    chart_part4_->addSeries(z_acceleration_line_);
    chart_part4_->addSeries(z_displacement_line_);

    // 设置X轴
    axisX_->setTickCount(7);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    // axisX_->setTitleText(tr("时间"));// 名称
    axisX_->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY_->setRange(0,40);
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

    connect(z_speed_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(z_acceleration_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(z_displacement_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::OnlineCheckSlot()
{
    if(online_flag_ == true)
    {
        internal_table_model_->ModifyOnlineStatus(online_flag_ ,device_id_ ,data_list_.at(5));
        online_flag_ = false;
    }
    else if(online_flag_ == false)
    {
        internal_table_model_->ModifyOnlineStatus(online_flag_ ,device_id_ ,data_list_.at(5));
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
        point_value_label_->setText(QString::asprintf("\n%1.0f", point.y()));
        QPoint curPos = mapFromGlobal(QCursor::pos());
        point_value_label_->move(curPos.x() - point_value_label_->width() / 2, curPos.y() - point_value_label_->height());//移动数值
        point_value_label_->show();
    }
    else
        point_value_label_->hide();
}

void ChartView::ReceiveDataToUpdate(QList<int> data_list)
{
    data_list_ = data_list;
    DebugOut("ChartView::ReceiveDataToUpdate()<<Add Data Point");
    temperature_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(1));
    humidity_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(2));
    smoke_density_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(3));
    light_intensity_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(4));

    current_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(15));

    x_speed_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(6));
    x_acceleration_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(7));
    x_displacement_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(8));

    y_speed_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(9));
    y_acceleration_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(10));
    y_displacement_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(11));

    z_speed_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(12));
    z_acceleration_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(13));
    z_displacement_line_->append(QDateTime::currentMSecsSinceEpoch(),data_list.at(14));

    online_flag_ = true;
    internal_table_model_->ModifyOnlineStatus(true ,device_id_ ,data_list.at(5));
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
    chart_part_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    chart_part1_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    chart_part2_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    chart_part3_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    chart_part4_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
}
