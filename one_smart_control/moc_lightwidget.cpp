/****************************************************************************
** Meta object code from reading C++ file 'lightwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtProjects/One_Smart_Control/one_smart_control_desktop/lightwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lightwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OneSmartControl__LightWidget_t {
    QByteArrayData data[16];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OneSmartControl__LightWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OneSmartControl__LightWidget_t qt_meta_stringdata_OneSmartControl__LightWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "OneSmartControl::LightWidget"
QT_MOC_LITERAL(1, 29, 11), // "dataChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 7), // "toChart"
QT_MOC_LITERAL(4, 50, 12), // "setColourRed"
QT_MOC_LITERAL(5, 63, 14), // "setColourGreen"
QT_MOC_LITERAL(6, 78, 13), // "setColourBlue"
QT_MOC_LITERAL(7, 92, 13), // "setColourCyan"
QT_MOC_LITERAL(8, 106, 15), // "setColourYellow"
QT_MOC_LITERAL(9, 122, 16), // "setColourMagenta"
QT_MOC_LITERAL(10, 139, 14), // "setColourWhite"
QT_MOC_LITERAL(11, 154, 11), // "setLightOff"
QT_MOC_LITERAL(12, 166, 19), // "iSliderValueChanged"
QT_MOC_LITERAL(13, 186, 5), // "value"
QT_MOC_LITERAL(14, 192, 15), // "iSliderReleased"
QT_MOC_LITERAL(15, 208, 19) // "toChartButtonHandle"

    },
    "OneSmartControl::LightWidget\0dataChanged\0"
    "\0toChart\0setColourRed\0setColourGreen\0"
    "setColourBlue\0setColourCyan\0setColourYellow\0"
    "setColourMagenta\0setColourWhite\0"
    "setLightOff\0iSliderValueChanged\0value\0"
    "iSliderReleased\0toChartButtonHandle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OneSmartControl__LightWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    1,   89,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OneSmartControl::LightWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LightWidget *_t = static_cast<LightWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataChanged(); break;
        case 1: _t->toChart(); break;
        case 2: _t->setColourRed(); break;
        case 3: _t->setColourGreen(); break;
        case 4: _t->setColourBlue(); break;
        case 5: _t->setColourCyan(); break;
        case 6: _t->setColourYellow(); break;
        case 7: _t->setColourMagenta(); break;
        case 8: _t->setColourWhite(); break;
        case 9: _t->setLightOff(); break;
        case 10: _t->iSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->iSliderReleased(); break;
        case 12: _t->toChartButtonHandle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LightWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LightWidget::dataChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LightWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LightWidget::toChart)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OneSmartControl::LightWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_OneSmartControl__LightWidget.data,
    qt_meta_data_OneSmartControl__LightWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OneSmartControl::LightWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OneSmartControl::LightWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OneSmartControl__LightWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OneSmartControl::LightWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void OneSmartControl::LightWidget::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OneSmartControl::LightWidget::toChart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
