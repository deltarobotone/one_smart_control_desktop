#include "timewidget.h"

OneSmartControl::TimeWidget::TimeWidget(OneSmartControl::SmartControlData &smartControlData, QWidget *parent):
    QWidget(parent),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);

    tLabel = new QLabel;
    tSlider = new QSlider(Qt::Horizontal);

    toChartButton = new QPushButton;

    createLayout();
}

void OneSmartControl::TimeWidget::createLayout()
{
    setStyleSheet("background-color:white;");

    toChartButton->setIcon(QIcon(":/images/icons/next.png"));
    toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    toChartButton->setIconSize(QSize(35, 35));
    connect(toChartButton, SIGNAL(released()),this,SLOT(toChartButtonHandle()));

    QFont font("Arial Rounded MT Bold", 14);

    tLabel->setAlignment(Qt::AlignCenter);
    tLabel->setFont(font);
    tSlider->setMaximum(1000);
    tSlider->setMinimum(100);
    tSlider->setValue(500);
    connect(tSlider, SIGNAL(valueChanged(int)),this, SLOT(tSliderValueChanged(int)));
    tSlider->setStyleSheet("QSlider::sub-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::add-page:Horizontal { background: rgb(180, 180, 180); }"
                           "QSlider::groove:Horizontal { background: transparent; height:5px; }"
                           "QSlider::handle:Horizontal { width:5px; height:10px; background: rgb(30, 144, 255); border-radius: 7.49px; border: 5px solid rgb(30, 144, 255); margin: -5px 0px -5px 0px; }");

    basicLayout->addWidget(tLabel,0,0,1,2);
    basicLayout->addWidget(toChartButton,0,1,1,1,Qt::AlignRight);
    basicLayout->addWidget(tSlider,2,0,1,2);

    setLayout(basicLayout);

    controlData.waitFortime  = uint(tSlider->value());
    QString text = "Wait for " +  QString::number(tSlider->value()) + QString(" ms");
    tLabel->setText(text);
    emit dataChanged();

}

void OneSmartControl::TimeWidget::tSliderValueChanged(int value)
{
    QString text = "Wait for " +  QString::number(value) + QString(" ms");
    tLabel->setText(text);
    controlData.waitFortime  = uint(value);
    emit dataChanged();
}

void OneSmartControl::TimeWidget::toChartButtonHandle()
{
    controlData.dataid = ID::waitFor;
    emit toChart();
}
