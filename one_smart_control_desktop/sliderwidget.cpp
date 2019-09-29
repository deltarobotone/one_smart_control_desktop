#include "sliderwidget.h"

OneSmartControl::SliderWidget::SliderWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent):
    QWidget(parent),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);
    
    xLabel = new QLabel;
    yLabel = new QLabel;
    zLabel = new QLabel;
    vLabel = new QLabel;
    
    xValue = new QLabel;
    yValue = new QLabel;
    zValue = new QLabel;
    vValue = new QLabel;
    
    xSlider = new QSlider(Qt::Horizontal);
    ySlider = new QSlider(Qt::Horizontal);
    zSlider = new QSlider(Qt::Horizontal);
    vSlider = new QSlider(Qt::Horizontal);
    
    toChartButton = new QPushButton;

    createLayout();

    workingSpace.setLevel(1, 70.0, 79.0, 25.0);
    workingSpace.setLevel(2, 80.0, 99.0, 45.0);
    workingSpace.setLevel(3, 100.0, 119.0, 37.5);
    workingSpace.setLevel(4, 120.0, 130.0, 15.0);
}

void OneSmartControl::SliderWidget::createLayout()
{
    setStyleSheet("background-color:white;");

    toChartButton->setIcon(QIcon(":/images/icons/next.png"));
    toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    toChartButton->setIconSize(QSize(35, 35));
    connect(toChartButton, SIGNAL(released()),this,SLOT(toChartButtonHandle()));

    QFont font("Arial Rounded MT Bold", 14);
    
    xLabel->setText("- X +");
    xLabel->setAlignment(Qt::AlignCenter);
    xLabel->setFont(font);
    xValue->setAlignment(Qt::AlignCenter);
    xValue->setFont(font);
    xSlider->setMaximum(45);
    xSlider->setMinimum(-45);
    xSlider->setValue(0);
    connect(xSlider, SIGNAL(valueChanged(int)),this, SLOT(xSliderValueChanged(int)));
    connect(xSlider, SIGNAL(sliderReleased()),this, SLOT(xSliderReleased()));
    xSlider->setStyleSheet("QSlider::sub-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::add-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::groove:Horizontal { background: transparent; height:5px; }"
                           "QSlider::handle:Horizontal { width:5px; height:10px; background: rgb(30, 144, 255); border-radius: 7.49px; border: 5px solid rgb(30, 144, 255); margin: -5px 0px -5px 0px; }");


    yLabel->setText("- Y +");
    yLabel->setAlignment(Qt::AlignCenter);
    yLabel->setFont(font);
    yValue->setAlignment(Qt::AlignCenter);
    yValue->setFont(font);
    ySlider->setMaximum(45);
    ySlider->setMinimum(-45);
    ySlider->setValue(0);
    connect(ySlider, SIGNAL(valueChanged(int)),this, SLOT(ySliderValueChanged(int)));
    connect(ySlider, SIGNAL(sliderReleased()),this, SLOT(ySliderReleased()));
    ySlider->setStyleSheet("QSlider::sub-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::add-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::groove:Horizontal { background: transparent; height:5px; }"
                           "QSlider::handle:Horizontal { width:5px; height:10px; background: rgb(30, 144, 255); border-radius: 7.49px; border: 5px solid rgb(30, 144, 255); margin: -5px 0px -5px 0px; }");
    
    
    zLabel->setText("- Z +");
    zLabel->setAlignment(Qt::AlignCenter);
    zLabel->setFont(font);
    zValue->setAlignment(Qt::AlignCenter);
    zValue->setFont(font);
    zSlider->setMaximum(130);
    zSlider->setMinimum(70);
    zSlider->setValue(100);
    connect(zSlider, SIGNAL(valueChanged(int)),this, SLOT(zSliderValueChanged(int)));
    connect(zSlider, SIGNAL(sliderReleased()),this, SLOT(zSliderReleased()));
    zSlider->setStyleSheet("QSlider::sub-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::add-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::groove:Horizontal { background: transparent; height:5px; }"
                           "QSlider::handle:Horizontal { width:5px; height:10px; background: rgb(30, 144, 255); border-radius: 7.49px; border: 5px solid rgb(30, 144, 255); margin: -5px 0px -5px 0px; }");
    

    vLabel->setText("- Speed +");
    vLabel->setAlignment(Qt::AlignCenter);
    vLabel->setFont(font);
    vValue->setAlignment(Qt::AlignCenter);
    vValue->setFont(font);
    vSlider->setMaximum(100);
    vSlider->setMinimum(10);
    vSlider->setValue(80);
    connect(vSlider, SIGNAL(valueChanged(int)),this, SLOT(vSliderValueChanged(int)));
    connect(vSlider, SIGNAL(sliderReleased()),this, SLOT(vSliderReleased()));
    vSlider->setStyleSheet("QSlider::sub-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::add-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::groove:Horizontal { background: transparent; height:5px; }"
                           "QSlider::handle:Horizontal { width:5px; height:10px; background: rgb(30, 144, 255); border-radius: 7.49px; border: 5px solid rgb(30, 144, 255); margin: -5px 0px -5px 0px; }");


    basicLayout->addWidget(xLabel,0,0,1,2);
    basicLayout->addWidget(toChartButton,0,1,1,1,Qt::AlignRight);
    basicLayout->addWidget(xValue,1,0,1,2);
    basicLayout->addWidget(xSlider,2,0,1,2);
    
    basicLayout->addWidget(yLabel,3,0,1,2);
    basicLayout->addWidget(yValue,4,0,1,2);
    basicLayout->addWidget(ySlider,5,0,1,2);
    
    basicLayout->addWidget(zLabel,6,0,1,2);
    basicLayout->addWidget(zValue,7,0,1,2);
    basicLayout->addWidget(zSlider,8,0,1,2);

    basicLayout->addWidget(vLabel,9,0,1,2);
    basicLayout->addWidget(vValue,10,0,1,2);
    basicLayout->addWidget(vSlider,11,0,1,2);

    setLayout(basicLayout);

    controlData.xPosition  = int(xSlider->value());
    QString text = QString::number(xSlider->value()) + QString(" mm");
    xValue->setText(text);

    controlData.yPosition  = int(ySlider->value());
    text = QString::number(ySlider->value()) + QString(" mm");
    yValue->setText(text);

    controlData.zPosition  = int(zSlider->value());
    text = QString::number(zSlider->value()) + QString(" mm");
    zValue->setText(text);

    controlData.velocity  = int(vSlider->value());
    text = QString::number(vSlider->value()) + QString(" %");
    vValue->setText(text);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::xSliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" mm");
    xValue->setText(text);
    controlData.xPosition = value;
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::ySliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" mm");
    yValue->setText(text);
    controlData.yPosition = value;
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::zSliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" mm");
    zValue->setText(text);
    controlData.zPosition = value;
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::vSliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" %");
    vValue->setText(text);
    controlData.velocity = value;
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::xSliderReleased()
{
    controlData.xPosition = xSlider->value();
    robot.move.ptp(controlData.xPosition,controlData.yPosition,controlData.zPosition,controlData.velocity);
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
}

void OneSmartControl::SliderWidget::ySliderReleased()
{
    controlData.yPosition = ySlider->value();
    robot.move.ptp(controlData.xPosition,controlData.yPosition,controlData.zPosition,controlData.velocity);
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
}

void OneSmartControl::SliderWidget::zSliderReleased()
{
    controlData.zPosition = zSlider->value();
    robot.move.ptp(controlData.xPosition,controlData.yPosition,controlData.zPosition,controlData.velocity);
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
}

void OneSmartControl::SliderWidget::vSliderReleased()
{
    controlData.velocity = vSlider->value();
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
}

void OneSmartControl::SliderWidget::toChartButtonHandle()
{
    controlData.dataid = ID::move;
    controlData.xPosition = xSlider->value();
    controlData.yPosition = ySlider->value();
    controlData.zPosition = zSlider->value();
    controlData.velocity = vSlider->value();
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit toChart();
}


