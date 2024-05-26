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
    chart = new QChart();
    axisX = new QDateTimeAxis(this);
    axisY= new QValueAxis(this);

    line = new QLineSeries(this);
    line2 = new QLineSeries(this);
    line3 = new QLineSeries(this);
    line4 = new QLineSeries(this);

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
    return chartView;
}

QChartView* ChartView::DeleteChart()
{
    return NULL;
}

void ChartView::initChart()
{
    // 向图标添加坐标轴和数据系列

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addSeries(line);
    chart->addSeries(line2);
    chart->addSeries(line3);
    chart->addSeries(line4);

    // 设置X轴
    axisX->setTickCount(10);// 刻度线
    axisX->setFormat(tr("hh:mm:ss"));// 格式
    axisX->setTitleText(tr("时间"));// 名称
    axisX->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY->setRange(0,300);
    axisY->setGridLineVisible(true);
    axisY->setTickCount(6);
    axisY->setMinorTickCount(5);

    // 温度
    line->setName(tr("温度"));
    line->attachAxis(axisX);// 将line附在 axisXDate 上
    line->attachAxis(axisY);
    line->setPointsVisible(true);

    // 湿度
    line2->setName(tr("湿度"));
    line2->attachAxis(axisX);// 将line附在 axisXDate 上
    line2->attachAxis(axisY);
    line2->setPointsVisible(true);

    // 烟雾浓度
    line3->setName(tr("烟雾浓度"));
    line3->attachAxis(axisX);// 将line附在 axisXDate 上
    line3->attachAxis(axisY);
    line3->setPointsVisible(true);

    // 光照强度
    line4->setName(tr("光照强度"));
    line4->attachAxis(axisX);// 将line附在 axisXDate 上
    line4->attachAxis(axisY);
    line4->setPointsVisible(true);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

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

    connect(line, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(line2, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(line3, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
    connect(line4, &QScatterSeries::hovered, this, &ChartView::PointHoverd);//用于鼠标移动到点上显示数值
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
    line->append(QDateTime::currentMSecsSinceEpoch(),temperature);
    line2->append(QDateTime::currentMSecsSinceEpoch(),humidity);
    line3->append(QDateTime::currentMSecsSinceEpoch(),smoke);
    line4->append(QDateTime::currentMSecsSinceEpoch(),light);
}

void ChartView::TimeOut()
{
    chart->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
}

