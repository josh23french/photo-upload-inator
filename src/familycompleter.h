#ifndef FAMILYCOMPLETER_H
#define FAMILYCOMPLETER_H

#include <QCompleter>
#include <QStringList>
#include <QStandardItemModel>
#include <qjson/parser.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class FamilyCompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit FamilyCompleter(QObject *parent = 0);
    ~FamilyCompleter();
signals:
    void log(QString);
    void abortOthers();
public slots:
    void update(QString text);
private slots:
    void gotJSON(QNetworkReply* result);
private:
    QStandardItemModel * getItemsFromResult(QByteArray data);
    QStandardItemModel *items;
    QList<QStandardItem> list;
    QString endpoint;
    QNetworkAccessManager * networkManager;
    QNetworkReply* currentReply;
    //QNetworkRequest currentRequest;
    QJson::Parser parser;
    bool ok;
};

#endif // FAMILYCOMPLETER_H
