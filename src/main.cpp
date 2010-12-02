//------------------------------------------------------
// main.cpp
// 
// Open a window for the barebones application
//------------------------------------------------------

#include "window.h"
#include <qapplication.h>

// Main program to start up gui app
int main( int argc, char **argv )
{
    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication app(argc,argv);			

    Window w;
    w.resize(WIN_W, WIN_H);
   // app.setMainWidget( &w );

    w.show();

    return app.exec();
}
