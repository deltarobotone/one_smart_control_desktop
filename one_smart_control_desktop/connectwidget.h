#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QListView>
#include <QProgressBar>
#include <QStringListModel>

#include "easyprotocol.h"
#include "smartcontroldata.h"

namespace OneSmartControl
{

class ConnectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent = nullptr);

private:
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;

    QHBoxLayout *basicLayout;
    QHBoxLayout *connectLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;

    QWidget *connectWidget;
    QWidget *leftWidget;
    QWidget *rightWidget;

    QLabel *statusLabel;
    QLabel *idLabel;
    QLabel *portLabel;

    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QPushButton *refreshButton;

    QProgressBar *scanProgressBar;

    QListView *devicesListView;
    QStringList *devicesStringList;
    QStringListModel *devicesListModel;

    QDialog *connectionFailedDialog;
    QVBoxLayout *connectionFailedLayout;
    QImage *connectionFailedImage;
    QLabel *connectionfailedWidget;

    bool scanState = false;

    void createLayout();

private slots:
    void connectButtonHandle();
    void disconnectButtonHandle();
    void refreshButtonHandle();
    void scanProgressBarHandle(int value);
    void selectionChangedHandle( const QModelIndex& selected, const QModelIndex& deselected );

public slots:
    void scanFinished();
    void scanStarted();
    void deviceDisconnected();
    void connectingDevice();
    void handshakeFailed();
    void deviceConnected(char id);
};

} // OneSmartControl

#endif // CONNECTWIDGET_H
