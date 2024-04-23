#include "mainform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainForm w;
    // w.setAttribute(Qt::WA_QuitOnClose,false);
    w.show();
    return a.exec();
}
