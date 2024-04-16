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
