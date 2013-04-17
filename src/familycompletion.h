#ifndef FAMILYCOMPLETION_H
#define FAMILYCOMPLETION_H

#include <QtGui>
#include <QNetworkAccessManager>
#include <QObject>

#include <QLineEdit>
#include <QNetworkReply>
#include <QTimer>
#include <QTreeWidget>
#include <qjson/parser.h>

class FamilyCompletion : public QObject
{
    Q_OBJECT
public:
    explicit FamilyCompletion(QLineEdit *parent = 0);
    ~FamilyCompletion();
    bool eventFilter(QObject *obj, QEvent *ev);
    void showCompletion(const QStringList &choices, const QStringList &hits);
    bool completed;
signals:
    void doneCompletion(QString,QString);
public slots:
    void doneCompletion();
    void preventSuggest();
    void autoSuggest();
    void handleNetworkData(QNetworkReply *networkReply);
    void sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist);
private:
    QLineEdit *editor;
    QTreeWidget *popup;
    QTimer *timer;
    QNetworkAccessManager networkManager;
    QJson::Parser parser;
};

#endif // FAMILYCOMPLETION_H
