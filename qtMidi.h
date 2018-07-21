#ifndef qtMidi_H
#define qtMidi_H

#include <QProcess>
#include <QtGui/QMainWindow>
#include <QBoxLayout>
#include <QListWidget>
#include <QtGui/QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QLineEdit>

class qtMidi : public QMainWindow
{
    Q_OBJECT

public:
    qtMidi();
    virtual ~qtMidi();
    void setString(QString string);
    void setDevices(QStringList list);
private:
    QTableView *devicesListWidget;
    QStandardItemModel *devicesListModel;
    QPushButton *connectSynthButton;
    QMenuBar *menuBar;
    QLabel *label;
    QPushButton *selectFile;
    QPushButton *startPlaying;
    QPushButton *stopPlaying;
    QLineEdit *fileNameEdit;
    QProcess *qprocessSynth;
    QProcess *qprocessPlay;
    
    QString midiFileName;
    
private slots:
    void pickFile();
    void play();
    void finished();
    void stop();
    void connectSynth();
    void synthReady();
public slots:
    void reloadDevices();
    
};

#endif // qtMidi_H
