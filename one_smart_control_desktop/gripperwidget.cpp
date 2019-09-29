#include "gripperwidget.h"

OneSmartControl::GripperWidget::GripperWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent):
    QWidget(parent),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);
    buttonRowLayout = new QHBoxLayout;

    buttonRow = new QWidget;
    openButton = new QPushButton;
    closeButton = new QPushButton;
    toChartButton = new QPushButton;

    createLayout();
}

void OneSmartControl::GripperWidget::createLayout()
{
    setStyleSheet("background-color:white;");

    toChartButton->setIcon(QIcon(":/images/icons/next.png"));
    toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    toChartButton->setIconSize(QSize(35, 35));
    connect(toChartButton, SIGNAL(released()),this,SLOT(toChartButtonHandle()));

    QFont font("Arial Rounded MT Bold", 12);

    int size = 30;

    openButton->setText("open");
    openButton->setFont(font);
    openButton->setMinimumSize(size*4,size);
    openButton->setMaximumSize(size*4,size);
    openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
    connect(openButton, SIGNAL(released()),this,SLOT(openGripper()));

    closeButton->setText("close");
    closeButton->setFont(font);
    closeButton->setMinimumSize(size*4,size);
    closeButton->setMaximumSize(size*4,size);
    closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
    connect(closeButton, SIGNAL(released()),this,SLOT(closeGripper()));

    buttonRowLayout->addWidget(openButton);
    buttonRowLayout->addWidget(closeButton);
    buttonRow->setLayout(buttonRowLayout);

    basicLayout->addWidget(toChartButton,0,1);
    basicLayout->addWidget(buttonRow,0,0,1,1);

    setLayout(basicLayout);
}

void OneSmartControl::GripperWidget::openGripper()
{
    openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
    closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
    robot.gripper.open();
    controlData.gripperStatus = false;
    emit dataChanged();
}

void OneSmartControl::GripperWidget::closeGripper()
{
    openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
    closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
    robot.gripper.close();
    controlData.gripperStatus = true;
    emit dataChanged();
}

void OneSmartControl::GripperWidget::toChartButtonHandle()
{
    controlData.dataid = ID::gripper;
    emit toChart();
}
