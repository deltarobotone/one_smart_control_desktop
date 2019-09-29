#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>

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

    QGridLayout *basicLayout;
    QHBoxLayout *connectLayout;
    QVBoxLayout *statusLayout;

    QWidget *connectWidget;
    QWidget *statusWidget;

    QLabel *statusLabel;
    QLabel *idLabel;
    QLabel *portLabel;

    QPushButton *connectButton;
    QPushButton *disconnectButton;

    QDialog *connectionFailedDialog;
    QVBoxLayout *connectionFailedLayout;
    QImage *connectionFailedImage;
    QLabel *connectionfailedWidget;

    void createLayout();

private slots:
    void connectButtonHandle();
    void disconnectButtonHandle();
};

} // OneSmartControl

#endif // CONNECTWIDGET_H
