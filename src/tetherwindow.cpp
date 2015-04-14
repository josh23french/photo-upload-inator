#include "tetherwindow.h"
#include "ui_tetherwindow.h"
#include <libexif/exif-loader.h>
#include "tetherthumb.h"
#include <QDebug>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "QMessageBox"
#include "QDebug"
#include "curl/curl.h"
#include <forms/signindialog.h>
#include <gphoto2/gphoto2-version.h>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <src/fastresizer.h>
#include <QTimer>
#include "mythread.h"
#include <unistd.h>
#include "settingsdialog.h"
#include <QWindowStateChangeEvent>
#include "photouploadinator.h"
#include "flowlayout.h"

static int _lookup_widget(CameraWidget*widget, const char *key, CameraWidget **child)
{
    int ret;
    ret = gp_widget_get_child_by_name (widget, key, child);
    if (ret < GP_OK)
        ret = gp_widget_get_child_by_label (widget, key, child);
    return ret;

}

TetherWindow::TetherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TetherWindow)
{
    ui->setupUi(this);
    startedThread = false;
    ui->menuView->addAction(ui->dockWidget->toggleViewAction());
    mirrorDisplay = new PreviewGraphicsView(parent);
    connect(mirrorDisplay, SIGNAL(visibilityChanged(bool)), ui->actionSecondary_Preview, SLOT(setChecked(bool)));

    QWidget * tl = new QWidget(ui->scrollArea);
    ui->scrollArea->setWidget(tl);
    ui->scrollArea->setWidgetResizable(true);
    thumbList = new FlowLayout();
    tl->setLayout(thumbList);

    QSettings settings;
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
    move(settings.value("pos", QPoint(100, 100)).toPoint());
    resize(settings.value("size", QSize(800, 600)).toSize());
    if( settings.value("maximized", isMaximized()).toBool() ) {
        showMaximized();
    }

    settings.endGroup();

    //ui->menuView->addAction(ui->dockWidget_2->toggleViewAction());

    //FamilyCompleter *completer = new FamilyCompleter(this);
    //ui->searchbox->setCompleter(completer);
    //connect(ui->searchbox,SIGNAL(textEdited(QString)),completer,SLOT(update(QString)));
    connect(ui->searchbox->completer, SIGNAL(doneCompletion(QString,QString)), this, SLOT(setFamily(QString,QString)));
    connect(&uploader, SIGNAL(sendLog(QString)), this, SLOT(logMessage(QString)));
    this->family_id = 0;
    context = NULL;
    camera = NULL;
    this->rereadCameraInfo();
    //connect(ui->thumbList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayFullForThumb(QListWidgetItem*)));
    //connect(completer,SIGNAL(activated(QModelIndex)),this,SLOT(setFamily(QModelIndex)));
    //resizeTimer = new QTimer();
    //resizeTimer->setSingleShot(true);
    //connect(resizeTimer, SIGNAL(timeout()), this, SLOT(displayFullForCurrent()));
}

void TetherWindow::moveEvent(QMoveEvent *event)
{
    QTimer::singleShot(10, this, SLOT(writeGeometry()));
    //DUMBEST HACK EVER. STUPID QT.
}

void TetherWindow::resizeEvent(QResizeEvent * event)
{
    QTimer::singleShot(10, this, SLOT(writeGeometry()));
    //DUMBEST HACK EVER. STUPID QT.
}

void TetherWindow::displayFullForCurrent(){
    displayFullForFilename(currentFilename);
}

void TetherWindow::writeGeometry()
{
    QSettings settings;
    settings.beginGroup( "MainWindow" );
    settings.setValue( "geometry", saveGeometry() );
    settings.setValue( "state", saveState() );
    settings.setValue( "maximized", isMaximized() );
    if( !isMaximized() ) {
        settings.setValue( "size", size() );
        settings.setValue( "pos", pos() );
        //qDebug() << "WINDOW IS NOT MAXIMIZED" << size() << pos();
    }
    settings.endGroup();
}

void TetherWindow::closeEvent(QCloseEvent *event)
{
    writeGeometry();
    maybeDeleteCurrentFamilyFiles();
    mirrorDisplay->close();
}

