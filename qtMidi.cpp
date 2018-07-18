#include "qtMidi.h"


#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QDebug>
#include <QHeaderView>
#include <QTextCodec>


qtMidi::qtMidi()
{
  
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  
    menuBar = new QMenuBar;
    
    QAction* action = new QAction(this);
    action->setText( "Quit" );
    
    connect(action, SIGNAL(triggered()), SLOT(close()) );
    menuBar->addMenu( "File" )->addAction( action );
    
    setMenuBar(menuBar);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    label = new QLabel( );
    label->setText( "Hello World!" );
    mainLayout->addWidget(label);
    
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
    
    connectSynth = new QPushButton(tr("Synthesyser verbinden"));
    
    devicesLayout->addWidget(connectSynth,1,0);
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
    QHBoxLayout *playLayout = new QHBoxLayout();


    startPlaying = new QPushButton(tr("Abspielen"));
    connect(startPlaying, SIGNAL(released()), SLOT(play()));
    playLayout->addWidget(startPlaying);
    
    stopPlaying = new QPushButton(tr("Stop"));
    playLayout->addWidget(stopPlaying);
    
    
    playGroup->setLayout(playLayout);
    
    
    mainLayout->addWidget(deviceConfigurationGroup);
    mainLayout->addWidget(fileGroup);
    mainLayout->addWidget(playGroup);
    
    QFrame *mainGroup = new QFrame;
    mainGroup->setLayout(mainLayout);
    setCentralWidget( mainGroup );
}

qtMidi::~qtMidi()
{}

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
    midiFileName = QFileDialog::getOpenFileName(this, tr("Öffne Midi Datei"), "", tr("Midi (*.mid)"));
    if (midiFileName != NULL) {
      label->setText(midiFileName);
    }
}

void qtMidi::play()
{
    QProcess *qprocessPlay = new QProcess();
    QString deviceID = devicesListModel->itemFromIndex(devicesListWidget->selectionModel()->selectedRows().first())->text();
    qprocessPlay->start("aplaymidi -p "+deviceID+" "+midiFileName);
    
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




#include "qtMidi.moc"
