#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include "familycompleter.h"

#include <gphoto2/gphoto2-camera.h>

#include "settingsdialog.h"
#include "imagedisplaydialog.h"

namespace Ui {
    class InfoDialog;
}

void error_func (GPContext *context, const char *format, va_list args, void *data);
void message_func (GPContext *context, const char *format, va_list args, void *data);

class InfoDialog : public QDialog {
    Q_OBJECT
public:
    InfoDialog(QWidget *parent = 0);
    ~InfoDialog();

    static int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in);

    void logMessage(const QString message);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::InfoDialog *ui;

    void rereadCameraInfo();
    void canon_enable_capture(Camera *camera, GPContext *context, CameraWidget *config);
    void populateWithConfigs(CameraWidget *cc);
    int result_check(int retval, QString message = "");

    GPContext *context;
    Camera *camera;
    ImageDisplayDialog dialog;
    FamilyCompleter *completer;
    QModelIndex family;
    double family_id;

    void notImplementedError();
    void uploadImage(CameraFile *cf);
    void setImage(CameraFile *cf, QString &method, bool out = true);

signals:
    void familyChanged();
    void imageSaved( const char * );

private slots:
    void on_pb_capture_preview_clicked();
    void on_pb_capture_image_clicked();
    void on_pb_rescan_clicked();
    void log(QString lt);
    void setFamily(QModelIndex mi);
    void processPreview(CameraFile *cf);
};



#endif // INFODIALOG_H
