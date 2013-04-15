/****************************************************************************
** Meta object code from reading C++ file 'infodialog.h'
**
** Created: Mon Feb 18 13:21:55 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/infodialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'infodialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InfoDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      28,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   11,   11,   11, 0x08,
      84,   11,   11,   11, 0x08,
     114,   11,   11,   11, 0x08,
     140,  137,   11,   11, 0x08,
     156,  153,   11,   11, 0x08,
     182,  179,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InfoDialog[] = {
    "InfoDialog\0\0familyChanged()\0"
    "imageSaved(const char*)\0"
    "on_pb_capture_preview_clicked()\0"
    "on_pb_capture_image_clicked()\0"
    "on_pb_rescan_clicked()\0lt\0log(QString)\0"
    "mi\0setFamily(QModelIndex)\0cf\0"
    "processPreview(CameraFile*)\0"
};

void InfoDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InfoDialog *_t = static_cast<InfoDialog *>(_o);
        switch (_id) {
        case 0: _t->familyChanged(); break;
        case 1: _t->imageSaved((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->on_pb_capture_preview_clicked(); break;
        case 3: _t->on_pb_capture_image_clicked(); break;
        case 4: _t->on_pb_rescan_clicked(); break;
        case 5: _t->log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setFamily((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 7: _t->processPreview((*reinterpret_cast< CameraFile*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InfoDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InfoDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InfoDialog,
      qt_meta_data_InfoDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InfoDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InfoDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InfoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InfoDialog))
        return static_cast<void*>(const_cast< InfoDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int InfoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void InfoDialog::familyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void InfoDialog::imageSaved(const char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
