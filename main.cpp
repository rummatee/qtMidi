#include <QtGui/QApplication>
#include <QTextCodec>
#include "qtMidi.h"



int main(int argc, char** argv)
{

    QApplication app(argc, argv);
    qtMidi qtmidi;
    QProcess *qprocessGetDeviceList = new QProcess();
    qprocessGetDeviceList->start("aplaymidi -l");
    qprocessGetDeviceList->waitForFinished();
    QString output(qprocessGetDeviceList->readAllStandardOutput());
    QStringList devicesList = output.split("\n");
    qtmidi.setDevices(devicesList);
    qtmidi.show();
    return app.exec();
}
