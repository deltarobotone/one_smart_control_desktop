#include <QApplication>
#include <QThread>
#include <QSplashScreen>

#include "config.h"
#include "easyprotocol.h"
#include "smartcontrolmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);   

    a.setWindowIcon(QIcon(":/images/icons/oneicon.png"));

    QPixmap pixmap(":/images/logos/onesmartcontrol.png");

    QSplashScreen splash(pixmap);

    splash.show();
    splash.showMessage("V" + OneSmartControl::version.toString());

    QThread::sleep(3);

    splash.close();

    SmartControlMainWindow mainwindow;

    mainwindow.show();

    return a.exec();
}
