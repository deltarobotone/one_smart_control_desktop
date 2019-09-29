/****************************************************************************
** Meta object code from reading C++ file 'flowchartwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtProjects/One_Smart_Control/one_smart_control_desktop/flowchartwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flowchartwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OneSmartControl__FlowChartWidget_t {
    QByteArrayData data[10];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OneSmartControl__FlowChartWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OneSmartControl__FlowChartWidget_t qt_meta_stringdata_OneSmartControl__FlowChartWidget = {
    {
QT_MOC_LITERAL(0, 0, 32), // "OneSmartControl::FlowChartWidget"
QT_MOC_LITERAL(1, 33, 7), // "addData"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 16), // "loadButtonHandle"
QT_MOC_LITERAL(4, 59, 16), // "saveButtonHandle"
QT_MOC_LITERAL(5, 76, 15), // "addButtonHandle"
QT_MOC_LITERAL(6, 92, 18), // "deleteButtonHandle"
QT_MOC_LITERAL(7, 111, 16), // "playButtonHandle"
QT_MOC_LITERAL(8, 128, 14), // "upButtonHandle"
QT_MOC_LITERAL(9, 143, 16) // "downButtonHandle"

    },
    "OneSmartControl::FlowChartWidget\0"
    "addData\0\0loadButtonHandle\0saveButtonHandle\0"
    "addButtonHandle\0deleteButtonHandle\0"
    "playButtonHandle\0upButtonHandle\0"
    "downButtonHandle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OneSmartControl__FlowChartWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OneSmartControl::FlowChartWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlowChartWidget *_t = static_cast<FlowChartWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addData(); break;
        case 1: _t->loadButtonHandle(); break;
        case 2: _t->saveButtonHandle(); break;
        case 3: _t->addButtonHandle(); break;
        case 4: _t->deleteButtonHandle(); break;
        case 5: _t->playButtonHandle(); break;
        case 6: _t->upButtonHandle(); break;
        case 7: _t->downButtonHandle(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject OneSmartControl::FlowChartWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_OneSmartControl__FlowChartWidget.data,
    qt_meta_data_OneSmartControl__FlowChartWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OneSmartControl::FlowChartWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OneSmartControl::FlowChartWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OneSmartControl__FlowChartWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OneSmartControl::FlowChartWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
