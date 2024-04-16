#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //各项UI初始化
    {
        ui->frame->setAutoFillBackground(true);
        ui->frame2->setAutoFillBackground(true);
        ui->frame3->setAutoFillBackground(true);
        QColor c;
        c.setRed(255);
        ui->frame->setPalette(c);
        ui->frame2->setPalette(c);
        ui->frame3->setPalette(c);
    }

    //节点一
    {
        QValueAxis *axisX=new QValueAxis();
        QValueAxis *axisY=new QValueAxis();
        QDateTimeAxis *axisXDate = new QDateTimeAxis();//时间轴

        //创建图标
        chart->setTitle("节点一");
        series->setName("温度");
        series_2->setName("湿度");
        chart->addSeries(series);
        chart->addSeries(series_2);


        //X轴（时间轴）
        // axisXDate->setRange(temp_StartTime,temp_EndTime);//时间显示范围
        // axisXDate->setTitleText("Date");
        // axisXDate->setGridLineVisible(true);
        // axisXDate->setTickCount(6);//分为六格
        // axisXDate->setFormat("MM:dd");
        // chart->addAxis(axisXDate,Qt::AlignBottom);
        // series->attachAxis(axisXDate);

        //X轴
        axisX->setRange(0,30);
        axisX->setTitleText("Time (s)");
        axisX->setGridLineVisible(true);
        axisX->setTickCount(15);
        axisX->setMinorTickCount(15);
        chart->addAxis(axisX,Qt::AlignBottom);
        series->attachAxis(axisX);

        //Y轴
        axisY->setRange(0,60);
        axisY->setGridLineVisible(true);
        axisY->setTickCount(6);
        axisY->setMinorTickCount(5);
        chart->addAxis(axisY,Qt::AlignLeft);
        series->attachAxis(axisY);

        //图标设置
        chart->createDefaultAxes();
        chart->setAnimationOptions(QChart::SeriesAnimations);


        //图标UI设置
        ui->graphicsView->setChart(chart);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    }

    //节点二
    {
        QValueAxis *axisX2=new QValueAxis();
        QValueAxis *axisY2=new QValueAxis();

        chart2->setTitle("节点2");
        series2->setName("光强");
        chart2->addSeries(series2);

        axisX2->setRange(0,60);
        axisX2->setGridLineVisible(true);
        axisX2->setTickCount(6);
        axisX2->setMinorTickCount(10);
        chart2->addAxis(axisX2,Qt::AlignBottom);
        series2->attachAxis(axisX2);

        axisY2->setRange(0,60);
        axisY2->setGridLineVisible(true);
        axisY2->setTickCount(6);
        axisY2->setMinorTickCount(5);
        chart2->addAxis(axisY2,Qt::AlignLeft);
        series2->attachAxis(axisY2);

        ui->graphicsView2->setChart(chart2);
        ui->graphicsView2->setRenderHint(QPainter::Antialiasing);

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 30; ++j) {
                series2->append(i,j);
            }
        }
    }

    //节点三
    {
        QValueAxis *axisX3=new QValueAxis();
        QValueAxis *axisY3=new QValueAxis();

        chart3->setTitle("节点3");
        series3->setName("浓度");
        chart3->addSeries(series3);

        axisX3->setRange(0,60);
        axisX3->setGridLineVisible(true);
        axisX3->setTickCount(6);
        axisX3->setMinorTickCount(5);
        chart3->addAxis(axisX3,Qt::AlignBottom);

        axisY3->setRange(0,60);
        axisY3->setGridLineVisible(true);
        axisY3->setTickCount(6);
        axisY3->setMinorTickCount(5);
        chart3->addAxis(axisY3,Qt::AlignLeft);

        series3->attachAxis(axisX3);
        series3->attachAxis(axisY3);

        ui->graphicsView3->setChart(chart3);
        ui->graphicsView3->setRenderHint(QPainter::Antialiasing);

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 30; ++j) {
                series3->append(i,j);
            }
        }
    }

    //初始化 TCP 客户端
    {
        tcpClient = new QTcpSocket(this);   //实例化tcpClient
        tcpClient->abort();                 //取消原有连接
        connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
        connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(ReadError(QAbstractSocket::SocketError)));
    }
}

//返回当前时间
QString Widget::updateRealTimeData()
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("hh:mm:ss:z");
}


Widget::~Widget()
{
    delete ui;
}


//TCP客户端函数
void Widget::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        ui->textBrowser->append(buffer);
    }
}

void Widget::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    ui->pushButton4->setText(tr("连接"));
    QMessageBox msgBox;
    msgBox.setText(tr("连接服务器失败：%1").arg(tcpClient->errorString()));
    msgBox.exec();
}

