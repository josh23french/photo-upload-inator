#include "tetherthumb.h"
#include <libexif/exif-loader.h>
#include <QDebug>
#include <QSizePolicy>
#include <QStyle>

TetherThumb::TetherThumb(QString const& fn, QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    qDebug() << "Got Filename:";
    qDebug() << fn;
    filename = fn;

    ExifLoader *l = exif_loader_new();
    if(l){
        exif_loader_write_file(l, fn.toLocal8Bit());
        ExifData *ed = exif_loader_get_data(l);
        exif_loader_unref(l);
        l = NULL;

        if(ed){
            qDebug() << "Have thumbnail!!";
            QPixmap *image = new QPixmap();
            image->loadFromData(ed->data, ed->size);
            this->setPixmap(*image);
        }
        exif_data_unref(ed);
    } else {
        qDebug() << "No thumb... :(";
    }
}

void TetherThumb::mousePressEvent( QMouseEvent *)
{
    emit clicked(this);
}
