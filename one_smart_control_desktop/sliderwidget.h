#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include "easyprotocol.h"
#include "smartcontroldata.h"
#include "workingspace.h"

namespace OneSmartControl
{

class SliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent = nullptr);

private:
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;
    OneSmartControl::WorkingSpace workingSpace;

    QGridLayout *basicLayout;

    QLabel *xLabel;
    QLabel *yLabel;
    QLabel *zLabel;
    QLabel *vLabel;

    QLabel *xValue;
    QLabel *yValue;
    QLabel *zValue;
    QLabel *vValue;

    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *vSlider;

    QPushButton *toChartButton;

    void createLayout();

signals:
    void dataChanged();
    void toChart();

private slots:
    void xSliderValueChanged(int value);
    void ySliderValueChanged(int value);
    void zSliderValueChanged(int value);
    void vSliderValueChanged(int value);

    void xSliderReleased();
    void ySliderReleased();
    void zSliderReleased();
    void vSliderReleased();

    void toChartButtonHandle();
};

} // OneSmartControl

#endif // SLIDERWIDGET_H
