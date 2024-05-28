#include "devices_chart_handler.h"
#include <QDebug>

extern QString updateRealTimeData();

QString updateRealTimeData()
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("hh:mm:ss:z");
}

ChartView::ChartView(QWidget *parent)
    : QWidget(parent)
    , timer(new QTimer(this))
    , valueLabel(new QLabel(parent))
{
    chart_ = new QChart();
    axisX_ = new QDateTimeAxis(this);
    axisY_= new QValueAxis(this);

    temperature_line_ = new QLineSeries(this);
    humidity_line_ = new QLineSeries(this);
    smoke_density_line_ = new QLineSeries(this);
    light_intensity_line_ = new QLineSeries(this);

    chart_switch_button_ = new QPushButton(chart_view_);

    initChart();

    connect(timer, SIGNAL(timeout()), this, SLOT(TimeOut()));

    qDebug()<<"类创建";

    timer->start(1000);
}

ChartView::~ChartView()
{
    qDebug()<<tr("销毁chartView");
}

QChartView* ChartView::AddChart()
{
    return chart_view_;
}

QChartView* ChartView::DeleteChart()
{
    return NULL;
}

void ChartView::initChart()
{

    qDebug()<<chart_view_->pos();
    qDebug()<<chart_view_->width()<<chart_view_->height();
    qDebug()<<chart_switch_button_->width()<<chart_switch_button_->height();
    chart_switch_button_->move(chart_view_->width() - chart_switch_button_->width() /2 ,100);
    qDebug()<<chart_switch_button_->pos();
    // 向图标添加坐标轴和数据系列

    chart_->addAxis(axisX_, Qt::AlignBottom);
    chart_->addAxis(axisY_, Qt::AlignLeft);
    chart_->addSeries(temperature_line_);
    chart_->addSeries(humidity_line_);
    chart_->addSeries(smoke_density_line_);
    chart_->addSeries(light_intensity_line_);

    // 设置X轴
    axisX_->setTickCount(10);// 刻度线
    axisX_->setFormat(tr("hh:mm:ss"));// 格式
    axisX_->setTitleText(tr("时间"));// 名称
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

    chart_view_->setChart(chart_);
    chart_view_->setRenderHint(QPainter::Antialiasing);

    // 数据点显示
    valueLabel->setStyleSheet(QString("QLabel{color:#1564FF;"
                                        "font-family:\"Microsoft Yahei\";"
                                        "font-size:12px; font-weight:bold;"
                                        "background-color:rgba(21, 100, 255, 51);"
                                        "border-radius:4px;"
                                        "text-align:center;}"));
    valueLabel->setFixedSize(60, 35);
    valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    valueLabel->hide();

    connect(temperature_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(humidity_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(smoke_density_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(light_intensity_line_, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
}

void ChartView::resizeEvent(QResizeEvent *event)
{
    //chart_switch_button_->move(chart_switch_button_->width()/2,chart_switch_button_->height()-100);
    qDebug()<<chart_switch_button_->width()<<chart_switch_button_->height();
    QWidget::resizeEvent(event);
}

bool ChartView::Event(QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        QResizeEvent *rec_event = static_cast<QResizeEvent*>(event);
        qDebug()<<"old:"<<rec_event->oldSize().width()<<rec_event->oldSize().height();

        return ChartView::Event(event);
    }
}

void ChartView::PointHoverd(const QPointF &point, bool state)
{
    QDateTime time = QDateTime::currentDateTime();
    if (state)
    {
        valueLabel->setText(QString::asprintf(time.toString("hh:mm:ss").toUtf8()+"\n%1.0f", point.y()));

        QPoint curPos = mapFromGlobal(QCursor::pos());
        valueLabel->move(curPos.x() - valueLabel->width() / 2, curPos.y() - valueLabel->height() * 1.5);//移动数值
        valueLabel->show();//显示出来
    }
    else
        valueLabel->hide();//进行隐藏
}

void ChartView::ReceiveDataToUpdate(int temperature, int humidity, int smoke, int light)
{
    qDebug()<<"增添数据点";
    temperature_line_->append(QDateTime::currentMSecsSinceEpoch(),temperature);
    humidity_line_->append(QDateTime::currentMSecsSinceEpoch(),humidity);
    smoke_density_line_->append(QDateTime::currentMSecsSinceEpoch(),smoke);
    light_intensity_line_->append(QDateTime::currentMSecsSinceEpoch(),light);
}

void ChartView::TimeOut()
{
    // qreal y_range = line->;
    // qDebug()<< y_range;
    chart_->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
}

