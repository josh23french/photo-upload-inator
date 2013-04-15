/********************************************************************************
** Form generated from reading UI file 'infodialog.ui'
**
** Created: Mon Feb 18 12:04:09 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFODIALOG_H
#define UI_INFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InfoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *familyGrp;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *searchbox;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lb_version_local;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *lb_model;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLabel *lb_quality;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLabel *lb_images_left;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLabel *lb_space_total;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLabel *lb_space_left;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *lb_capture_image;
    QPushButton *pb_capture_image;
    QHBoxLayout *horizontalLayout_11;
    QLabel *lb_capture_preview;
    QPushButton *pb_capture_preview;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *pb_rescan;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_close;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *log;

    void setupUi(QDialog *InfoDialog)
    {
        if (InfoDialog->objectName().isEmpty())
            InfoDialog->setObjectName(QString::fromUtf8("InfoDialog"));
        InfoDialog->resize(544, 429);
        verticalLayout = new QVBoxLayout(InfoDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        familyGrp = new QGroupBox(InfoDialog);
        familyGrp->setObjectName(QString::fromUtf8("familyGrp"));
        horizontalLayout_9 = new QHBoxLayout(familyGrp);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        searchbox = new QLineEdit(familyGrp);
        searchbox->setObjectName(QString::fromUtf8("searchbox"));

        horizontalLayout_9->addWidget(searchbox);


        verticalLayout->addWidget(familyGrp);

        groupBox_4 = new QGroupBox(InfoDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setStyleSheet(QString::fromUtf8("QLabel:disabled {\n"
"	color: rgb(211, 211, 211);\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox = new QGroupBox(groupBox_4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lb_version_local = new QLabel(groupBox);
        lb_version_local->setObjectName(QString::fromUtf8("lb_version_local"));

        horizontalLayout_2->addWidget(lb_version_local);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lb_model = new QLabel(groupBox);
        lb_model->setObjectName(QString::fromUtf8("lb_model"));

        horizontalLayout_4->addWidget(lb_model);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        lb_quality = new QLabel(groupBox);
        lb_quality->setObjectName(QString::fromUtf8("lb_quality"));

        horizontalLayout_5->addWidget(lb_quality);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        lb_images_left = new QLabel(groupBox);
        lb_images_left->setObjectName(QString::fromUtf8("lb_images_left"));

        horizontalLayout_6->addWidget(lb_images_left);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        lb_space_total = new QLabel(groupBox);
        lb_space_total->setObjectName(QString::fromUtf8("lb_space_total"));

        horizontalLayout_7->addWidget(lb_space_total);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_8->addWidget(label_7);

        lb_space_left = new QLabel(groupBox);
        lb_space_left->setObjectName(QString::fromUtf8("lb_space_left"));

        horizontalLayout_8->addWidget(lb_space_left);


        verticalLayout_4->addLayout(horizontalLayout_8);


        horizontalLayout_3->addWidget(groupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        lb_capture_image = new QLabel(groupBox_4);
        lb_capture_image->setObjectName(QString::fromUtf8("lb_capture_image"));
        lb_capture_image->setEnabled(false);

        horizontalLayout_10->addWidget(lb_capture_image);

        pb_capture_image = new QPushButton(groupBox_4);
        pb_capture_image->setObjectName(QString::fromUtf8("pb_capture_image"));
        pb_capture_image->setEnabled(false);
        pb_capture_image->setMinimumSize(QSize(72, 0));
        pb_capture_image->setAutoDefault(false);

        horizontalLayout_10->addWidget(pb_capture_image);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        lb_capture_preview = new QLabel(groupBox_4);
        lb_capture_preview->setObjectName(QString::fromUtf8("lb_capture_preview"));
        lb_capture_preview->setEnabled(false);

        horizontalLayout_11->addWidget(lb_capture_preview);

        pb_capture_preview = new QPushButton(groupBox_4);
        pb_capture_preview->setObjectName(QString::fromUtf8("pb_capture_preview"));
        pb_capture_preview->setEnabled(false);
        pb_capture_preview->setMinimumSize(QSize(72, 0));
        pb_capture_preview->setAutoDefault(false);

        horizontalLayout_11->addWidget(pb_capture_preview);


        verticalLayout_2->addLayout(horizontalLayout_11);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addWidget(groupBox_4);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        pb_rescan = new QPushButton(InfoDialog);
        pb_rescan->setObjectName(QString::fromUtf8("pb_rescan"));

        horizontalLayout_15->addWidget(pb_rescan);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer);

        pb_close = new QPushButton(InfoDialog);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setAutoDefault(false);
        pb_close->setDefault(false);

        horizontalLayout_15->addWidget(pb_close);


        verticalLayout->addLayout(horizontalLayout_15);

        groupBox_3 = new QGroupBox(InfoDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 150));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        log = new QPlainTextEdit(groupBox_3);
        log->setObjectName(QString::fromUtf8("log"));
        log->setMaximumSize(QSize(16777215, 100));
        log->setLineWrapMode(QPlainTextEdit::NoWrap);
        log->setReadOnly(true);
        log->setCenterOnScroll(false);

        horizontalLayout->addWidget(log);


        verticalLayout->addWidget(groupBox_3);


        retranslateUi(InfoDialog);
        QObject::connect(pb_close, SIGNAL(clicked()), InfoDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(InfoDialog);
    } // setupUi

    void retranslateUi(QDialog *InfoDialog)
    {
        InfoDialog->setWindowTitle(QApplication::translate("InfoDialog", "LBC Directory", 0, QApplication::UnicodeUTF8));
        familyGrp->setTitle(QApplication::translate("InfoDialog", "Family", 0, QApplication::UnicodeUTF8));
        searchbox->setPlaceholderText(QApplication::translate("InfoDialog", "Search for family...", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("InfoDialog", "Camera", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("InfoDialog", "GPhoto Version:", 0, QApplication::UnicodeUTF8));
        lb_version_local->setText(QApplication::translate("InfoDialog", "VERSION", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("InfoDialog", "Model", 0, QApplication::UnicodeUTF8));
        lb_model->setText(QString());
        label_4->setText(QApplication::translate("InfoDialog", "Driver Quality", 0, QApplication::UnicodeUTF8));
        lb_quality->setText(QString());
        label_5->setText(QApplication::translate("InfoDialog", "Number of Images left", 0, QApplication::UnicodeUTF8));
        lb_images_left->setText(QString());
        label_6->setText(QApplication::translate("InfoDialog", "Space Total", 0, QApplication::UnicodeUTF8));
        lb_space_total->setText(QString());
        label_7->setText(QApplication::translate("InfoDialog", "Space Left", 0, QApplication::UnicodeUTF8));
        lb_space_left->setText(QString());
        lb_capture_image->setText(QApplication::translate("InfoDialog", "Capture Image", 0, QApplication::UnicodeUTF8));
        pb_capture_image->setText(QApplication::translate("InfoDialog", "Try", 0, QApplication::UnicodeUTF8));
        lb_capture_preview->setText(QApplication::translate("InfoDialog", "Capture Preview", 0, QApplication::UnicodeUTF8));
        pb_capture_preview->setText(QApplication::translate("InfoDialog", "Try", 0, QApplication::UnicodeUTF8));
        pb_rescan->setText(QApplication::translate("InfoDialog", "Detect Camera", 0, QApplication::UnicodeUTF8));
        pb_close->setText(QApplication::translate("InfoDialog", "Quit", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("InfoDialog", "Logging", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InfoDialog: public Ui_InfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFODIALOG_H
