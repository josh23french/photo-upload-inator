/********************************************************************************
** Form generated from reading UI file 'tetherwindow.ui'
**
** Created: Sun Apr 14 00:27:30 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TETHERWINDOW_H
#define UI_TETHERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TetherWindow
{
public:
    QAction *actionQuit;
    QAction *actionInfo;
    QAction *actionDetect_Camer;
    QAction *actionLog;
    QAction *actionLogin;
    QAction *actionSign_in;
    QAction *actionCapture;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *familyGrp;
    QVBoxLayout *verticalLayout;
    QLineEdit *searchbox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *preview;
    QListWidget *thumbList;
    QPlainTextEdit *log;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuCamera;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TetherWindow)
    {
        if (TetherWindow->objectName().isEmpty())
            TetherWindow->setObjectName(QString::fromUtf8("TetherWindow"));
        TetherWindow->setWindowModality(Qt::NonModal);
        TetherWindow->resize(583, 560);
        TetherWindow->setAcceptDrops(false);
        TetherWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionQuit = new QAction(TetherWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("application-exit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionQuit->setIcon(icon);
        actionQuit->setShortcutContext(Qt::ApplicationShortcut);
        actionQuit->setMenuRole(QAction::QuitRole);
        actionQuit->setIconVisibleInMenu(true);
        actionInfo = new QAction(TetherWindow);
        actionInfo->setObjectName(QString::fromUtf8("actionInfo"));
        actionDetect_Camer = new QAction(TetherWindow);
        actionDetect_Camer->setObjectName(QString::fromUtf8("actionDetect_Camer"));
        actionLog = new QAction(TetherWindow);
        actionLog->setObjectName(QString::fromUtf8("actionLog"));
        actionLogin = new QAction(TetherWindow);
        actionLogin->setObjectName(QString::fromUtf8("actionLogin"));
        actionSign_in = new QAction(TetherWindow);
        actionSign_in->setObjectName(QString::fromUtf8("actionSign_in"));
        actionSign_in->setIconVisibleInMenu(false);
        actionCapture = new QAction(TetherWindow);
        actionCapture->setObjectName(QString::fromUtf8("actionCapture"));
        centralwidget = new QWidget(TetherWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        familyGrp = new QGroupBox(centralwidget);
        familyGrp->setObjectName(QString::fromUtf8("familyGrp"));
        verticalLayout = new QVBoxLayout(familyGrp);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        searchbox = new QLineEdit(familyGrp);
        searchbox->setObjectName(QString::fromUtf8("searchbox"));

        verticalLayout->addWidget(searchbox);


        verticalLayout_2->addWidget(familyGrp);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(200);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        preview = new QLabel(widget);
        preview->setObjectName(QString::fromUtf8("preview"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(preview->sizePolicy().hasHeightForWidth());
        preview->setSizePolicy(sizePolicy1);
        preview->setScaledContents(false);

        horizontalLayout->addWidget(preview, 0, Qt::AlignLeft|Qt::AlignTop);

        thumbList = new QListWidget(widget);
        thumbList->setObjectName(QString::fromUtf8("thumbList"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(200);
        sizePolicy2.setHeightForWidth(thumbList->sizePolicy().hasHeightForWidth());
        thumbList->setSizePolicy(sizePolicy2);
        thumbList->setMinimumSize(QSize(50, 0));
        thumbList->setMouseTracking(false);

        horizontalLayout->addWidget(thumbList);

        horizontalLayout->setStretch(0, 1);

        verticalLayout_2->addWidget(widget);

        log = new QPlainTextEdit(centralwidget);
        log->setObjectName(QString::fromUtf8("log"));

        verticalLayout_2->addWidget(log);

        TetherWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TetherWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 583, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuCamera = new QMenu(menubar);
        menuCamera->setObjectName(QString::fromUtf8("menuCamera"));
        TetherWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(TetherWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TetherWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuCamera->menuAction());
        menuFile->addAction(actionSign_in);
        menuFile->addAction(actionQuit);
        menuCamera->addAction(actionInfo);
        menuCamera->addAction(actionDetect_Camer);
        menuCamera->addAction(actionCapture);

        retranslateUi(TetherWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), TetherWindow, SLOT(close()));
        QObject::connect(actionInfo, SIGNAL(triggered()), TetherWindow, SLOT(raise()));

        QMetaObject::connectSlotsByName(TetherWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TetherWindow)
    {
        TetherWindow->setWindowTitle(QApplication::translate("TetherWindow", "LBC Directory Tether", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("TetherWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("TetherWindow", "Ctrl+Shift+Q", 0, QApplication::UnicodeUTF8));
        actionInfo->setText(QApplication::translate("TetherWindow", "Information", 0, QApplication::UnicodeUTF8));
        actionDetect_Camer->setText(QApplication::translate("TetherWindow", "Detect Camera", 0, QApplication::UnicodeUTF8));
        actionLog->setText(QApplication::translate("TetherWindow", "Event Log", 0, QApplication::UnicodeUTF8));
        actionLogin->setText(QApplication::translate("TetherWindow", "Login", 0, QApplication::UnicodeUTF8));
        actionSign_in->setText(QApplication::translate("TetherWindow", "Sign in...", 0, QApplication::UnicodeUTF8));
        actionCapture->setText(QApplication::translate("TetherWindow", "Capture", 0, QApplication::UnicodeUTF8));
        familyGrp->setTitle(QApplication::translate("TetherWindow", "Family", 0, QApplication::UnicodeUTF8));
        preview->setText(QString());
        menuFile->setTitle(QApplication::translate("TetherWindow", "File", 0, QApplication::UnicodeUTF8));
        menuCamera->setTitle(QApplication::translate("TetherWindow", "Camera", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TetherWindow: public Ui_TetherWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TETHERWINDOW_H
