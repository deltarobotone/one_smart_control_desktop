#ifndef FLOWCHARTWIDGET_H
#define FLOWCHARTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QDialog>
#include <QFileDialog>
#include <QTextStream>

#include "config.h"
#include "easyprotocol.h"
#include "smartcontroldata.h"
#include "timewidget.h"

namespace OneSmartControl
{

class FlowChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowChartWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent = nullptr);
    OneSmartControl::TimeWidget *timeWidget;
private:
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;

    QVBoxLayout *basicLayout;
    QVBoxLayout *addDialogLayout;
    QHBoxLayout *buttonRowLayout;

    QWidget *buttonRow;

    QListView *controlChartView;
    QStringList *controlDataList;
    QStringListModel *controlDataListModel;

    QList<OneSmartControl::SmartControlData> controlDataStore;

    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *playButton;
    QPushButton *upButton;
    QPushButton *downButton;

    void createLayout();
    void activatePlayList();

    QDialog *addDialog;

    bool running = false;
    int selectedRow = 0;

public slots:
    void addData();
    void freeChannel();
    void dataTransmitted();

private slots:
    void loadButtonHandle();
    void saveButtonHandle();
    void addButtonHandle();
    void deleteButtonHandle();
    void playButtonHandle();
    void upButtonHandle();
    void downButtonHandle();

signals:
    void playlistOn();
    void playlistOff();
};

} // OneSmartControl

#endif // FLOWCHARTWIDGET_H
