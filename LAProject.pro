QT       += core gui charts network serialport mqtt sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    devices_data_handle.cpp \
    devices_view_handle.cpp \
    main.cpp \
    main_form.cpp \
    mqtt_form.cpp \
    serial_form.cpp \
    setting_form.cpp \
    sqlite_handle.cpp

HEADERS += \
    devices_data_handle.h \
    devices_view_handle.h \
    main_form.h \
    mqtt_form.h \
    serial_form.h \
    setting_form.h \
    sqlite_handle.h

FORMS += \
    main_form.ui \
    mqtt_form.ui \
    serial_form.ui \
    setting_form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
