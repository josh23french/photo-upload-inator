/********************************************************************************
** Form generated from reading UI file 'imagedisplaydialog.ui'
**
** Created: Mon Feb 18 12:04:09 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEDISPLAYDIALOG_H
#define UI_IMAGEDISPLAYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ImageDisplayDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QDialog *ImageDisplayDialog)
    {
        if (ImageDisplayDialog->objectName().isEmpty())
            ImageDisplayDialog->setObjectName(QString::fromUtf8("ImageDisplayDialog"));
        ImageDisplayDialog->resize(379, 237);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImageDisplayDialog->sizePolicy().hasHeightForWidth());
        ImageDisplayDialog->setSizePolicy(sizePolicy);
        ImageDisplayDialog->setSizeGripEnabled(true);
        horizontalLayout = new QHBoxLayout(ImageDisplayDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ImageDisplayDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);


        retranslateUi(ImageDisplayDialog);

        QMetaObject::connectSlotsByName(ImageDisplayDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageDisplayDialog)
    {
        ImageDisplayDialog->setWindowTitle(QApplication::translate("ImageDisplayDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ImageDisplayDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Sorry, Image could not be displayed!</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This often means that this unfortunately </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">command is not working on your"
                        " camera.</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageDisplayDialog: public Ui_ImageDisplayDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEDISPLAYDIALOG_H
