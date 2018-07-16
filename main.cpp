#include <QtGui/QApplication>
#include "qtMidi.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    qtMidi qtmidi;
    qtmidi.show();
    return app.exec();
}
