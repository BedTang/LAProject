#include "dataviewoperator.h"
#include <QDebug>

chartView::chartView(QWidget *parent, QWidget *table)
    : QWidget(parent)
    , timer(new QTimer(this))
    , m_valueLabel(new QLabel(parent))
{
    chart = new QChart();
    axisX = new QDateTimeAxis(this);
    axisY= new QValueAxis(this);
    line = new QLineSeries(this);
    scatter = new QScatterSeries(this);
    scatter_2 = new QScatterSeries(this);

    // 向图标添加坐标轴和数据系列
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addSeries(line);
    chart->addSeries(scatter);
    chart->addSeries(scatter_2);

    // 设置X轴
    axisX->setTickCount(10);// 刻度线
    axisX->setFormat(tr("hh:mm:ss"));// 格式
    axisX->setTitleText(tr("时间"));// 名称
    axisX->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(60));// 范围

    // Y轴
    axisY->setRange(0,100);
    axisY->setGridLineVisible(true);
    axisY->setTickCount(6);
    axisY->setMinorTickCount(5);

    // 折线图
    line->setName("浓度");
    line->attachAxis(axisX);// 将line附在 axisXDate 上
    line->attachAxis(axisY);

    // 散点图（边框）
    scatter->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    scatter->setBorderColor(QColor(21, 100, 255)); // 离散点边框颜色
    scatter->setBrush(QBrush(QColor(21, 100, 255)));// 离散点背景色
    scatter->setMarkerSize(7); // 离散点大小
    scatter->attachAxis(axisX);
    scatter->attachAxis(axisY);

    // 散点图（中心）
    scatter_2->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    scatter_2->setBorderColor(Qt::white);// 边框颜色
    scatter_2->setBrush(QBrush(Qt::white));// 背景颜色
    scatter_2->setMarkerSize(3);// 点大小
    scatter_2->attachAxis(axisX);
    scatter_2->attachAxis(axisY);

    chart->legend()->markers(scatter).first()->setVisible(false);// 隐藏图例
    chart->legend()->markers(scatter_2).first()->setVisible(false);

    m_chartView->setChart(chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timer->start(1000);

    connect(scatter_2, &QScatterSeries::hovered, this, &chartView::pointHoverd);//用于鼠标移动到点上显示数值
    // m_valueLabel = new QLabel(chartView);
    m_valueLabel->setStyleSheet(QString("QLabel{color:#1564FF; font-family:\"Microsoft Yahei\";"
                                        "font-size:12px; font-weight:bold;"
                                        "background-color:rgba(21, 100, 255, 51); border-radius:4px; text-align:center;}"));
    m_valueLabel->setFixedSize(60, 35);
    m_valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_valueLabel->hide();
}

chartView::~chartView()
{

}

QChartView* chartView::addChart()
{
    return m_chartView;
}

QChartView* chartView::deleteChart()
{

}

void chartView::pointHoverd(const QPointF &point, bool state)
{
    QDateTime time = QDateTime::currentDateTime();
    if (state) {
        m_valueLabel->setText(QString::asprintf(time.toString("hh:mm:ss").toUtf8()+"\n%1.0f", point.y()));

        QPoint curPos = mapFromGlobal(QCursor::pos());
        m_valueLabel->move(curPos.x() - m_valueLabel->width() / 2, curPos.y() - m_valueLabel->height() * 1.5);//移动数值
        m_valueLabel->show();//显示出来
    }
    else
        m_valueLabel->hide();//进行隐藏
}

void chartView::timeOut()
{
    QPointF p(QDateTime::currentMSecsSinceEpoch(),QRandomGenerator::global()->bounded(100));
    chart->axes(Qt::Horizontal).back()->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());

    line->append(p);
    scatter->append(p);
    scatter_2->append(p);
}

tableView::tableView(QWidget *parent, QWidget *table)
    : QWidget(parent)
{
    tableModel = new QStandardItemModel(table);
    tableModel->setColumnCount(7);// 设置列字段名
    tableModel->setHeaderData(0, Qt::Horizontal, tr("设备名称"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("设备地址"));
    tableModel->setHeaderData(2, Qt::Horizontal, tr("设备类型"));
    tableModel->setHeaderData(3, Qt::Horizontal, tr("设备状态"));
    tableModel->setHeaderData(4, Qt::Horizontal, tr("上线时间"));
    tableModel->setHeaderData(5, Qt::Horizontal, tr("最后在线时间"));
    tableModel->setHeaderData(6, Qt::Horizontal, tr("Test"));
    tableModel->setItem(0,0,new QStandardItem("张三123123123123122"));
    qDebug()<<"class tableview created successfully!";
}

QStandardItemModel* tableView::addTable()
{
    return tableModel;
}
