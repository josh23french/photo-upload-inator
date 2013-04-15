#ifndef FASTRESIZER_H
#define FASTRESIZER_H

#include <QObject>
#include <QImage>

class FastResizer : public QObject
{
    Q_OBJECT
public:
    explicit FastResizer(QObject *parent = 0);
    ~FastResizer();
    
signals:
    void error();
    void finished( const QImage &output, const QString &filename );

public slots:
    void setSize( const QSize &size );
    void setAspectRatioMode( const Qt::AspectRatioMode mode );

    void setInput( const QImage &input );
    void setInput( const QString &filename );

    void start();

private:
    struct ResizerPrivate *d;
};

#endif // FASTRESIZER_H
