#ifndef TIMEFUNC_H
#define TIMEFUNC_H

#include <QDateTime>

static QString updateRealTimeData()
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("[ hh:mm:ss:z ]");
}

static QString updateRealTimeData(int)
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("[ hh:mm:ss ]");
}

#endif // TIMEFUNC_H
