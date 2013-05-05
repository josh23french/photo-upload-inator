#ifndef TETHERWINDOW_H
#define TETHERWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <map>
#include <string>
#include <QListWidgetItem>
#include <gphoto2/gphoto2-camera.h>
#include "photouploadinator.h"
#include "mythread.h"
#include "tetherthumb.h"
#include "flowlayout.h"

namespace Ui {
class TetherWindow;
}

typedef std::map<std::string, QPixmap> Cache;

void error_func (GPContext *context, const char *format, va_list args, void *data);
void message_func (GPContext *context, const char *format, va_list args, void *data);


class TetherWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TetherWindow(QWidget *parent = 0);
    ~TetherWindow();
    void logMessage(const QString message);
    static int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in);

public slots:
    void displayThumbForJPEG();
    void displayFullForThumb(TetherThumb * );
    void displayThumbForTethered( const char *filename );
    void displayFullForFilename(QString filename );
    void displayFullForCurrent();

    void rereadCameraInfo();
    void uploadImage(QString f, int fd);

    void showSettingsDialog();

signals:
    void familyChanged();
    void imageSaved( const char * );

private slots:
    void on_actionSign_in_triggered();
    void on_actionDetect_Camer_triggered();
    void on_actionCapture_triggered();
    void setFamily(QString fam, QString familyId);
    void writeGeometry();
    void startCapturing();

protected:
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    void moveEvent(QMoveEvent *event);

private:
    int result_check(int retval, QString message = "");
    void canon_enable_capture(Camera *camera, GPContext *context, CameraWidget *config);

    Ui::TetherWindow *ui;
    QTimer *resizeTimer;
    Cache cached;
    QString currentFilename;
    GPContext *context;
    Camera *camera;
    //ImageDisplayDialog dialog;
    //FamilyCompleter *completer;
    QString family;
    double family_id;
    QPoint normalpos;
    QSize normalsize;
    PhotoUploadInator uploader;
    QThread *thread;
    MyThread *waiter;
    bool startedThread;
    FlowLayout * thumbList;
};

#endif // TETHERWINDOW_H
