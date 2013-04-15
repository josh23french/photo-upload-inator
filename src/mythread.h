#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <gphoto2/gphoto2-camera.h>

class MyThread : public QObject
{
    Q_OBJECT

public slots:
    void start();

public:
    explicit MyThread(QObject *parent = 0);
    ~MyThread();

    void setData(GPContext *lcontext, Camera *lcamera);
    int result_check(int retval, QString message);

    void mysleep(unsigned long time);
    bool running;

signals:
    void imageAvailable(CameraFile *cf);


private:
    GPContext *context;
    Camera *camera;
};

#endif // MYTHREAD_H
