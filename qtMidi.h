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
    QMenuBar *menuBar;
    QLabel *label;
    QPushButton *selectFile;
    QPushButton *startPlaying;
    
    QString midiFileName;
    
private slots:
    void pickFile();
    void play();
    
};

#endif // qtMidi_H
