/****************************************************************************
** Meta object code from reading C++ file 'tetherwindow.h'
**
** Created: Sat Apr 13 23:43:17 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/tetherwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tetherwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TetherWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      30,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   13,   13,   13, 0x0a,
      76,   13,   13,   13, 0x0a,
     123,  114,   13,   13, 0x0a,
     160,   13,   13,   13, 0x0a,
     179,   13,   13,   13, 0x08,
     208,   13,   13,   13, 0x08,
     242,   13,   13,   13, 0x08,
     274,  271,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TetherWindow[] = {
    "TetherWindow\0\0familyChanged()\0"
    "imageSaved(const char*)\0displayThumbForJPEG()\0"
    "displayFullForThumb(QListWidgetItem*)\0"
    "filename\0displayThumbForTethered(const char*)\0"
    "rereadCameraInfo()\0on_actionSign_in_triggered()\0"
    "on_actionDetect_Camer_triggered()\0"
    "on_actionCapture_triggered()\0mi\0"
    "setFamily(QModelIndex)\0"
};

void TetherWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TetherWindow *_t = static_cast<TetherWindow *>(_o);
        switch (_id) {
        case 0: _t->familyChanged(); break;
        case 1: _t->imageSaved((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->displayThumbForJPEG(); break;
        case 3: _t->displayFullForThumb((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->displayThumbForTethered((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 5: _t->rereadCameraInfo(); break;
        case 6: _t->on_actionSign_in_triggered(); break;
        case 7: _t->on_actionDetect_Camer_triggered(); break;
        case 8: _t->on_actionCapture_triggered(); break;
        case 9: _t->setFamily((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TetherWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TetherWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TetherWindow,
      qt_meta_data_TetherWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TetherWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TetherWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TetherWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TetherWindow))
        return static_cast<void*>(const_cast< TetherWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TetherWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TetherWindow::familyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TetherWindow::imageSaved(const char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
