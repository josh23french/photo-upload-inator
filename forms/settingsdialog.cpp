#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QDebug>
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QSettings settings;
    settings.beginGroup("Preferences");
    ui->signoutonquit->setChecked(settings.value("signoutonquit", true).toBool());
    ui->keeptempfiles->setChecked(settings.value("keeptempfiles", false).toBool());
    settings.endGroup();
    ui->buttons->button(QDialogButtonBox::Apply)->setEnabled(false);
    connect(ui->buttons, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonHandler(QAbstractButton*)));
    connect(ui->signoutonquit, SIGNAL(toggled(bool)), this, SLOT(changed()));
    connect(ui->keeptempfiles, SIGNAL(toggled(bool)), this, SLOT(changed()));
}

void SettingsDialog::changed()
{
    QSettings settings;
    qDebug() << (ui->signoutonquit->isChecked() == settings.value("signoutonquit", true).toBool());
    if( (ui->signoutonquit->isChecked() == settings.value("signoutonquit", true).toBool())
            or (ui->keeptempfiles->isChecked() == settings.value("keeptempfiles", false).toBool()))
    {
        ui->buttons->button(QDialogButtonBox::Apply)->setEnabled(true);
    } else {
        ui->buttons->button(QDialogButtonBox::Apply)->setEnabled(false);
    }
}

void SettingsDialog::buttonHandler(QAbstractButton *button)
{
    QSettings settings;
    switch(ui->buttons->standardButton(button))
    {
    case QDialogButtonBox::Apply:
        qDebug() << "Apply Pressed";
        settings.beginGroup("Preferences");
        settings.setValue("signoutonquit", ui->signoutonquit->isChecked());
        settings.setValue("keeptempfiles", ui->keeptempfiles->isChecked());
        settings.endGroup();
        button->setEnabled(false);
        settings.sync();
        break;
    case QDialogButtonBox::Reset:
        //qDebug() << "Reset Pressed";
        ui->signoutonquit->setChecked(true);
        ui->keeptempfiles->setChecked(false);
        break;
    default:
        break;
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
