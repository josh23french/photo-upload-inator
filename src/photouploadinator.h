#ifndef PHOTOUPLOADER_H
#define PHOTOUPLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QSslError>

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

    bool loggedIn();
    void startLoginProcess();
    void upload(QString filename);

    QString username;
    QString password;

    QList<QString> uploadQueue;
    bool uploading;

private slots:
    void gotCredentials();
    void startUploading();
};

#endif // PHOTOUPLOADER_H
