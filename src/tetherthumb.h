#ifndef TETHERTHUMB_H
#define TETHERTHUMB_H

#include <QLabel>

class TetherThumb : public QLabel
{
    Q_OBJECT
public:
    explicit TetherThumb(QString const& fn, QWidget *parent = 0);
    void mousePressEvent( QMouseEvent * e);
    QString filename;
signals:
    void clicked( TetherThumb* );
public slots:

};

#endif // TETHERTHUMB_H
