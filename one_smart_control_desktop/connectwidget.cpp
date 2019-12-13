#include "connectwidget.h"

OneSmartControl::ConnectWidget::ConnectWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent) :
    QWidget(parent),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QHBoxLayout(this);

    connectLayout = new QHBoxLayout;
    leftLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;

    connectWidget = new QWidget;
    leftWidget = new QWidget;
    rightWidget = new QWidget;

    connectButton = new QPushButton;
    disconnectButton = new QPushButton;
    refreshButton = new QPushButton;

    scanProgressBar = new QProgressBar;

    devicesListView= new QListView;
    devicesStringList = new QStringList;
    devicesListModel = new QStringListModel;

    statusLabel = new QLabel;
    idLabel = new QLabel;
    portLabel = new QLabel;

    connectionFailedDialog = new QDialog(this);
    connectionFailedLayout = new QVBoxLayout;
    connectionFailedImage = new QImage;
    connectionfailedWidget = new QLabel;

    createLayout();

    connect(&robot.connection,SIGNAL(connectingDevice()),this,SLOT(connectingDevice()));
    connect(&robot.connection, SIGNAL(deviceConnected(char)),this,SLOT(deviceConnected(char)));
    connect(&robot.connection,SIGNAL(deviceDisconnected()),this,SLOT(deviceDisconnected()));
    connect(&robot.connection,SIGNAL(scanStarted()),this,SLOT(scanStarted()));
    connect(&robot.connection,SIGNAL(scanFinished()),this,SLOT(scanFinished()));
    connect(&robot.connection,SIGNAL(handshakeFailed()),this,SLOT(handshakeFailed()));
    connect(&robot.connection, SIGNAL(updateScanValue(int)),this,SLOT(scanProgressBarHandle(int)));
}

void OneSmartControl::ConnectWidget::createLayout()
{
    QFont font("Arial Rounded MT Bold", 14);

    devicesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    devicesListView->setSelectionMode(QAbstractItemView::SingleSelection);
    devicesListView->setFont(font);
    devicesListView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid rgb(200, 200, 200); padding: 20px 20px;}"
                                   "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 5px; border: 2px solid rgb(200, 200, 200);}"
                                   "QScrollBar:horizontal{height: 10px; background-color: rgb(200, 200, 200); border: 5px transparent; border-radius: 5px;}"
                                   "QScrollBar::handle:horizontal{height: 10px; background: rgb(30, 144, 255); border: 5px rgb(30, 144, 255); border-radius: 5px;}"
                                   "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                   "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                   "QScrollBar:vertical{width: 10px; background-color: rgb(200, 200, 200); border: 5px transparent; border-radius: 5px;}"
                                   "QScrollBar::handle:vertical{width: 10px; background: rgb(30, 144, 255); border: 5px rgb(30, 144, 255); border-radius: 5px;}"
                                   "QScrollBar::add-line:vertical{border: none;background: none;}"
                                   "QScrollBar::sub-line:vertical{border: none;background: none;}");
    scanProgressBar->setFont(font);
    scanProgressBar->setStyleSheet("QProgressBar {border-radius: 10px; border: 2px solid rgb(200, 200, 200);height: 10px;}"
                                   "QProgressBar::chunk {background-color: rgb(30, 144, 255);border-bottom-right-radius: 8px;border-bottom-left-radius: 8px;border-top-right-radius: 8px;border-top-left-radius: 8px; padding: 2px 2px;}");
    scanProgressBar->setValue(0);
    scanProgressBar->setMinimum(0);
    scanProgressBar->setMaximum(280);
    scanProgressBar->setTextVisible(false);

    connectButton->setIcon(QIcon(":/images/icons/connect.png"));
    connectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    connectButton->setIconSize(QSize(60, 60));
    connect(connectButton, SIGNAL(released()),this,SLOT(connectButtonHandle()));

    disconnectButton->setIcon(QIcon(":/images/icons/disconnect.png"));
    disconnectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    disconnectButton->setIconSize(QSize(60, 60));
    connect(disconnectButton, SIGNAL(released()),this,SLOT(disconnectButtonHandle()));

    refreshButton->setIcon(QIcon(":/images/icons/refresh.png"));
    refreshButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
    refreshButton->setIconSize(QSize(60, 60));
    connect(refreshButton, SIGNAL(released()),this,SLOT(refreshButtonHandle()));

    statusLabel->setFont(font);
    statusLabel->setText("Status: disconnected");
    idLabel->setFont(font);
    idLabel->setText("Robot-ID: -");
    portLabel->setFont(font);
    portLabel->setText("USB-Port: -");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(true);
    disconnectButton->setEnabled(false);

    connectLayout->addWidget(connectButton);
    connectLayout->addWidget(disconnectButton);
    connectLayout->addWidget(refreshButton);

    connectLayout->setContentsMargins(10,0,10,0);
    connectWidget->setLayout(connectLayout);
    connectWidget->setMinimumHeight(70);

    leftLayout->addWidget(connectWidget,0,Qt::AlignLeft);
    leftLayout->addWidget(statusLabel,0,Qt::AlignLeft);
    leftLayout->addWidget(portLabel,0,Qt::AlignLeft);
    leftLayout->addWidget(idLabel,0,Qt::AlignLeft);
    leftLayout->setContentsMargins(10,0,10,0);
    leftWidget->setMinimumWidth(250);
    leftWidget->setLayout(leftLayout);

    rightLayout->addWidget(devicesListView);
    rightLayout->addWidget(scanProgressBar);
    rightLayout->setContentsMargins(10,0,10,0);
    rightWidget->setMinimumWidth(200);
    rightWidget->setLayout(rightLayout);

    basicLayout->addWidget(leftWidget);
    basicLayout->addWidget(rightWidget);

    setLayout(basicLayout);
}

