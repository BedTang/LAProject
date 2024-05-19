#include "devices_view_handle.h"
#include <QDebug>

chartViewClass::chartViewClass(QWidget *parent)
    : QWidget(parent)
    , timer(new QTimer(this))
    , valueLabel(new QLabel(parent))
{
    chart = new QChart();
    axisX = new QDateTimeAxis(this);
    axisY= new QValueAxis(this);
    line = new QLineSeries(this);
    scatter = new QScatterSeries(this);
    scatter_2 = new QScatterSeries(this);

    initChart();

    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timer->start(1000);

}

chartViewClass::~chartViewClass()
{
    qDebug()<<tr("销毁chartView");
}

QChartView* chartViewClass::addChart()
{
    return chartView;
}

QChartView* chartViewClass::deleteChart()
{

}

void chartViewClass::initChart()
{
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
    chart->legend()->markers(scatter).first()->setVisible(false);// 隐藏图例

    // 散点图（中心）
    scatter_2->setMarkerShape(QScatterSeries::MarkerShapeCircle);// 圆形的点
    scatter_2->setBorderColor(Qt::white);// 边框颜色
    scatter_2->setBrush(QBrush(Qt::white));// 背景颜色
    scatter_2->setMarkerSize(3);// 点大小
    scatter_2->attachAxis(axisX);
    scatter_2->attachAxis(axisY);
    chart->legend()->markers(scatter_2).first()->setVisible(false);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 数据点显示
    valueLabel->setStyleSheet(QString("QLabel{color:#1564FF; font-family:\"Microsoft Yahei\";"
                                        "font-size:12px; font-weight:bold;"
                                        "background-color:rgba(21, 100, 255, 51); border-radius:4px; text-align:center;}"));
    valueLabel->setFixedSize(60, 35);
    valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    valueLabel->hide();
    connect(scatter_2, &QScatterSeries::hovered, this, &chartViewClass::pointHoverd);//用于鼠标移动到点上显示数值
}

void chartViewClass::pointHoverd(const QPointF &point, bool state)
{
    QDateTime time = QDateTime::currentDateTime();
    if (state) {
        valueLabel->setText(QString::asprintf(time.toString("hh:mm:ss").toUtf8()+"\n%1.0f", point.y()));

        QPoint curPos = mapFromGlobal(QCursor::pos());
        valueLabel->move(curPos.x() - valueLabel->width() / 2, curPos.y() - valueLabel->height() * 1.5);//移动数值
        valueLabel->show();//显示出来
    }
    else
        valueLabel->hide();//进行隐藏
}

void chartViewClass::timeOut()
{
    QPointF p(QDateTime::currentMSecsSinceEpoch(),QRandomGenerator::global()->bounded(100));
    chart->axes(Qt::Horizontal).back()->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());

    line->append(p);
    scatter->append(p);
    scatter_2->append(p);
}



tableViewClass::tableViewClass(QWidget *parent, QTableView *table)
    : QWidget(parent)
    ,table(table)
{
    tableModel = new QStandardItemModel(table);

    initTable(table);

    qDebug()<<"class tableview created successfully!";
}

QStandardItemModel* tableViewClass::addTable()
{
    return tableModel;
}

void tableViewClass::addData()
{
    QList<QStandardItem*> add_items;
    // QStandardItem *item = new QStandardItem();
    add_items << new QStandardItem("deviceName") << new QStandardItem("deviceAddress") << new QStandardItem("deviceType") << new QStandardItem("deviceStats") << new QStandardItem("deviceOnlineTime") << new QStandardItem("deviceLastOnlineTime");
    tableModel->appendRow(add_items);
}

void tableViewClass::deleteView(int index)
{
    tableModel->removeRows(index, index);
}

void tableViewClass::initTable(QTableView *table)
{
    QStringList header;
    header<<tr("设备名称")<<tr("设备地址")<<tr("设备类型")<<tr("设备状态")<<tr("上线时间")<<tr("最后在线时间");
    tableModel->setHorizontalHeaderLabels(header);
    table->setModel(this->addTable());
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    // table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setHighlightSections(false);
    // table->horizontalHeader()->setFont(QFont(QFont::defaultFamily(),14))
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);// 禁止修改
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}
