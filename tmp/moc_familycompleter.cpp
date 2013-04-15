/****************************************************************************
** Meta object code from reading C++ file 'familycompleter.h'
**
** Created: Mon Feb 18 13:21:56 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/familycompleter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'familycompleter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FamilyCompleter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   30,   16,   16, 0x0a,
      58,   51,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FamilyCompleter[] = {
    "FamilyCompleter\0\0log(QString)\0text\0"
    "update(QString)\0result\0gotJSON(QNetworkReply*)\0"
};

void FamilyCompleter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FamilyCompleter *_t = static_cast<FamilyCompleter *>(_o);
        switch (_id) {
        case 0: _t->log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->update((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->gotJSON((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FamilyCompleter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FamilyCompleter::staticMetaObject = {
    { &QCompleter::staticMetaObject, qt_meta_stringdata_FamilyCompleter,
      qt_meta_data_FamilyCompleter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FamilyCompleter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FamilyCompleter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FamilyCompleter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FamilyCompleter))
        return static_cast<void*>(const_cast< FamilyCompleter*>(this));
    return QCompleter::qt_metacast(_clname);
}

int FamilyCompleter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCompleter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FamilyCompleter::log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
