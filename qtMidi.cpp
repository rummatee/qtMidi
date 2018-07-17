#include "qtMidi.h"


#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QDebug>


qtMidi::qtMidi()
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    label = new QLabel( );
    label->setText( "Hello World!" );
    mainLayout->addWidget(label);
    
    devicesListWidget = new QTableView();
    devicesListModel = new QStandardItemModel;
    devicesListWidget->setModel(devicesListModel);
    devicesListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    devicesListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    devicesListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    
    menuBar = new QMenuBar;
    
    QAction* action = new QAction(this);
    action->setText( "Quit" );
    
    connect(action, SIGNAL(triggered()), SLOT(close()) );
    menuBar->addMenu( "File" )->addAction( action );
    
    setMenuBar(menuBar);
    
    selectFile = new QPushButton(tr("Midi Datei auswählen"));
    connect(selectFile, SIGNAL(released()), SLOT(pickFile()));
    mainLayout->addWidget(devicesListWidget);
    mainLayout->addWidget(selectFile);

    startPlaying = new QPushButton(tr("Abspielen"));
    connect(startPlaying, SIGNAL(released()), SLOT(play()));
    mainLayout->addWidget(startPlaying);
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
}

void qtMidi::pickFile()
{
    midiFileName = QFileDialog::getOpenFileName(this, tr("Öffne Midi Datei"), "", tr("Midi (*.mid)"));
    label->setText(midiFileName);
}

void qtMidi::play()
{
    QProcess *qprocessPlay = new QProcess();
    QString deviceID = devicesListModel->itemFromIndex(devicesListWidget->selectionModel()->selectedRows().first())->text();
    qprocessPlay->start("aplaymidi -p "+deviceID+" "+midiFileName);
    
}



#include "qtMidi.moc"