void OneSmartControl::ConnectWidget::selectionChangedHandle( const QModelIndex& selected, const QModelIndex& deselected )
{
    connectButton->setEnabled(true);
    refreshButton->setEnabled(true);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(true);
};

void OneSmartControl::ConnectWidget::scanProgressBarHandle(int value)
{
    scanProgressBar->setValue(value+24);
    this->repaint();
};

void OneSmartControl::ConnectWidget::connectButtonHandle()
{
    int index = devicesListView->currentIndex().row();
    robot.connection.connectDevice(index);

    QString robotid = QChar(robot.getRobotID());
    QString port = QString::fromStdString(robot.getPort());
}

void OneSmartControl::ConnectWidget::handshakeFailed()
{
    statusLabel->setText("Status: handshake failed");
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

void OneSmartControl::ConnectWidget::disconnectButtonHandle()
{
    statusLabel->setText("Status: disconnect...");
    idLabel->setText("Robot-ID: -");
    portLabel->setText("USB-Port: -");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);

    robot.connection.disconnectDevice();
}

void OneSmartControl::ConnectWidget::refreshButtonHandle()
{
    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);

    devicesStringList->clear();
    devicesListModel->setStringList( QStringList{} );
    devicesListView->setModel(devicesListModel);
    robot.connection.startDeviceDiscovery();
}

void OneSmartControl::ConnectWidget::connectingDevice()
{
    statusLabel->setText("Status: connecting...");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);
}

void OneSmartControl::ConnectWidget::deviceConnected(char id)
{
    statusLabel->setText("Status: connected");

    QString qid = QString::fromStdString(&id);

    int index = devicesListView->currentIndex().row();
    QString modul = devicesStringList->at(index);

    idLabel->setText("Robot-ID: " + qid);
    portLabel->setText("USB-Port: " + modul);

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(true);
    devicesListView->setEnabled(false);
}

void OneSmartControl::ConnectWidget::deviceDisconnected()
{
    if(!scanState)
    {
        statusLabel->setText("Status: disconnected");
        idLabel->setText("Robot-ID: -");
        portLabel->setText("USB-Port: -");

        connectButton->setEnabled(false);
        refreshButton->setEnabled(true);
        disconnectButton->setEnabled(false);
        devicesListView->setEnabled(false);

        devicesStringList->clear();
        devicesListModel->setStringList( QStringList{} );
        devicesListView->setModel(devicesListModel);
    }
}

void OneSmartControl::ConnectWidget::scanStarted()
{
    scanState = true;
    devicesStringList->clear();
    devicesListModel->setStringList( QStringList{} );
    devicesListView->setModel(devicesListModel);

    statusLabel->setText("Status: scanning...");
    idLabel->setText("Robot-ID: -");
    portLabel->setText("USB-Port: -");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);
}

void OneSmartControl::ConnectWidget::scanFinished()
{
    QList<QString> deviceList = robot.connection.getDeviceList();

    scanState = false;
    devicesStringList->clear();
    devicesListModel->setStringList( QStringList{} );
    devicesListView->setModel(devicesListModel);

    if(!deviceList.empty())
    {
        statusLabel->setText("Status: scan finished");
        idLabel->setText("Robot-ID: -");
        portLabel->setText("USB-Port: -");

        connectButton->setEnabled(false);
        refreshButton->setEnabled(true);
        disconnectButton->setEnabled(false);
        devicesListView->setEnabled(true);

        for (int i = 0; i < deviceList.size(); i++)
        {
            devicesStringList->append(deviceList.at(i));
            devicesListModel->setStringList(*devicesStringList);
            devicesListView->setModel(devicesListModel);
        }
    }
    else
    {
        statusLabel->setText("Status: no device found");
        idLabel->setText("Robot-ID: -");
        portLabel->setText("USB-Port: -");

        connectButton->setEnabled(false);
        refreshButton->setEnabled(true);
        disconnectButton->setEnabled(false);
        devicesListView->setEnabled(false);
    }

    QItemSelectionModel *selectionModel = devicesListView->selectionModel();
    connect(selectionModel,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(selectionChangedHandle(QModelIndex,QModelIndex)));
};

