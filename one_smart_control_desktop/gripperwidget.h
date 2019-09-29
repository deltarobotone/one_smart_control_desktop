#ifndef GRIPPERWIDGET_H
#define GRIPPERWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

#include "easyprotocol.h"
#include "smartcontroldata.h"

namespace OneSmartControl
{

class GripperWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GripperWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent = nullptr);

private:
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;

    QGridLayout *basicLayout;
    QHBoxLayout *buttonRowLayout;

    QWidget *buttonRow;
    QPushButton *openButton;
    QPushButton *closeButton;
    QPushButton *toChartButton;

    void createLayout();

signals:
    void dataChanged();
    void toChart();

private slots:
    void closeGripper();
    void openGripper();
    void toChartButtonHandle();
};

} // OneSmartControl

#endif // GRIPPERWIDGET_H
