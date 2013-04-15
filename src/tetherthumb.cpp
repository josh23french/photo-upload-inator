#include "tetherthumb.h"
#include <libexif/exif-loader.h>
#include <QDebug>
#include <QSizePolicy>
#include <QStyle>

TetherThumb::TetherThumb(const char* filename, QWidget *parent) :
    QLabel(parent)
{
    this->setMouseTracking(true);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    qDebug() << "Got Filename:";
    qDebug() << filename;
    this->filename = std::string(filename);

    ExifLoader *l = exif_loader_new();
    if(l){
        exif_loader_write_file(l, filename);
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
    emit clicked(this->filename.c_str());
}