TetherWindow::~TetherWindow()
{
    delete ui;
}

void TetherWindow::maybeDeleteCurrentFamilyFiles()
{
    QSettings settings;
    if( (family_id == NULL) or settings.value("Preferences/keeptempfiles").toBool() == true ) {
        qDebug() << "family_id is null or keeptempfiles is true";
        return;
    }
    qDebug() << "Attempting to delete files...";
    QString dirName = settings.value("Preferences/directory", "/tmp").toString() + "/" + QString::number(family_id);
    QDir dir(dirName);
    bool result;
    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                qDebug() << "WHY IS THERE A DIRECTORY IN HERE?!";
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                qDebug() << "Error!! Could not delete file!";
            }
        }
        result = dir.rmdir(dirName);
    }
}

void TetherWindow::showSettingsDialog()
{
    SettingsDialog *sd = new SettingsDialog(this);
    sd->exec();
    sd->deleteLater();
}

void TetherWindow::displayFullForThumb( TetherThumb * thumb)
{
    currentFilename = thumb->filename;
    displayFullForFilename(currentFilename);
    if( mirrorDisplay->isVisible() ) {
        mirrorDisplay->setPicture(currentFilename);
    }
}

void TetherWindow::displayFullForFilename( QString filename )
{
    if( filename.isEmpty() )
            return;
    currentFilename = filename;
    qDebug() << "Got filename: " << filename;
    ui->preview->setPicture(filename);
    return;
}

void TetherWindow::displayThumbForTethered( QString filename )
{
    TetherThumb *label = new TetherThumb(filename, this);
    thumbList->insertWidgetAt(label, 0);
    connect(label, SIGNAL(clicked(TetherThumb *)), this, SLOT(displayFullForThumb(TetherThumb *)));
    displayFullForThumb(label);
}

void TetherWindow::displayThumbForJPEG()
{
    //QByteArray la = ui->searchbox->text().toLatin1().constData();
    //const char * filename = la.constData();
    TetherThumb *label = new TetherThumb("/tmp/fileeZcvL5.jpg", ui->scrollArea->widget());
    //ui->scrollArea->widget()->layout()->addWidget(label);
    thumbList->insertWidgetAt(label, 0);
    //ui->scrollArea->widget()->layout()->addWidget();
    connect(label, SIGNAL(clicked(TetherThumb *)), this, SLOT(displayFullForThumb(TetherThumb *)));
}

void TetherWindow::on_actionSign_in_triggered()
{
    SignInDialog *sid = new SignInDialog();
    sid->exec();
}

void TetherWindow::canon_enable_capture(Camera *camera, GPContext *context, CameraWidget *config)
{
    int onoff = 1;
    CameraWidgetType type;
    CameraWidget *child;
    int ret;

    printf("CANON ENABLE CAPTURE Config is at %p\n", config);
    ret = _lookup_widget (config, "capture", &child);
    if (ret < GP_OK) {
        fprintf (stderr, "lookup widget failed: %d\n", ret);
        goto out;
    }

    ret = gp_widget_get_type (child, &type);
    if (ret < GP_OK) {
        fprintf (stderr, "widget get type failed: %d\n", ret);
        goto out;
    }
    switch (type) {
    case GP_WIDGET_TOGGLE:
        break;
    default:
        fprintf (stderr, "widget has bad type %d\n", type);
        ret = GP_ERROR_BAD_PARAMETERS;
        goto out;
    }
    /* Now set the toggle to the wanted value */
    ret = gp_widget_set_value (child, &onoff);
    if (ret < GP_OK) {
        fprintf (stderr, "toggling Canon capture to %d failed with %d\n", onoff, ret);
        goto out;
    }
    /* OK */
    ret = gp_camera_set_config (camera, config, context);
    if (ret < GP_OK) {
        fprintf (stderr, "camera_set_config failed: %d\n", ret);
        return;
    }

    out:
    child=NULL;
    return;
}

