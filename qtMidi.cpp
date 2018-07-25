#include "qtMidi.h"


#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QDebug>
#include <QHeaderView>
#include <QTextCodec>
#include <iostream>
#include <unistd.h>



qtMidi::qtMidi()
{
  
    qprocessPlay = NULL;
  
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  
    menuBar = new QMenuBar;
    
    QAction* action = new QAction(this);
    action->setText( "Quit" );
    
    connect(action, SIGNAL(triggered()), SLOT(close()) );
    menuBar->addMenu( "File" )->addAction( action );
    
    setMenuBar(menuBar);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    
    QGroupBox *deviceConfigurationGroup= new QGroupBox(tr("konfiguriere Geräte"));
    QGridLayout *devicesLayout = new QGridLayout();
    
    devicesListWidget = new QTableView();
    devicesListModel = new QStandardItemModel;
    devicesListWidget->setModel(devicesListModel);
    devicesListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    devicesListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    devicesListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    devicesListWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    devicesLayout->addWidget(devicesListWidget);
    
    connectSynthButton = new QPushButton(tr("Synthesyser verbinden"));
    connect(connectSynthButton, SIGNAL(released()), SLOT(connectSynth()));
    devicesLayout->addWidget(connectSynthButton,1,0);
    deviceConfigurationGroup->setLayout(devicesLayout);
    
    
    
    QGroupBox *fileGroup= new QGroupBox(tr("wähle Datei"));
    QGridLayout *fileLayout = new QGridLayout();
    
    fileNameEdit = new QLineEdit;
    
    selectFile = new QPushButton(tr("Midi Datei auswählen"));
    connect(selectFile, SIGNAL(released()), SLOT(pickFile()));
    
    fileLayout->addWidget(fileNameEdit,0,0);
    fileLayout->addWidget(selectFile,0,1);
    
    fileGroup->setLayout(fileLayout);
    
    
    QGroupBox *playGroup= new QGroupBox(tr("Abspielen"));
    QGridLayout *playLayout = new QGridLayout();
    
    label = new QLabel( );
    label->setText( tr("Bitte Gerät und Datei auswählen") );
    playLayout->addWidget(label,0,0);


    startPlaying = new QPushButton(tr("Abspielen"));
    startPlaying->setEnabled(false);
    connect(startPlaying, SIGNAL(released()), SLOT(play()));
    playLayout->addWidget(startPlaying,1,0);
    
    stopPlaying = new QPushButton(tr("Stop"));
    stopPlaying->setEnabled(false);
    connect(stopPlaying, SIGNAL(released()), SLOT(stop()));
    playLayout->addWidget(stopPlaying,1,1);
    
    
    playGroup->setLayout(playLayout);
    
    
    mainLayout->addWidget(deviceConfigurationGroup);
    mainLayout->addWidget(fileGroup);
    mainLayout->addWidget(playGroup);
    
    QFrame *mainGroup = new QFrame;
    mainGroup->setLayout(mainLayout);
    setCentralWidget( mainGroup );
}

qtMidi::~qtMidi()
{
    if (qprocessPlay != NULL) {
      qprocessPlay->kill();
    }
    if (qprocessSynth != NULL) {
      qprocessSynth->kill();
    }
}

void qtMidi::setString(QString string)
{
    label->setText( string );
}

void qtMidi::setDevices(QStringList list)
{
    QString header = list.first();
    list.removeFirst();
    devicesListModel->setHorizontalHeaderLabels(header.split("  ", QString::SkipEmptyParts));
    for ( QStringList::iterator it = list.begin(); it != list.end();++it  ) {
      QList<QStandardItem*> item;
      QStringList parts = ((*it).split("  ", QString::SkipEmptyParts));
      for ( QStringList::iterator part = parts.begin(); part != parts.end();++part  ) {
	item.append(new QStandardItem(*part));
      }
      devicesListModel->appendRow(item);
    }
    devicesListWidget->selectRow(0);
}

