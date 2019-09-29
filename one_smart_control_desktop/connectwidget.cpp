#include "connectwidget.h"

OneSmartControl::ConnectWidget::ConnectWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent) :
    QWidget(parent),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);

    connectLayout = new QHBoxLayout;
    statusLayout = new QVBoxLayout;

    connectWidget = new QWidget;
    statusWidget = new QWidget;

    connectButton = new QPushButton;
    disconnectButton = new QPushButton;

    statusLabel = new QLabel;
    idLabel = new QLabel;
    portLabel = new QLabel;

    connectionFailedDialog = new QDialog(this);
    connectionFailedLayout = new QVBoxLayout;
    connectionFailedImage = new QImage;
    connectionfailedWidget = new QLabel;

    createLayout();
}

void OneSmartControl::ConnectWidget::createLayout()
{
    connectButton->setIcon(QIcon(":/images/icons/connect.png"));
    connectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    connectButton->setIconSize(QSize(65, 65));
    connect(connectButton, SIGNAL(released()),this,SLOT(connectButtonHandle()));

    disconnectButton->setIcon(QIcon(":/images/icons/disconnect.png"));
    disconnectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    disconnectButton->setIconSize(QSize(65, 65));
    connect(disconnectButton, SIGNAL(released()),this,SLOT(disconnectButtonHandle()));

    QFont font("Arial Rounded MT Bold", 14);
    statusLabel->setFont(font);
    statusLabel->setText("Status: disconnected");
    idLabel->setFont(font);
    idLabel->setText("Robot-ID: -");
    portLabel->setFont(font);
    portLabel->setText("USB-Port: -");

    connectLayout->addWidget(connectButton,0,Qt::AlignLeft);
    connectLayout->addWidget(disconnectButton,0,Qt::AlignLeft);

    statusLayout->addWidget(statusLabel,0,Qt::AlignLeft);
    statusLayout->addWidget(portLabel,0,Qt::AlignLeft);
    statusLayout->addWidget(idLabel,0,Qt::AlignLeft);
    statusLayout->setContentsMargins(10,0,10,0);
    statusWidget->setFixedWidth(250);
    statusWidget->setLayout(statusLayout);

    connectLayout->addWidget(statusWidget,0,Qt::AlignLeft);

    connectLayout->setContentsMargins(10,0,10,10);
    connectWidget->setLayout(connectLayout);
    basicLayout->addWidget(connectWidget);

    setLayout(basicLayout);
}

void OneSmartControl::ConnectWidget::connectButtonHandle()
{
    statusLabel->setText("Status: connecting...");
    repaint();
    robot.findRobot();
    robot.start();

    QString robotid = QChar(robot.getRobotID());
    QString port = QString::fromStdString(robot.getPort());

    if(robot.isConnected()==true)
    {
        statusLabel->setText("Status: connected");
        idLabel->setText("Robot-ID: " + robotid);
        portLabel->setText("USB-Port: " + port);
    }
    else
    {
        statusLabel->setText("Status: disconnected");
        idLabel->setText("Robot-ID: -");
        portLabel->setText("USB-Port: -");


        connectionFailedImage->load(":/images/screens/connectionfailed.png");
        connectionfailedWidget->setPixmap(QPixmap::fromImage(*connectionFailedImage));
        connectionFailedLayout->addWidget(connectionfailedWidget,0,Qt::AlignCenter);
        connectionFailedDialog->setLayout(connectionFailedLayout);
        connectionFailedDialog->setFixedSize(400,600);
        connectionFailedDialog->setWindowTitle("Information");
        connectionFailedDialog->setWindowFlags(connectionFailedDialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
        connectionFailedDialog->show();

    }
}

void OneSmartControl::ConnectWidget::disconnectButtonHandle()
{
    robot.stop();
    statusLabel->setText("Status: disconnected");
    idLabel->setText("Robot-ID: -");
    portLabel->setText("USB-Port: -");
}
