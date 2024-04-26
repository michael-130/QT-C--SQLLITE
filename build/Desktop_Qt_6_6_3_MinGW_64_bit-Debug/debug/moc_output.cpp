/****************************************************************************
** Meta object code from reading C++ file 'output.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../output.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'output.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSoutputENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSoutputENDCLASS = QtMocHelpers::stringData(
    "output",
    "on_pushButton_loadtable_clicked",
    "",
    "on_pushButton_clicked",
    "on_pushButtonwrite_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_READ_clicked",
    "on_pushButtonwrite_2_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSoutputENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[7];
    char stringdata1[32];
    char stringdata2[1];
    char stringdata3[22];
    char stringdata4[27];
    char stringdata5[24];
    char stringdata6[27];
    char stringdata7[29];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSoutputENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSoutputENDCLASS_t qt_meta_stringdata_CLASSoutputENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "output"
        QT_MOC_LITERAL(7, 31),  // "on_pushButton_loadtable_clicked"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(62, 26),  // "on_pushButtonwrite_clicked"
        QT_MOC_LITERAL(89, 23),  // "on_pushButton_2_clicked"
        QT_MOC_LITERAL(113, 26),  // "on_pushButton_READ_clicked"
        QT_MOC_LITERAL(140, 28)   // "on_pushButtonwrite_2_clicked"
    },
    "output",
    "on_pushButton_loadtable_clicked",
    "",
    "on_pushButton_clicked",
    "on_pushButtonwrite_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_READ_clicked",
    "on_pushButtonwrite_2_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSoutputENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject output::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSoutputENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSoutputENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSoutputENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<output, std::true_type>,
        // method 'on_pushButton_loadtable_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonwrite_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_READ_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonwrite_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void output::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<output *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_loadtable_clicked(); break;

        case 2: _t->on_pushButtonwrite_clicked(); break;

        case 4: _t->on_pushButton_READ_clicked(); break;
        case 5: _t->on_pushButtonwrite_2_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *output::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *output::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSoutputENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int output::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
