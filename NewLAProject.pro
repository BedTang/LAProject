QT       += core gui charts network serialport mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TimeFunc.cpp \
    main.cpp \
    mainform.cpp \
    mqttform.cpp \
    serialform.cpp \
    settingform.cpp

HEADERS += \
    TimeFunc.h \
    mainform.h \
    mqttform.h \
    serialform.h \
    settingform.h

FORMS += \
    mainform.ui \
    mqttform.ui \
    serialform.ui \
    settingform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
