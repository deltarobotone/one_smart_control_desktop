/****************************************************************************
** Meta object code from reading C++ file 'timewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtProjects/One_Smart_Control/one_smart_control_desktop/timewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OneSmartControl__TimeWidget_t {
    QByteArrayData data[7];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OneSmartControl__TimeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OneSmartControl__TimeWidget_t qt_meta_stringdata_OneSmartControl__TimeWidget = {
    {
QT_MOC_LITERAL(0, 0, 27), // "OneSmartControl::TimeWidget"
QT_MOC_LITERAL(1, 28, 11), // "dataChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 7), // "toChart"
QT_MOC_LITERAL(4, 49, 19), // "tSliderValueChanged"
QT_MOC_LITERAL(5, 69, 5), // "value"
QT_MOC_LITERAL(6, 75, 19) // "toChartButtonHandle"

    },
    "OneSmartControl::TimeWidget\0dataChanged\0"
    "\0toChart\0tSliderValueChanged\0value\0"
    "toChartButtonHandle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OneSmartControl__TimeWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   36,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void OneSmartControl::TimeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TimeWidget *_t = static_cast<TimeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataChanged(); break;
        case 1: _t->toChart(); break;
        case 2: _t->tSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->toChartButtonHandle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TimeWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimeWidget::dataChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TimeWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimeWidget::toChart)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OneSmartControl::TimeWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_OneSmartControl__TimeWidget.data,
    qt_meta_data_OneSmartControl__TimeWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OneSmartControl::TimeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OneSmartControl::TimeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OneSmartControl__TimeWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OneSmartControl::TimeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void OneSmartControl::TimeWidget::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OneSmartControl::TimeWidget::toChart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
