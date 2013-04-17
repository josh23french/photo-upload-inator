#include <QApplication>

#include "tetherwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TetherWindow tw;
    tw.show();
    app.connect(&tw, SIGNAL(imageSaved( const char * )), &tw, SLOT(displayThumbForTethered( const char * )));
    return app.exec();
}