void qtMidi::pickFile()
{
    midiFileName = QFileDialog::getOpenFileName(this, tr("Öffne Midi Datei"), QDir::homePath(), tr("Midi (*.mid)"));
    if (midiFileName != NULL) {
      fileNameEdit->setText(midiFileName);
      startPlaying->setEnabled(true);
      label->setText("bereit");
    }
}

void qtMidi::play()
{
    if (qprocessPlay==NULL) {
      qprocessPlay = new QProcess();
      qprocessPlay->setProcessChannelMode(QProcess::MergedChannels);
      QString deviceID = devicesListModel->itemFromIndex(devicesListWidget->selectionModel()->selectedRows().first())->text();
      QStringList args = QStringList()<<"-p"<<deviceID <<midiFileName;
      //midiFileName.replace(" ","\\ ");
      std::cout << ("aplaymidi -p "+deviceID+" "+midiFileName).toStdString()<<std::endl;
      //qprocessPlay->start("aplaymidi -p "+deviceID,args);
      qprocessPlay->start("aplaymidi -p "+deviceID+" "+midiFileName);
      connect(qprocessPlay,SIGNAL(finished(int)),SLOT(finished()));
      label->setText("spiele ab");
      stopPlaying->setEnabled(true);
      startPlaying->setEnabled(false);
    }
    
}

void qtMidi::reloadDevices()
{
    QProcess *qprocessGetDeviceList = new QProcess();
    qprocessGetDeviceList->start("aplaymidi -l");
    qprocessGetDeviceList->waitForFinished();
    QString output(qprocessGetDeviceList->readAllStandardOutput());
    QStringList devicesList = output.split("\n");
    setDevices(devicesList);
}

void qtMidi::finished()
{
    if (qprocessPlay != NULL) {
      std::cout << QString(qprocessPlay->readAllStandardOutput()).toStdString()<<std::endl;
      qprocessPlay->deleteLater();
      qprocessPlay = NULL;
      startPlaying->setEnabled(true);
      stopPlaying->setEnabled(false);
      label->setText("beendet");
    }
}

void qtMidi::stop()
{
    if (qprocessPlay != NULL) {
      
      qprocessPlay->kill();
      qprocessPlay->deleteLater();
      qprocessPlay = NULL;
      startPlaying->setEnabled(true);
      stopPlaying->setEnabled(false);
      label->setText("abgebrochen");
    }
}

void qtMidi::connectSynth()
{
    qprocessSynth = new QProcess();
    //qprocessSynth->setProcessChannelMode(QProcess::ForwardedChannels);
    //qprocessSynth->setReadChannel(QProcess::StandardOutput);
    qprocessSynth->start("timidity -iA");
    //QString output(qprocessSynth->readAllStandardOutput());
    //std::cout << output.toStdString()<<std::endl;
    //connect(qprocessSynth,SIGNAL(readyReadStandardOutput()),SLOT(synthReady()));
    QProcess *qprocessGetDeviceList = new QProcess();
    usleep(500000);
    qprocessGetDeviceList->start("aplaymidi -l");
    std::cout << "aplaymidi -l"<<std::endl;
    qprocessGetDeviceList->waitForFinished();
    QString output(qprocessGetDeviceList->readAllStandardOutput());
    std::cout << output.toStdString()<<std::endl;
    QStringList devicesList = output.split("\n");
    QString port;
    for ( QStringList::iterator it = devicesList.begin(); it != devicesList.end();++it  ) {
      QList<QStandardItem*> item;
      QStringList parts = ((*it).split("  ", QString::SkipEmptyParts));
      if (parts.value(1) == "TiMidity") {
	port = parts.value(0);
	break;
      }
    }
    QProcess *qprocessConnect = new QProcess();
    qprocessConnect->setProcessChannelMode(QProcess::ForwardedChannels);
    QString deviceID = devicesListModel->itemFromIndex(devicesListWidget->selectionModel()->selectedRows().first())->text();
    std::cout << ("aconnect "+deviceID+" "+port).toStdString()<<std::endl;
    qprocessConnect->start("aconnect "+deviceID+" "+port);
    //qprocessSynth->waitForBytesWritten();

}


void qtMidi::synthReady()
{

}

#include "qtMidi.moc"
