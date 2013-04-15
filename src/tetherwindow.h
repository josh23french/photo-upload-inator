#ifndef TETHERWINDOW_H
#define TETHERWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <map>
#include <string>
#include <QListWidgetItem>
#include <src/familycompleter.h>
#include <gphoto2/gphoto2-camera.h>

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
    void displayFullForThumb( QListWidgetItem * );
    void displayThumbForTethered( const char *filename );
    void displayFullForFilename(QString filename );
    void rereadCameraInfo();
    void displayFullFromPixmap(QPixmap pic);
    void receiveScaled(QImage image, QString filename);
    void displayFullForCurrent();
    void uploadImage(QString f, int fd);

signals:
    void familyChanged();
    void imageSaved( const char * );

private slots:
    void on_actionSign_in_triggered();
    void on_actionDetect_Camer_triggered();
    void on_actionCapture_triggered();
    void setFamily(QModelIndex mi);

protected:
    void resizeEvent(QResizeEvent *event);
    void changeEvent(QEvent *event);

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
    FamilyCompleter *completer;
    QModelIndex family;
    double family_id;
};

#endif // TETHERWINDOW_H
