#include "familycompleter.h"
#include <QCompleter>
#include <QStandardItemModel>
#include <QStandardItem>
#include <qjson/parser.h>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

FamilyCompleter::FamilyCompleter(QObject *parent) :
    QCompleter(parent)
{
    this->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    this->setCaseSensitivity(Qt::CaseInsensitive);
    this->endpoint = "https://www.jafrench.com/autocomplete/?contains=";
    this->networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotJSON(QNetworkReply*)));
    currentReply = NULL;
}

void FamilyCompleter::update(QString text) {
    if(text != "")
    {
        if (currentReply != NULL) {
            currentReply->abort();
        }
        currentReply = networkManager->get(QNetworkRequest(QUrl(this->endpoint + text)));  // GET
    }
}

void FamilyCompleter::gotJSON(QNetworkReply* result) {
    if (result->error() != QNetworkReply::NoError) {
        qDebug() << "Errorno " << result->error() << ": " << result->errorString();
        qDebug() << this->networkManager->networkAccessible();
        return;
    }
    QByteArray data = result->readAll();
    QStandardItemModel * items = getItemsFromResult(data);
    setModel(items);
    complete();
    setCurrentRow(0);
}

QStandardItemModel * FamilyCompleter::getItemsFromResult(QByteArray data) {
    QVariantMap res = this->parser.parse(data, &ok).toMap();
    if (!ok) {
        qDebug("An error occurred during parsing");
        return NULL;
    }
    QStandardItemModel *items = new QStandardItemModel(0, 2, this);
    foreach (QVariant family, res["families"].toList()) {
        qDebug() << family.toMap()["firstNames"].toString() << " " << family.toMap()["lastName"].toString();
        QList<QStandardItem *> list;
        QStandardItem *item0 = new QStandardItem(QString(family.toMap()["firstNames"].toString() + " " + family.toMap()["lastName"].toString()));
        QStandardItem *item1 = new QStandardItem(QString::number(family.toMap()["pk"].toInt()));
        list.append(item0);
        list.append(item1);
        items->appendRow(list);
    }
    return items;
}
