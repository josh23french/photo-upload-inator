#include "QDebug"
#include "mythread.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

MyThread::MyThread(QObject *parent) {
    qDebug() << "I'm Alive!!!";
    running = false;
}
MyThread::~MyThread() {
    qDebug() << "I'm Dying!!!";
}


void MyThread::setData(GPContext *lcontext, Camera *lcamera)
{
    context = lcontext;
    camera = lcamera;

    running = true;
}

int MyThread::result_check(int retval, QString message) {
    if (retval < GP_OK) {
        QString log;
        if (message.size() == 0)
            log += QString(gp_result_as_string(retval));
        else
            log.sprintf("%s: %s\n",message.toStdString().c_str(),gp_result_as_string(retval));
        qDebug() << log;
    }
    return retval;
}


void MyThread::start()
{
    int retval;
    CameraEventType type;
    CameraFilePath *cfp;
    CameraFile *file;
    QString filename;
    int fd;
    void *data;
    qDebug() << "In Thread!!";

    while (running)
    {
        retval = gp_camera_wait_for_event(camera, 200, &type, &data, context);
        //qDebug() << "Waiting - retval: " << retval;
        if( retval != 0 ){
            qDebug() << "Error!! " << gp_result_as_string(retval);
            emit error();
            break;
        }
        switch( type )
        {
        case GP_EVENT_UNKNOWN:
        case GP_EVENT_FOLDER_ADDED:
        case GP_EVENT_TIMEOUT:
            continue;
        case GP_EVENT_FILE_ADDED:
            qDebug() << "File added";
            cfp = (CameraFilePath*)data;
            //qDebug() << cfp->folder << cfp->name;
            filename = QString(tmpnam(NULL));
            filename.append(".jpg");
            fd = open(filename.toLocal8Bit(), O_CREAT | O_WRONLY, 0644);
            retval = gp_file_new_from_fd(&file, fd);
            qDebug() << "Read for file - " << gp_result_as_string(retval);
            retval = gp_camera_file_get(camera, cfp->folder, cfp->name, GP_FILE_TYPE_NORMAL, file, context);
            qDebug() << "Got file - " << gp_result_as_string(retval);
            retval = gp_camera_file_delete(camera, cfp->folder, cfp->name, context);
            qDebug() << "Deleted file - " << gp_result_as_string(retval);
            emit imageAvailable(filename, fd);
            //qDebug() << "Emit Signal";
        case GP_EVENT_CAPTURE_COMPLETE:
            qDebug() << "Capture complete";
            //emit imageAvailable(cf);
        }
    }
}

void MyThread::mysleep(unsigned long time)
{
    usleep(time);
}
