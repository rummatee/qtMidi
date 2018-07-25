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
    QPushButton *selectFileRecord;
    QPushButton *startPlaying;
    QPushButton *stopPlaying;
    QPushButton *saveFile;
    QPushButton *startRecordingButton;
    QPushButton *stopRecordingButton;
    QLineEdit *fileNameEdit;
    QLineEdit *fileNameEditRecord;
    QProcess *qprocessSynth;
    QProcess *qprocessPlay;
    QProcess *qprocessRecord;
    QWidget *playPage;
    QWidget *recordPage;
    QTabWidget *tabs;
    
    QString midiFileName;
    QString midiFileNameRecord;
    QLabel* labelRecord;
    
private slots:
    void pickFile();
    void pickFileRecord();
    void play();
    void record();
    void finished();
    void stop();
    void stopRecording();
    void connectSynth();
    void synthReady();
public slots:
    void reloadDevices();
    
};

#endif // qtMidi_H
