#include "QDebug"
#include "mythread.h"

MyThread::MyThread(QObject *parent)  { }
MyThread::~MyThread() { }


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
    void *data;
    qDebug() << "In Thread!!";

    while (running)
    {
        retval = gp_camera_wait_for_event(camera, 200, &type, &data, context);
        //qDebug() << "Waiting - retval: " << retval;
        if( retval != 0 ){
            qDebug() << "Error!! " << gp_result_as_string(retval);
            break;
        }
        switch( type )
        {
        case GP_EVENT_UNKNOWN:
        case GP_EVENT_FOLDER_ADDED:
        case GP_EVENT_TIMEOUT:
            continue;
        case GP_EVENT_FILE_ADDED:
            qDebug() << "File added" << data;
            //qDebug() << "Emit Signal";
        case GP_EVENT_CAPTURE_COMPLETE:
            qDebug() << "Capture complete";
            //emit imageAvailable(cf);
        }
    }
}

void MyThread::mysleep(unsigned long time)
{
    //sleep(time);
}
