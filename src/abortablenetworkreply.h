#ifndef ABORTABLENETWORKREPLY_H
#define ABORTABLENETWORKREPLY_H

#include <QNetworkReply>

class AbortableNetworkReply : public QNetworkReply
{
    Q_OBJECT
public:
    explicit AbortableNetworkReply(QObject *parent = 0);
    
signals:
    
public slots:
    void abort();
};

#endif // ABORTABLENETWORKREPLY_H
