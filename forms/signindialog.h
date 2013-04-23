#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

#include <QDialog>

namespace Ui {
class SignInDialog;
}

class SignInDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SignInDialog(QWidget *parent = 0);
    ~SignInDialog();
    QString username();
    QString password();
    void setUsername(QString un);
    void setPassword(QString un);
    
private:
    Ui::SignInDialog *ui;
};

#endif // SIGNINDIALOG_H
