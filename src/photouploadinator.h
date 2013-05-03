#ifndef PHOTOUPLOADER_H
#define PHOTOUPLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QSslError>
#include "cookiejar.h"

class PhotoUploadInator : public QObject
{
    Q_OBJECT
public:
    explicit PhotoUploadInator(QObject *parent = 0);
    ~PhotoUploadInator();
    void getCredentials();
    bool haveCredentials();
    bool addUpload(QString filename);
    void setFamily(QString fid);
signals:
    
public slots:
    void uploadComplete();
    void handleSslErrors(QNetworkReply *, QList<QSslError>);

private:
    QNetworkAccessManager *qnam;
    QString csrftoken;
    QString sessionid;
    bool haveCSRF();
    void getCSRF();

    QString familyId;
    QString curfn;

    bool loggedIn();
    void startLoginProcess();
    void upload(QString filename);

    QString username;
    QString password;

    QList<QString> uploadQueue;
    bool uploading;
    CookieJar *cj;

private slots:
    void gotCredentials();
    void startUploading();
    void maybeQuit();
};

#endif // PHOTOUPLOADER_H
