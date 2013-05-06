#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QDebug>
#include <QPushButton>
#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QSettings settings;
    settings.beginGroup("Preferences");
    ui->signoutonquit->setChecked(settings.value("signoutonquit", true).toBool());
    ui->keeptempfiles->setChecked(settings.value("keeptempfiles", false).toBool());
    ui->lineEdit->setText(settings.value("directory", "/tmp").toString());
    settings.endGroup();
    ui->buttons->button(QDialogButtonBox::Apply)->setEnabled(false);
    connect(ui->buttons, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonHandler(QAbstractButton*)));
    connect(ui->signoutonquit, SIGNAL(toggled(bool)), this, SLOT(changed()));
    connect(ui->keeptempfiles, SIGNAL(toggled(bool)), this, SLOT(changed()));
}

void SettingsDialog::changed()
{
    QSettings settings;
    settings.beginGroup("Preferences");
    if( (ui->signoutonquit->isChecked() != settings.value("signoutonquit", true).toBool())
            or (ui->keeptempfiles->isChecked() != settings.value("keeptempfiles", false).toBool())
            or (ui->lineEdit->text() != settings.value("directory", "/tmp").toString()))
    {
        ui->buttons->button(QDialogButtonBox::Apply)->setEnabled(true);
    } else {
        ui->buttons->button(QDialogButtonBox::Apply)->setEnabled(false);
    }
    settings.endGroup();
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
        settings.setValue("directory", ui->lineEdit->text());
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

void SettingsDialog::on_pushButton_pressed()
{
    QString initialDir = "/tmp";
    if( !ui->lineEdit->text().isEmpty() ) {
        initialDir = ui->lineEdit->text();
    }
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Folder"), initialDir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if( !dir.isNull() ) {
        ui->lineEdit->setText(dir);
        changed();
    }
}
