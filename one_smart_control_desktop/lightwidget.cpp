#include "lightwidget.h"

OneSmartControl::LightWidget::LightWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent):
    QWidget(parent),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);

    buttonRowLayout = new QHBoxLayout;

    buttonRow = new QWidget;

    redButton = new QPushButton;
    greenButton = new QPushButton;
    blueButton = new QPushButton;
    cyanButton = new QPushButton;
    yellowButton = new QPushButton;
    magentaButton = new QPushButton;
    whiteButton = new QPushButton;
    offButton = new QPushButton;

    iLabel = new QLabel;
    iValue = new QLabel;
    iSlider = new QSlider(Qt::Horizontal);

    toChartButton = new QPushButton;

    createLayout();
}

void OneSmartControl::LightWidget::createLayout()
{
    setStyleSheet("background-color:white;");

    toChartButton->setIcon(QIcon(":/images/icons/next.png"));
    toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    toChartButton->setIconSize(QSize(35, 35));
    connect(toChartButton, SIGNAL(released()),this,SLOT(toChartButtonHandle()));

    int size = 30;

    redButton->setMinimumSize(size,size);
    redButton->setMaximumSize(size,size);
    redButton->setStyleSheet("QPushButton{ background-color: rgb(200, 40, 40); border-radius: 10px; border: 1px solid rgb(200, 40, 40);}");
    connect(redButton, SIGNAL(released()),this,SLOT(setColourRed()));

    greenButton->setMinimumSize(size,size);
    greenButton->setMaximumSize(size,size);
    greenButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 20); border-radius: 10px; border: 1px solid rgb(20, 200, 20);}");
    connect(greenButton, SIGNAL(released()),this,SLOT(setColourGreen()));

    blueButton->setMinimumSize(size,size);
    blueButton->setMaximumSize(size,size);
    blueButton->setStyleSheet("QPushButton{ background-color: rgb(20, 20, 200); border-radius: 10px; border: 1px solid rgb(20, 20, 200);}");
    connect(blueButton, SIGNAL(released()),this,SLOT(setColourBlue()));

    whiteButton->setMinimumSize(size,size);
    whiteButton->setMaximumSize(size,size);
    whiteButton->setStyleSheet("QPushButton{ background-color: rgb(250, 250, 250); border-radius: 10px; border: 1px solid rgb(200, 200, 200);}");
    connect(whiteButton, SIGNAL(released()),this,SLOT(setColourWhite()));

    cyanButton->setMinimumSize(size,size);
    cyanButton->setMaximumSize(size,size);
    cyanButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 200); border-radius: 10px; border: 1px solid rgb(20, 200, 200);}");
    connect(cyanButton, SIGNAL(released()),this,SLOT(setColourCyan()));

    yellowButton->setMinimumSize(size,size);
    yellowButton->setMaximumSize(size,size);
    yellowButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 20); border-radius: 10px; border: 1px solid rgb(200, 200, 20);}");
    connect(yellowButton, SIGNAL(released()),this,SLOT(setColourYellow()));

    magentaButton->setMinimumSize(size,size);
    magentaButton->setMaximumSize(size,size);
    magentaButton->setStyleSheet("QPushButton{ background-color: rgb(200, 20, 200); border-radius: 10px; border: 1px solid rgb(200, 20, 200);}");
    connect(magentaButton, SIGNAL(released()),this,SLOT(setColourMagenta()));

    offButton->setMinimumSize(size,size);
    offButton->setMaximumSize(size,size);
    offButton->setStyleSheet("QPushButton{ background-color: rgb(200,200,200); border-radius: 10px; border: 1px solid rgb(200, 200, 200);}");
    connect(offButton, SIGNAL(released()),this,SLOT(setLightOff()));

    buttonRowLayout->addWidget(redButton);
    buttonRowLayout->addWidget(greenButton);
    buttonRowLayout->addWidget(blueButton);
    buttonRowLayout->addWidget(cyanButton);
    buttonRowLayout->addWidget(yellowButton);
    buttonRowLayout->addWidget(magentaButton);
    buttonRowLayout->addWidget(whiteButton);
    buttonRowLayout->addWidget(offButton);

    QFont font("Arial Rounded MT Bold", 14);
    iLabel->setText("- Intensity +");
    iLabel->setAlignment(Qt::AlignCenter);
    iLabel->setFont(font);
    iValue->setAlignment(Qt::AlignCenter);
    iValue->setFont(font);
    iSlider->setMaximum(100);
    iSlider->setMinimum(10);
    iSlider->setValue(55);
    connect(iSlider, SIGNAL(valueChanged(int)),this, SLOT(iSliderValueChanged(int)));
    connect(iSlider, SIGNAL(sliderReleased()),this, SLOT(iSliderReleased()));
    iSlider->setStyleSheet("QSlider::sub-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::add-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::groove:Horizontal { background: transparent; height:5px; }"
                           "QSlider::handle:Horizontal { width:5px; height:10px; background: rgb(30, 144, 255); border-radius: 7.49px; border: 5px solid rgb(30, 144, 255); margin: -5px 0px -5px 0px; }");

    basicLayout->addWidget(iLabel,0,0,1,2);
    basicLayout->addWidget(toChartButton,0,1,1,1,Qt::AlignRight);
    basicLayout->addWidget(iValue,1,0,1,2);
    basicLayout->addWidget(iSlider,2,0,1,2);

    buttonRow->setLayout(buttonRowLayout);
    basicLayout->addWidget(buttonRow,3,0,1,2);

    setLayout(basicLayout);

    controlData.intensity  = int(iSlider->value());
    QString text = QString::number(iSlider->value()) + QString(" %");
    iValue->setText(text);

    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourRed()
{
    robot.light.setColour(Colour::red,controlData.intensity);
    controlData.colour = Colour::red;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourGreen()
{
    robot.light.setColour(Colour::green,controlData.intensity);
    controlData.colour = Colour::green;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourBlue()
{
    robot.light.setColour(Colour::blue,controlData.intensity);
    controlData.colour = Colour::blue;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourCyan()
{
    robot.light.setColour(Colour::cyan,controlData.intensity);
    controlData.colour = Colour::cyan;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourYellow()
{
    robot.light.setColour(Colour::yellow,controlData.intensity);
    controlData.colour = Colour::yellow;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourMagenta()
{
    robot.light.setColour(Colour::magenta,controlData.intensity);
    controlData.colour = Colour::magenta;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourWhite()
{
    robot.light.setColour(Colour::white,controlData.intensity);
    controlData.colour = Colour::white;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setLightOff()
{
    robot.light.off();
    controlData.colour = Protocol::lightoff;
    emit dataChanged();
}

void OneSmartControl::LightWidget::iSliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" %");
    iValue->setText(text);
    controlData.intensity  = value;
    emit dataChanged();
}

void OneSmartControl::LightWidget::iSliderReleased()
{
    robot.light.setColour(controlData.colour,controlData.intensity);
}

void OneSmartControl::LightWidget::toChartButtonHandle()
{
    controlData.dataid = ID::light;
    emit toChart();
}
