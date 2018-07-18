#include <QtGui/QApplication>
#include <QTextCodec>
#include "qtMidi.h"



int main(int argc, char** argv)
{

    QApplication app(argc, argv);
    qtMidi qtmidi;
    qtmidi.reloadDevices();
    qtmidi.show();
    return app.exec();
}
