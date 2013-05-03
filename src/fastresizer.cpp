#include "fastresizer.h"
#include <QImage>
#include <QDebug>

struct ResizerPrivate
{
    QSize size;
    Qt::AspectRatioMode aspectMode;
    QImage input;
    QString inputFilename;
};

FastResizer::FastResizer(QObject *parent) :
    QObject(parent),
    d(new ResizerPrivate)
{
    d->aspectMode = Qt::KeepAspectRatio;
    //qDebug() << "in Thread!!";
}

FastResizer::~FastResizer()
{
    delete d;
}

void FastResizer::setSize(const QSize &size)
{
    d->size = size;
}

void FastResizer::setAspectRatioMode(const Qt::AspectRatioMode mode)
{
    d->aspectMode = mode;
}

void FastResizer::setInput(const QImage &input)
{
    d->input = input;
}

void FastResizer::setInput(const QString &filename)
{
    d->inputFilename = filename;
}

void FastResizer::start()
{
    //qDebug() << "Starting thread... filename: " << d->inputFilename;
    if( !d->inputFilename.isEmpty() ){
        d->input.load( d->inputFilename );
    }
    if( d->input.isNull() ){
        emit error();
        return;
    }

    bool done = false;
    int currentSize = d->input.width();
    int finalSize = d->size.width();
    if( d->size.height() > d->size.width())
        finalSize = d->size.height();
    while(!done){
        float halfSize = currentSize / 2.0f;
        float scaleFactor = (float)currentSize / (float)finalSize;
        if(scaleFactor > 2.0f){
            currentSize = (int)halfSize + 1;
        }
        else {
            currentSize = finalSize;
            done = true;
        }
        d->input = d->input.scaled(currentSize, currentSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    emit finished( d->input, d->inputFilename );
    emit finished();
}