void TetherWindow::rereadCameraInfo()
{
    // Parameters and Variables
    //CameraStorageInformation    *storage;

    int ret = 0;
    //int tmp = 0;

    // Creating Context and Camera
//sdialog.clearItems();

    if( camera ) {
        gp_camera_exit(camera, context);
        logMessage(QString("Destroying camera"));
    }
    logMessage(QString("Initializing camera"));
    context = gp_context_new();

    gp_camera_new (&camera);
    ret = result_check(gp_camera_init (camera, context),"gp_camera_init");

    if (ret < GP_OK) {
        logMessage(QString("No camera connected!"));
        gp_camera_free (camera);
        free(context);
        camera = NULL;
        context = NULL;
        return;
    }

    // set callbacks for camera messages
     gp_context_set_error_func(context, error_func, NULL);
     gp_context_set_message_func(context, message_func, NULL);


    // summary
    CameraText sum;
    result_check(gp_camera_get_summary(camera,&sum,context),"gp_camera_get_summary");
    logMessage(QString(sum.text));

    // about
    CameraText about;
    result_check(gp_camera_get_about(camera,&about,context),"gp_camera_get_about");
    logMessage(QString(about.text));


    /*/ Reading Storage information
    logMessage(QString("Loading Storage configuration"));
    ret = result_check(gp_camera_get_storageinfo( camera, &storage, &tmp, context),"gp_camera_get_storageinfo");

    ui->lb_images_left->setText( QString::number( storage->freeimages ));
    ui->lb_space_total->setText( QString::number( storage->capacitykbytes ));
    ui->lb_space_left->setText( QString::number( storage->freekbytes ));

    free(storage);

    */
    // Camera Settings
    CameraWidget *config = NULL;
    logMessage(QString("Read configuration"));
    ret = result_check(gp_camera_get_config (camera, &config, context),"gp_camera_get_config");
    canon_enable_capture(camera, context, config);

    //populateWithConfigs(config);

    gp_widget_free (config);

    // Abilities
    CameraAbilities abilities;
    logMessage(QString("Checking camera abilities"));
    ret = result_check(gp_camera_get_abilities (camera, &abilities),"gp_camera_get_abilities");

    if (ret >= GP_OK)
    {
            QString log;
            log.sprintf("Abilities: %s\n", gp_result_as_string(ret));

            logMessage( log );
    }
    logMessage(QString("Init complete."));
}

void error_func (GPContext *context, const char *format, va_list args, void *data) {
 fprintf  (stderr, "*** Contexterror ***\n");
 vfprintf (stderr, format, args);
 fprintf  (stderr, "\n");
}

void message_func (GPContext *context, const char *format, va_list args, void *data) {
 vprintf (format, args);
 printf ("\n");
}

void TetherWindow::logMessage(const QString message)
{
    ui->log->appendPlainText(message);
    QApplication::processEvents();
}

int TetherWindow::result_check(int retval, QString message) {
    if (retval < GP_OK) {
        QString log;
        if (message.size() == 0)
            log += QString(gp_result_as_string(retval));
        else
            log.sprintf("%s: %s\n",message.toStdString().c_str(),gp_result_as_string(retval));
        logMessage(log);
    }
    return retval;
}

void TetherWindow::on_actionDetect_Camer_triggered()
{
    qDebug() << "Detecting camera...";
    rereadCameraInfo();
    if( family_id && camera && !startedThread) {
        qDebug() << "capturing...";
        on_actionCapture_triggered();
    }
}

void TetherWindow::on_actionCapture_triggered()
{
    qDebug() << "Trigger";
    if( startedThread ) {
        qDebug() << "Stopping Process";
        ui->stop->setEnabled(false);
        qDebug() << "-4";
        ui->stop->setText("Start");
        qDebug() << "-3";
        //if(camera == NULL)
        //     return;
        qDebug() << "-2";
        waiter->running = false;
        qDebug() << "-1";
        waiter->mysleep(500);
        qDebug() << "0";
        thread->quit();
        qDebug() << "1";
        waiter->deleteLater();
        qDebug() << "2";
        ui->stop->setEnabled(true);
        qDebug() << "3";
        startedThread = false;
        return;
    }
    qDebug() << "Starting Process";
    ui->stop->setEnabled(false);
    ui->stop->setText("Stop");
    ui->stop->setEnabled(true);
    startCapturing();
}

