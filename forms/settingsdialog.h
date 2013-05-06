#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QAbstractButton>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    
private slots:
    void buttonHandler(QAbstractButton *button);
    void changed();

    void on_pushButton_pressed();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
