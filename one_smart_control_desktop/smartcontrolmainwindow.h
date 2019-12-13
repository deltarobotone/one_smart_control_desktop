#ifndef SMARTCONTROLMAINWINDOW_H
#define SMARTCONTROLMAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QGroupBox>

#include "sliderwidget.h"
#include "workingspacewidget.h"
#include "flowchartwidget.h"
#include "lightwidget.h"
#include "gripperwidget.h"
#include "connectwidget.h"

#include "easyprotocol.h"
#include "smartcontroldata.h"

namespace Ui {
class SmartControlMainWindow;
}

class SmartControlMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartControlMainWindow(QWidget *parent = nullptr);
    ~SmartControlMainWindow();

private:
    EasyProtocol robot;
    OneSmartControl::SmartControlData smartControlData;

    Ui::SmartControlMainWindow *ui;

    QGroupBox *sliderGroupbox;
    QVBoxLayout *sliderLayout;
    OneSmartControl::SliderWidget *sliderWidget;

    QGroupBox *workingSpaceGroupbox;
    QVBoxLayout *workingSpaceLayout;
    OneSmartControl::WorkingSpaceWidget *workingSpaceWidget;

    QGroupBox *flowChartGroupbox;
    QVBoxLayout *flowChartLayout;
    OneSmartControl::FlowChartWidget *flowChartWidget;

    QGroupBox *lightGroupbox;
    QVBoxLayout *lightLayout;
    OneSmartControl::LightWidget *lightWidget;

    QGroupBox *gripperGroupbox;
    QVBoxLayout *gripperLayout;
    OneSmartControl::GripperWidget *gripperWidget;

    QGroupBox *connectGroupbox;
    QVBoxLayout *connectLayout;
    OneSmartControl::ConnectWidget *connectWidget;

    QGroupBox *infoGroupbox;
    QVBoxLayout *infoLayout;
    QLabel *infoLabel;

    QWidget *basicWidget;
    QHBoxLayout *basicLayout;

    QWidget *leftWidget;
    QVBoxLayout *leftLayout;

    QWidget *centerWidget;
    QVBoxLayout *centerLayout;

    QWidget *rightWidget;
    QVBoxLayout *rightLayout;

    void createLayout();

private slots:

    void showToChartMessage();
    void hideToChartMessage();
};

#endif // SMARTCONTROLMAINWINDOW_H
