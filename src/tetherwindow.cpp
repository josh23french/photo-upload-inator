#include "tetherwindow.h"
#include "ui_tetherwindow.h"
#include <libexif/exif-loader.h>
#include "tetherthumb.h"
#include "imagedisplaydialog.h"
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
}

TetherWindow::~TetherWindow()
{
    delete ui;
}

void TetherWindow::showSettingsDialog()
{
    SettingsDialog *sd = new SettingsDialog(this);
    sd->exec();
    sd->deleteLater();
}

void TetherWindow::displayFullForThumb( QListWidgetItem * thumb)
{
    currentFilename = thumb->data(Qt::EditRole).toString();
    displayFullForFilename(currentFilename);
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

void TetherWindow::displayThumbForTethered( const char * filename )
{
    TetherThumb *label = new TetherThumb(filename, this);
    QListWidgetItem *l = new QListWidgetItem();
    l->setSizeHint(label->pixmap()->size());
    l->setData(Qt::EditRole, filename);
    ui->thumbList->insertItem(0,l);
    ui->thumbList->setItemWidget(l, label);
    //ui->scrollAreaWidgetContents->layout()->addWidget(label);
    //ui->scrollAreaWidgetContents->layout()->setAlignment(label, Qt::AlignTop);
    displayFullForThumb(l);
}

void TetherWindow::displayThumbForJPEG()
{
    //const char * filename = "/tmp/canon-ixus.jpg";
    QByteArray la = ui->searchbox->text().toLatin1().constData();
    const char * filename = la.constData();
    qDebug() << filename;
    TetherThumb *label = new TetherThumb(filename, this);
    connect(label, SIGNAL(clicked(const char*)), this, SLOT(displayFullForThumb(const char*)));
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

void TetherWindow::uploadImage(QString f, int fd)
{
    logMessage("Upload called.");

    emit imageSaved(f.toLocal8Bit());
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
    ::close(fd);
}

void TetherWindow::setFamily(QString fam, QString familyId)
{
    this->family = fam;
    this->family_id = familyId.toDouble();
    ui->familyGrp->setTitle("Family: " + this->family.replace(" & "," && ") + " (" + QString::number(this->family_id) + ")");
    emit familyChanged();
    ui->preview->setPicture(NULL);
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
