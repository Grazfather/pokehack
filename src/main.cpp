//------------------------------------------------------
// main.cpp
// 
// Open a window for the barebones application
//------------------------------------------------------

#include <qapplication.h>
#include "window.h"
#include "SaveParser.h"

const char *filename = "../../Pokemon - Fire Red # GBA2"; // Default file name for now

// Main program to start up gui app
int main( int argc, char **argv )
{
    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication app(argc,argv);			

    Window w;
    w.resize(WIN_W, WIN_H);

    w.show();
	SaveParser::Instance()->load(filename);

    return app.exec();
}
