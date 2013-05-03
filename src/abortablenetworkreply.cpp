#include "abortablenetworkreply.h"

AbortableNetworkReply::AbortableNetworkReply(QObject *parent) :
    QNetworkReply(parent)
{
}

void AbortableNetworkReply::abort()
{
    this->abort();
}
