/****************************************************************************
** Meta object code from reading C++ file 'main_form.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../main_form.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainForm_t {
    QByteArrayData data[17];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainForm_t qt_meta_stringdata_MainForm = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MainForm"
QT_MOC_LITERAL(1, 9, 15), // "SendDataToChart"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "QList<int>"
QT_MOC_LITERAL(4, 37, 17), // "AddNewDeviceToTab"
QT_MOC_LITERAL(5, 55, 2), // "ip"
QT_MOC_LITERAL(6, 58, 9), // "AddDevice"
QT_MOC_LITERAL(7, 68, 12), // "QHostAddress"
QT_MOC_LITERAL(8, 81, 11), // "TimeMessage"
QT_MOC_LITERAL(9, 93, 27), // "DeviceTabCloseTabBtnClicked"
QT_MOC_LITERAL(10, 121, 5), // "index"
QT_MOC_LITERAL(11, 127, 21), // "StartServerBtnClicked"
QT_MOC_LITERAL(12, 149, 14), // "SaveBtnClicked"
QT_MOC_LITERAL(13, 164, 17), // "SettingBtnClicked"
QT_MOC_LITERAL(14, 182, 19), // "CleanDataBtnClicked"
QT_MOC_LITERAL(15, 202, 12), // "TableClicked"
QT_MOC_LITERAL(16, 215, 11) // "QModelIndex"

    },
    "MainForm\0SendDataToChart\0\0QList<int>\0"
    "AddNewDeviceToTab\0ip\0AddDevice\0"
    "QHostAddress\0TimeMessage\0"
    "DeviceTabCloseTabBtnClicked\0index\0"
    "StartServerBtnClicked\0SaveBtnClicked\0"
    "SettingBtnClicked\0CleanDataBtnClicked\0"
    "TableClicked\0QModelIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   67,    2, 0x0a /* Public */,
       6,    1,   70,    2, 0x0a /* Public */,
       8,    0,   73,    2, 0x08 /* Private */,
       9,    1,   74,    2, 0x08 /* Private */,
      11,    0,   77,    2, 0x08 /* Private */,
      12,    0,   78,    2, 0x08 /* Private */,
      13,    0,   79,    2, 0x08 /* Private */,
      14,    0,   80,    2, 0x08 /* Private */,
      15,    1,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    2,

       0        // eod
};

void MainForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendDataToChart((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        case 1: _t->AddNewDeviceToTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->AddDevice((*reinterpret_cast< QHostAddress(*)>(_a[1]))); break;
        case 3: _t->TimeMessage(); break;
        case 4: _t->DeviceTabCloseTabBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->StartServerBtnClicked(); break;
        case 6: _t->SaveBtnClicked(); break;
        case 7: _t->SettingBtnClicked(); break;
        case 8: _t->CleanDataBtnClicked(); break;
        case 9: _t->TableClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainForm::*)(QList<int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainForm::SendDataToChart)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MainForm.data,
    qt_meta_data_MainForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void MainForm::SendDataToChart(QList<int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
