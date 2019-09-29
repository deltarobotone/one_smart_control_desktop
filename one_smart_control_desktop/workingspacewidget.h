#ifndef WORKINGSPACEWIDGET_H
#define WORKINGSPACEWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPainter>

#include "easyprotocol.h"
#include "smartcontroldata.h"

namespace OneSmartControl
{

class WorkingSpaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorkingSpaceWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

private:
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;

    QVBoxLayout *basicLayout;

    QWidget *paintArea;

    void createLayout();
};

} // OneSmartControl

#endif // WORKINGSPACEWIDGET_H
