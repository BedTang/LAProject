/****************************************************************************
** Meta object code from reading C++ file 'mqtt_form.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mqtt_form.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mqtt_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MqttForm_t {
    QByteArrayData data[14];
    char stringdata0[241];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MqttForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MqttForm_t qt_meta_stringdata_MqttForm = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MqttForm"
QT_MOC_LITERAL(1, 9, 16), // "client_connected"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "client_mqtterror"
QT_MOC_LITERAL(4, 44, 24), // "QMqttClient::ClientError"
QT_MOC_LITERAL(5, 69, 19), // "clietn_disconnected"
QT_MOC_LITERAL(6, 89, 14), // "PingButtonSlot"
QT_MOC_LITERAL(7, 104, 17), // "ConnectButtonSlot"
QT_MOC_LITERAL(8, 122, 19), // "SubscribeButtonSlot"
QT_MOC_LITERAL(9, 142, 17), // "PublishButtonSlot"
QT_MOC_LITERAL(10, 160, 21), // "UnsubscribeButtonSlot"
QT_MOC_LITERAL(11, 182, 21), // "ReceiveClientMessages"
QT_MOC_LITERAL(12, 204, 14), // "QMqttTopicName"
QT_MOC_LITERAL(13, 219, 21) // "on_pushButton_clicked"

    },
    "MqttForm\0client_connected\0\0client_mqtterror\0"
    "QMqttClient::ClientError\0clietn_disconnected\0"
    "PingButtonSlot\0ConnectButtonSlot\0"
    "SubscribeButtonSlot\0PublishButtonSlot\0"
    "UnsubscribeButtonSlot\0ReceiveClientMessages\0"
    "QMqttTopicName\0on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MqttForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    1,   65,    2, 0x08 /* Private */,
       5,    0,   68,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    2,   74,    2, 0x08 /* Private */,
      13,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 12,    2,    2,
    QMetaType::Void,

       0        // eod
};

void MqttForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MqttForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->client_connected(); break;
        case 1: _t->client_mqtterror((*reinterpret_cast< QMqttClient::ClientError(*)>(_a[1]))); break;
        case 2: _t->clietn_disconnected(); break;
        case 3: _t->PingButtonSlot(); break;
        case 4: _t->ConnectButtonSlot(); break;
        case 5: _t->SubscribeButtonSlot(); break;
        case 6: _t->PublishButtonSlot(); break;
        case 7: _t->UnsubscribeButtonSlot(); break;
        case 8: _t->ReceiveClientMessages((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QMqttTopicName(*)>(_a[2]))); break;
        case 9: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttClient::ClientError >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttTopicName >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MqttForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MqttForm.data,
    qt_meta_data_MqttForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MqttForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MqttForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MqttForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MqttForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
