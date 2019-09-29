#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include "easyprotocol.h"
#include "smartcontroldata.h"

namespace OneSmartControl
{

class LightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LightWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent = nullptr);

private:
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;

    QGridLayout *basicLayout;
    QHBoxLayout *buttonRowLayout;

    QWidget *buttonRow;

    QLabel *iLabel;
    QLabel *iValue;
    QSlider *iSlider;

    QPushButton *redButton;
    QPushButton *greenButton;
    QPushButton *blueButton;
    QPushButton *cyanButton;
    QPushButton *yellowButton;
    QPushButton *magentaButton;
    QPushButton *whiteButton;
    QPushButton *offButton;

    QPushButton *toChartButton;

    float intensity = 0.0F;

    void createLayout();

signals:
    void dataChanged();
    void toChart();

private slots:
    void setColourRed();
    void setColourGreen();
    void setColourBlue();
    void setColourCyan();
    void setColourYellow();
    void setColourMagenta();
    void setColourWhite();
    void setLightOff();
    void iSliderValueChanged(int value);
    void iSliderReleased();
    void toChartButtonHandle();
};

} // OneSmartControl

#endif // LIGHTWIDGET_H
