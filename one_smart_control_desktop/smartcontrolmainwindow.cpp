#include "smartcontrolmainwindow.h"
#include "ui_smartcontrolmainwindow.h"

SmartControlMainWindow::SmartControlMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartControlMainWindow)
{
    ui->setupUi(this);
    setWindowTitle("One Smart Control");

    sliderGroupbox = new QGroupBox;
    sliderLayout = new QVBoxLayout;
    sliderWidget = new OneSmartControl::SliderWidget(robot,smartControlData);

    workingSpaceGroupbox = new QGroupBox;
    workingSpaceLayout = new QVBoxLayout;
    workingSpaceWidget = new OneSmartControl::WorkingSpaceWidget(robot,smartControlData);

    flowChartGroupbox = new QGroupBox;
    flowChartLayout = new QVBoxLayout;
    flowChartWidget = new OneSmartControl::FlowChartWidget(robot,smartControlData);

    lightGroupbox = new QGroupBox;
    lightLayout = new QVBoxLayout;
    lightWidget = new OneSmartControl::LightWidget(robot,smartControlData);

    gripperGroupbox = new QGroupBox;
    gripperLayout = new QVBoxLayout;
    gripperWidget = new OneSmartControl::GripperWidget(robot,smartControlData);

    connectGroupbox = new QGroupBox;
    connectLayout = new QVBoxLayout;
    connectWidget = new OneSmartControl::ConnectWidget(robot,smartControlData);

    basicWidget = new QWidget(this);
    basicLayout = new QHBoxLayout;

    leftWidget = new QWidget;
    leftLayout = new QVBoxLayout;

    centerWidget = new QWidget;
    centerLayout = new QVBoxLayout;

    rightWidget = new QWidget;
    rightLayout = new QVBoxLayout;
    createLayout();
}

SmartControlMainWindow::~SmartControlMainWindow()
{
    robot.stop();
    delete ui;
}

void SmartControlMainWindow::createLayout()
{
    setStyleSheet("background-color:white;");

    sliderGroupbox->setLayout(sliderLayout);
    sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
    sliderLayout->addWidget(sliderWidget);
    connect(sliderWidget,SIGNAL(dataChanged()),workingSpaceWidget,SLOT(update()));
    connect(sliderWidget,SIGNAL(toChart()),flowChartWidget,SLOT(addData()));

    lightGroupbox->setLayout(lightLayout);
    lightGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
    lightLayout->addWidget(lightWidget);
    connect(lightWidget,SIGNAL(dataChanged()),workingSpaceWidget,SLOT(update()));
    connect(lightWidget,SIGNAL(toChart()),flowChartWidget,SLOT(addData()));

    gripperGroupbox->setLayout(gripperLayout);
    gripperGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
    gripperLayout->addWidget(gripperWidget);
    connect(gripperWidget,SIGNAL(dataChanged()),workingSpaceWidget,SLOT(update()));
    connect(gripperWidget,SIGNAL(toChart()),flowChartWidget,SLOT(addData()));

    flowChartGroupbox->setLayout(flowChartLayout);
    flowChartGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
    flowChartLayout->addWidget(flowChartWidget);

    workingSpaceGroupbox->setLayout(workingSpaceLayout);
    workingSpaceGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
    workingSpaceLayout->addWidget(workingSpaceWidget);

    connectGroupbox->setLayout(connectLayout);
    connectGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
    connectLayout->addWidget(connectWidget);

    leftLayout->addWidget(sliderGroupbox);
    leftLayout->addWidget(lightGroupbox);
    leftLayout->addWidget(gripperGroupbox);

    centerLayout->addWidget(workingSpaceGroupbox);
    centerLayout->addWidget(connectGroupbox);
    rightLayout->addWidget(flowChartGroupbox);

    leftWidget->setLayout(leftLayout);
    centerWidget->setLayout(centerLayout);
    rightWidget->setLayout(rightLayout);

    basicLayout->addWidget(leftWidget);
    basicLayout->addWidget(centerWidget);
    basicLayout->addWidget(rightWidget);
    basicWidget->setLayout(basicLayout);

    setCentralWidget(basicWidget);
    workingSpaceWidget->setFixedSize(530,670);
    connectWidget->setFixedSize(470,105);
    setFixedSize(1600,720);
    hide();
}

