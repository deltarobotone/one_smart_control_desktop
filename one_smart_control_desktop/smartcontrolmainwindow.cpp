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

    infoLabel = new QLabel;
    infoGroupbox = new QGroupBox;
    infoLayout = new QVBoxLayout;

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
    robot.connection.disconnectDevice();
    delete ui;
}

void SmartControlMainWindow::createLayout()
{
    setStyleSheet("background-color:white;");

    connect(sliderWidget,SIGNAL(toChart()),this,SLOT(showToChartMessage()));
    connect(lightWidget,SIGNAL(toChart()),this,SLOT(showToChartMessage()));
    connect(gripperWidget,SIGNAL(toChart()),this,SLOT(showToChartMessage()));
    connect(flowChartWidget->timeWidget,SIGNAL(toChart()),this,SLOT(showToChartMessage()));

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

    infoGroupbox->setLayout(infoLayout);
    infoGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
    infoLayout->addWidget(infoLabel);

    QFont font("Arial Rounded MT Bold", 14);
    infoLabel->setFont(font);
    infoLabel->setText("");

    leftLayout->addWidget(sliderGroupbox);
    leftLayout->addWidget(lightGroupbox);
    leftLayout->addWidget(gripperGroupbox);

    centerLayout->addWidget(workingSpaceGroupbox);
    centerLayout->addWidget(connectGroupbox);

    rightLayout->addWidget(infoGroupbox);
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
    setFixedSize(1600,720);
    hide();
}

void SmartControlMainWindow::showToChartMessage()
{
    if(smartControlData.dataid == ID::move && smartControlData.workingSpaceStatus)
    {
        infoLabel->setAlignment(Qt::AlignHCenter);
        infoLabel->setStyleSheet("QLabel{ color: rgb(200, 50, 50);}");
        infoLabel->setText("Position out of workingspace!");
    }
    else
    {
        infoLabel->setAlignment(Qt::AlignHCenter);
        infoLabel->setStyleSheet("QLabel{ color: rgb(30, 144, 255);}");
        infoLabel->setText("Command added to flowchart >>");
    }
    QTimer::singleShot(750, this, &SmartControlMainWindow::hideToChartMessage);
}

void SmartControlMainWindow::hideToChartMessage()
{
    infoLabel->setText("");
}

