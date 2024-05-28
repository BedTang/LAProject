#ifndef CLOCK_CONTROL_H
#define CLOCK_CONTROL_H


#include <QDateTime>

inline QString NowTimeString()
{
    QDateTime dateTime= QDateTime::currentDateTime();
    return dateTime.toString("[ hh:mm:ss ]");
}

#endif // CLOCK_CONTROL_H
