#include "photouploadinator.h"
#include "cookiejar.h"
#include <QNetworkAccessManager>
#include <QApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QVariant>
#include <QFile>
#include <QDebug>
#include <QDesktopServices>
#include <QIODevice>
#include <QSettings>
#include "forms/signindialog.h"
#include <QTimer>
#include <QEventLoop>
#include <QErrorMessage>
#include <QMessageBox>
#include "qjson/parser.h"
#include <QSslError>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <QLabel>

PhotoUploadInator::PhotoUploadInator(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Start!";
    qnam = new QNetworkAccessManager(this);
    QObject::connect(qnam, SIGNAL(sslErrors(QNetworkReply *, QList<QSslError>)), this, SLOT(handleSslErrors(QNetworkReply *, QList<QSslError>)));
    cj = new CookieJar(qnam);
    qnam->setCookieJar(cj);
    //upload("/tmp/capt0000.jpg");
    QSettings settings;
    password = "";
    username = settings.value("login/username", QString("")).toString();
    if( !loggedIn() ) {
        startLoginProcess();
    }
    uploading = false;
    startUploading();

    /* TODO: When we have credentials, send out a request to get them verified.
     *
     * 1. Create request & POST it.
     * 2. Connect to finished() and catch when it's completed...
     * 3. If auth failed, ask for new credentials (and say, auth rejected, or something)
     * 4. If auth passed, delete password and start uploading things from the queue
     *
     */
}

void PhotoUploadInator::handleSslErrors(QNetworkReply *reply, QList<QSslError> errors)
{
    foreach(QSslError error, errors) {
        qDebug() << "SSL Error! : " << error;
    }
	reply->ignoreSslErrors();
}

PhotoUploadInator::~PhotoUploadInator()
{
    QSettings settings;
    if( settings.value("Preferences/signoutonquit").toBool() ) {
        cj->clear();
    }
    settings.setValue("login/username", username);
}

void PhotoUploadInator::setFamily(QString fid)
{
    familyId = fid;
}

void PhotoUploadInator::startUploading()
{
    if( uploading == true )
        return;
    if( uploadQueue.length() < 1 ) {
        //qDebug() << "Nothing in queue.";
        QTimer::singleShot(750, this, SLOT(startUploading()));
        return;
    }
    uploading = true;
    upload(uploadQueue.takeFirst());
}

bool PhotoUploadInator::addUpload(QString filename)
{
	// if file not exists... false!
	if( access( filename.toLocal8Bit(), F_OK ) != -1 ) {
		uploadQueue.append(filename);
		return true;
	}
    qDebug() << "File does not exist.";
    return false;

}

bool PhotoUploadInator::loggedIn()
{
    QNetworkReply *reply = qnam->get(QNetworkRequest(QUrl("https://www.jafrench.com/uploadphoto/")));
    QEventLoop el;
    connect( reply, SIGNAL(finished()), &el, SLOT(quit()));
    el.exec();
    QString jsonreply = reply->readAll();
    if( reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 405 )
    {
        return true;
    }
    qDebug() << jsonreply << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if( reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 0 )
        return loggedIn();
    return false;
}

