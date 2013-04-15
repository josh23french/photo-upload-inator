#include <QApplication>

#include "infodialog.h"
#include "tetherwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //InfoDialog dialog;
    //dialog.show();
    TetherWindow tw;
    tw.show();
    app.connect(&tw, SIGNAL(imageSaved( const char * )), &tw, SLOT(displayThumbForTethered( const char * )));
    return app.exec();
}