int TetherWindow::writer(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{
    // Is there anything in the buffer?
    if (buffer_in != NULL)
    {
        // Append the data to the buffer
        buffer_in->append(data, size * nmemb);

        // How much did we write?
        return size * nmemb;
    }

    return 0;
}

QString TetherWindow::moveImage(QString f)
{
    QDate date = QDate::currentDate();
    QString dateString = date.toString("MMddyy");
    seq +=1;
    QSettings settings;
    QDir dir(settings.value("Preferences/directory", "/tmp").toString() + "/" + QString::number(family_id));
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QString new_f =  dir.absolutePath() + "/" + QString::number(family_id) + "_" + dateString + "_" + QString::number(seq) + ".jpg";
    QFile nf(new_f);
    if( nf.exists() ) {
        // This works because we increment the seq number. Is this worse than a while loop?
        return moveImage(f);
    }
    logMessage("MOVED IMAGE!!! " + new_f );
    QFile::rename(f, new_f);
    return new_f;
}

void TetherWindow::uploadImage(QString f, int fd)
{
    ::close(fd);
    logMessage("Upload called.");
    f = moveImage(f);
    emit imageSaved(f);
    this->setEnabled(true);

    if (this->family_id == 0)
    {
        logMessage("No Family ID!!");
        QMessageBox *x = new QMessageBox(this);
        x->setWindowTitle("Error!");
        x->setIcon(QMessageBox::Critical);
        x->setText("No Family ID set!!\nImage was saved to " + f);
        x->exec();
        return;
    }

    logMessage("Uploading image...");
    uploader.addUpload(f);
}

void TetherWindow::setFamily(QString fam, QString familyId)
{
    maybeDeleteCurrentFamilyFiles();
    thumbList->clear();
    this->family = fam;
    this->family_id = familyId.toDouble();
    seq = 0;
    ui->familyGrp->setTitle("Family: " + this->family.replace(" & "," && ") + " (" + QString::number(this->family_id) + ")");
    emit familyChanged();
    ui->preview->setPicture(NULL);
    mirrorDisplay->setPicture(NULL);
    uploader.setFamily(familyId);
    if( !startedThread ) {
        on_actionCapture_triggered();
    }
}

void TetherWindow::startCapturing()
{
    qDebug() << "startCapturing()";
    if(camera == NULL) {
        qDebug() << "... DON'T have camera ...";
        on_actionDetect_Camer_triggered();
        return;
    }
    qDebug() << "... have camera ...";
    QApplication::processEvents();

    thread = new QThread();
    waiter = new MyThread();
    waiter->moveToThread( thread );

    QObject::connect( thread, SIGNAL(started()), waiter, SLOT(start()));
    QObject::connect( waiter, SIGNAL(imageAvailable(QString, int)), this, SLOT(uploadImage(QString,int)));

    waiter->setData(context,camera);
    thread->start();
    connect(waiter, SIGNAL(error()), this, SLOT(on_actionCapture_triggered()));
    ui->stop->setEnabled(true);
    qDebug() << "Thread started";
    startedThread = true;
}

void TetherWindow::on_actionSecondary_Preview_toggled(bool arg1)
{
    if(arg1) {
        connect(this, SIGNAL(imageSaved(QString)), mirrorDisplay, SLOT(setPicture(QString)));
        mirrorDisplay->show();
        mirrorDisplay->setPicture(currentFilename);
        QRect screenres = QApplication::desktop()->screenGeometry(1);
        qDebug() << screenres;
        mirrorDisplay->move(QPoint(screenres.x(), screenres.y()));
        /*
         * For some reason, the following causes an issue.. probably because the WM
         * reserves height for the system menu
        */
        //mirrorDisplay->resize(screenres.width(), screenres.height());
        mirrorDisplay->showFullScreen();
    } else {
        mirrorDisplay->hide();
        disconnect(this, SIGNAL(imageSaved(QString)), mirrorDisplay, SLOT(setPicture(QString)));
    }
    qDebug() << "Mirror display visibility: " << mirrorDisplay->isVisible();
}