int Widget::ServerReadData()
{
    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    for(int i=0; i<WhattcpClient.length(); i++)
    {
        QByteArray buffer = WhattcpClient[i]->readAll();
        if(buffer.isEmpty())    continue;

        static QString IP_Port, IP_Port_Pre;
        IP_Port = tr("[%1:%2]:").arg(WhattcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                      .arg(WhattcpClient[i]->peerPort());

        // 若此次消息的地址与上次不同，则需显示此次消息的客户端地址
        if(IP_Port != IP_Port_Pre)
            ui->textBrowser->append(IP_Port);

        ui->textBrowser->append("[ "+updateRealTimeData()+" ]"+buffer);

        //更新ip_port
        IP_Port_Pre = IP_Port;
        qDebug()<<buffer;
        QString str=buffer;
        str=str.simplified();
        qDebug()<<str;
        qDebug()<<str.toFloat();
        updateSeries(str.toFloat());
        return buffer.toInt();
    }
}

void Widget::NewConnectionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
    WhattcpClient.append(currentClient);
    // ui->textBrowser->append(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1])\
    //                                .arg(currentClient->peerPort()));
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ServerReadData()));
    // connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}

void Widget::updateSeries(float point)
{
    timeCount++;

    // 在温度曲线上增加一个点，模拟温度数据变化
    QPointF p1(timeCount,point);
    // QPointF p2(timeCount, qrand() % 10 + 30);
    // QPointF p3(timeCount, qrand() % 10 + 40);
    series->append(p1);
    // m_series2->append(p2);
    // m_series3->append(p3);
    // chart->axisX()->setRange(0, 5+timeCount);
    int count = series->points().size();
    chart->axisX()->setMax(count);
    // updateAxisYRange();
    // 清除多余的点，只保留最新的30个数据点
    // if (series->count() > 30) {
    //     series->removePoints(0, 1);
    //     // chart->axisX()->setRange(timeCount-5,10+timeCount);
    // }
    /*
    if (m_series2->count() > 30) {
        m_series2->removePoints(0, 1);
    }
    if (m_series3->count() > 30) {
        m_series3->removePoints(0, 1);
    }*/
}

void Widget::updateChartData()
{
    // 更新时间计数
    timeCount++;

    // 在温度曲线上增加一个点，模拟温度数据变化
    QPointF p1(timeCount, ServerReadData());
    // QPointF p2(timeCount, qrand() % 10 + 30);
    // QPointF p3(timeCount, qrand() % 10 + 40);
    series->append(p1);
    // m_series2->append(p2);
    // m_series3->append(p3);
    // chart->axisX()->setRange(0, 5+timeCount);
    int count = series->points().size();
    chart->axisX()->setMax(count);
    // 清除多余的点，只保留最新的30个数据点
    // if (series->count() > 30) {
    //     series->removePoints(0, 1);
    //     // chart->axisX()->setRange(timeCount-5,10+timeCount);
    // }
    /*
    if (m_series2->count() > 30) {
        m_series2->removePoints(0, 1);
    }
    if (m_series3->count() > 30) {
        m_series3->removePoints(0, 1);
    }*/
}

void Widget::updateAxisRange()
{
    // 获取横轴范围
    qreal minX = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::min();
    foreach (QAbstractSeries *series, chart->series()) {
        QXYSeries *xySeries = static_cast<QXYSeries*>(series);
        QPointF p1 = xySeries->at(0);
        QPointF p2 = xySeries->at(xySeries->count() - 1);
        qDebug()<<p1.x();
        qDebug()<<p1.x();
        if (p1.x() < minX) {
            minX = p1.x();
        }
        if (p2.x() > maxX) {
            maxX = p2.x();
        }
    }

    // 更新横轴范围
    chart->axisX()->setRange(minX, maxX);
}

//UI按钮功能区
void Widget::on_pushButton_clicked()
{
    ui->textBrowser->append("[ "+updateRealTimeData()+" ] "+"测试");
}


void Widget::on_pushButton2_clicked()
{
    ui->textBrowser->append("[ "+updateRealTimeData()+" ] "+"测试2");
}


void Widget::on_pushButton3_clicked()
{
    ui->textBrowser->append("[ "+updateRealTimeData()+" ] "+"测试3");
}


void Widget::on_pushButton4_clicked()
{
    ui->textBrowser->append("[ "+updateRealTimeData()+" ] "+"测试4");
}


void Widget::on_IPpushButton_clicked()
{
    tcpClient->connectToHost(ui->IPlineEdit->text(), ui->PortlineEdit->text().toInt());
    if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
    {
        ui->IPpushButton->setText("断开");
        ui->pushButton4->setEnabled(true);
    }
}

void Widget::on_IPpushButton2_clicked()
{

    for(int i=0; i<WhattcpClient.length(); i++)//断开所有连接
    {
        WhattcpClient[i]->disconnectFromHost();
        bool ok = WhattcpClient[i]->waitForDisconnected(1000);
        if(!ok)
        {
            // 处理异常
        }
        WhattcpClient.removeAt(i);  //从保存的客户端列表中取去除
    }
    tcpServer->close();     //不再监听端口

    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<WhattcpClient.length(); i++)
    {
        if(WhattcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            // 删除存储在combox中的客户端信息
            // ui->cbxConnection->removeItem(ui->cbxConnection->findText(tr("%1:%2")\
            //                                                               .arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
            //                                                               .arg(tcpClient[i]->peerPort())));
            // 删除存储在tcpClient列表中的客户端信息
            WhattcpClient[i]->destroyed();
            WhattcpClient.removeAt(i);
        }
    }

}
