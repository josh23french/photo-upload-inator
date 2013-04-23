#include "signindialog.h"
#include "ui_signindialog.h"

SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);
}

void SignInDialog::setUsername(QString un)
{
    ui->username->setText(un);
    if( un.isEmpty() )
        return;
    ui->password->setFocus();
}

void SignInDialog::setPassword(QString un)
{
    ui->password->setText(un);
}

QString SignInDialog::username()
{
    return ui->username->text();
}

QString SignInDialog::password()
{
    return ui->password->text();
}

SignInDialog::~SignInDialog()
{
    delete ui;
}
