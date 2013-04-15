#ifndef TETHERTHUMB_H
#define TETHERTHUMB_H

#include <QLabel>

class TetherThumb : public QLabel
{
    Q_OBJECT
public:
    explicit TetherThumb(const char* filename, QWidget *parent = 0);
    void mousePressEvent( QMouseEvent * e);
    std::string filename;
signals:
    void clicked( const char * );
public slots:

};

#endif // TETHERTHUMB_H
