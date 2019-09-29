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

private:
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;
    OneSmartControl::TimeWidget *timeWidget;

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

public slots:
    void addData();

private slots:
    void loadButtonHandle();
    void saveButtonHandle();
    void addButtonHandle();
    void deleteButtonHandle();
    void playButtonHandle();
    void upButtonHandle();
    void downButtonHandle();
};

} // OneSmartControl

#endif // FLOWCHARTWIDGET_H