void PhotoUploadInator::startLoginProcess()
{
    qDebug() << "Starting login process...";
    if( !haveCSRF() ) {
        getCSRF();
    }
    if( !haveCredentials() ) {
        getCredentials();
    }
    qDebug() << " --- Should have everything needed to login ---";
    qDebug() << "csrftoken=" << csrftoken;
    qDebug() << "sessionid=" << sessionid;
    qDebug() << "username=" << username;
    qDebug() << "password=" << password;
    QNetworkRequest qnr = QNetworkRequest(QUrl("https://www.jafrench.com/login/?next=/"));
    qnr.setRawHeader("Referer", "https://www.jafrench.com/login/?next=/");
    qnr.setRawHeader("Origin", "https://www.jafrench.com");
    qnr.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrl pd;
    pd.addQueryItem("username", username);
    pd.addQueryItem("password", password);
    pd.addQueryItem("csrfmiddlewaretoken", csrftoken);
    pd.addQueryItem("this_is_the_login_form", "1");
    pd.addQueryItem("next", "/uploadphoto/");


    QNetworkReply *reply = qnam->post(qnr, pd.encodedQuery());
    QEventLoop el;
    connect( reply, SIGNAL(finished()), &el, SLOT(quit()));
    el.exec();
    QString jsonreply = reply->readAll();
    reply->deleteLater();
    qDebug() << jsonreply;
    qDebug() << reply->header(QNetworkRequest::LocationHeader).toString();
    if( reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302 ) {
        qDebug() << "This one!!";
        QMetaObject::invokeMethod(this, SLOT(startUploading());
        return;
    }
    password = "";
    QErrorMessage *emd = new QErrorMessage();
    emd->showMessage("Invalid credentials! Please try again.");
    emd->setModal(true);
    emd->exec();
    qDebug() << ";_;";
    startLoginProcess();
}

bool PhotoUploadInator::haveCredentials()
{
    if( username == "" or password == "" )
        return false;
    return true;
}

void PhotoUploadInator::maybeQuit()
{
    qDebug() << "REJECTED()";
    if( QMessageBox::Ok == QMessageBox::question((QWidget*)parent(), tr("Quit?"), tr("If you don't log in, you can't continue. Quit?"), QMessageBox::Ok, QMessageBox::Cancel)) {
        exit(0);
        qDebug() << "Y U NO QUIT()?";
    }
}

void PhotoUploadInator::getCredentials()
{
    qDebug() << "I can has credentials?";
    SignInDialog *sid = new SignInDialog();
    sid->setPassword(password); // Order is important here...
    sid->setUsername(username); // So password gets focus.
    sid->setModal(true);
    connect(sid, SIGNAL(accepted()), this, SLOT(gotCredentials()));
    connect(sid, SIGNAL(rejected()), this, SLOT(maybeQuit()));
    sid->exec();
    sid->deleteLater();
}

void PhotoUploadInator::gotCredentials()
{
    username = ((SignInDialog*)QObject::sender())->username();
    password = ((SignInDialog*)QObject::sender())->password();
}

void PhotoUploadInator::uploadComplete()
{
    qDebug() << "csrftoken=" << csrftoken;
    qDebug() << "sessionid=" << sessionid;
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    if( reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 403 ) {
        qDebug() << "403 ERROR!";
        password = "";
        addUpload(curfn);
        uploading = false;
        startLoginProcess();
        return;
    }
    qDebug() << "---- Request Headers ----";
    foreach(QString f, reply->request().rawHeaderList()){
        qDebug() << f << ": " << reply->rawHeader(f.toLocal8Bit());
    }
    qDebug() << "---- Response Headers ----";
    foreach(QString f, reply->rawHeaderList()){
        qDebug() << f << ": " << reply->rawHeader(f.toLocal8Bit());
    }
    qDebug() << "Status code: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    qDebug() << "--- --- --- --- ---\n" << reply->readAll() << "\n--- --- --- --- ---";
    
    QJson::Parser *p = new QJson::Parser();
    qDebug() << "Upload Complete! Status code: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString() << " New PhotoID: "<< p->parse(reply->readAll()).toMap().value("familyphoto").toString();
    uploading = false;
    startUploading();
}

bool PhotoUploadInator::haveCSRF()
{
    //cookies may not be loaded from file... so load them now.
    foreach(QNetworkCookie c, qnam->cookieJar()->cookiesForUrl(QUrl("https://www.jafrench.com/uploadphoto/")))
    {
        if( c.name() == "csrftoken" )
            csrftoken = c.value();
        if( c.name() == "sessionid" )
            sessionid = c.value();
    }
    //qDebug() << "csrftoken=" << csrftoken;
    //qDebug() << "sessionid=" << sessionid;
    return !csrftoken.isNull();
}

void PhotoUploadInator::getCSRF()
{
    QNetworkRequest test = QNetworkRequest(QUrl("https://www.jafrench.com/login/?next=/"));
    test.setRawHeader("Host", "www.jafrench.com");
    test.setRawHeader("Referer", "https://www.jafrench.com/");
    test.setRawHeader("Origin", "https://www.jafrench.com");
    QNetworkReply *reply = qnam->get(test);
    QEventLoop el;
    connect(reply, SIGNAL(finished()), &el, SLOT(quit()));
    el.exec();

    qDebug() << "---- Request Headers ----";
    foreach(QString f, reply->request().rawHeaderList()){
        qDebug() << f << ": " << reply->rawHeader(f.toLocal8Bit());
    }
    qDebug() << "---- Response Headers ----";
    foreach(QString f, reply->rawHeaderList()){
        qDebug() << f << ": " << reply->rawHeader(f.toLocal8Bit());
    }
    qDebug() << "Status code: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    qDebug() << "--- --- start --- ---\n" << reply->readAll() << "\n--- ---  end  --- ---";
    foreach(QNetworkCookie c, qnam->cookieJar()->cookiesForUrl(QUrl("https://www.jafrench.com/uploadphoto/")))
    {
        if( c.name() == "csrftoken" )
            csrftoken = c.value();
        if( c.name() == "sessionid" )
            sessionid = c.value();
    }
    qDebug() << "csrftoken=" << csrftoken;
    qDebug() << "sessionid=" << sessionid;
    reply->deleteLater();
    if( !haveCSRF() ) {
        getCSRF();
    }
}

void PhotoUploadInator::upload(QString filename)
{
    curfn = filename;
    QNetworkRequest test = QNetworkRequest(QUrl("https://www.jafrench.com/uploadphoto/"));
    test.setRawHeader("Referer", "https://www.jafrench.com/");
    test.setRawHeader("Origin", "https://www.jafrench.com");
    QHttpMultiPart *form = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart csrf;
    csrf.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"csrfmiddlewaretoken\""));
    csrf.setBody(csrftoken.toUtf8());
    form->append(csrf);

    QHttpPart id_family;
    id_family.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"family\""));
    id_family.setBody(familyId.toUtf8());
    form->append(id_family);

    QHttpPart photo;
    //TODO: Make ContentType header get its value from the file
    photo.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    photo.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\"" + filename + "\""));
    //QFile *file = new QFile("/tmp/capt0000.jpg");
    QFile *file = new QFile(filename);
    file->open(QIODevice::ReadOnly);
    photo.setBodyDevice(file);
    file->setParent(form);
    form->append(photo);
    
    /*while (!file->atEnd()) {
         QByteArray line = file->readLine();
         qDebug() << line;
     }
     exit(0);*/

    //test.setHeader(QNetworkRequest::ContentDispositionHeader, "multipart/form-data; boundary=" + form->boundary());

    QNetworkReply * repl = qnam->post(test, form);
    form->setParent(repl);

    connect(repl, SIGNAL(finished()), this, SLOT(uploadComplete()));
    //connect(repl, SIGNAL(finished()), repl, SLOT(deleteLater()));
}
