#include "mainform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainForm w;
    // w.setAttribute(Qt::WA_QuitOnClose,false);
    w.show();

    // QString str="+MQTTSUBRECV:0,\"/sys/k14suPxlVyQ/Node1/thing/service/property/set\",96,{\"method\":\"thing.service.property.set\",\"id\":\"931543942\",\"params\":{\"Switch\":1},\"version\":\"1.0.0\"}";
    // qDebug()<<str;
    // QString str1;
    // str1=strstr(str,"Switch");



    return a.exec();
}
