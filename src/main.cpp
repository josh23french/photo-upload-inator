#include <QApplication>

#include "tetherwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Directory Uploader");
    QCoreApplication::setOrganizationDomain("lbcde.org");
    QCoreApplication::setOrganizationName("LBC");

    TetherWindow tw;
    tw.show();
    app.connect(&tw, SIGNAL(imageSaved(QString)), &tw, SLOT(displayThumbForTethered( QString )));
    return app.exec();
}
