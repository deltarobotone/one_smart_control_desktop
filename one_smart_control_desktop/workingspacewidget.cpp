#include "workingspacewidget.h"

OneSmartControl::WorkingSpaceWidget::WorkingSpaceWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, QWidget *parent):
    QWidget(parent),
    robot(easyProtocol),
    controlData(smartControlData)
{
    createLayout();
}

void OneSmartControl::WorkingSpaceWidget::createLayout()
{
    setStyleSheet("background-color:white;");
}

void OneSmartControl::WorkingSpaceWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QColor oneblue(30, 144, 255);
    QColor gray(230,230,230);
    QColor darkgray(50,50,50);
    QColor linegray(120,120,120);

    int intensity = 50 + controlData.intensity;

    QColor red(200, 40, 40, intensity);
    QColor green(20, 200, 20, intensity);
    QColor blue(20, 20, 200, intensity);
    QColor white(250, 250, 250, intensity);
    QColor cyan(20, 200, 200, intensity);
    QColor yellow(200, 200, 20, intensity);
    QColor magenta(200, 20, 200, intensity);

    QColor colourArea;
    if(controlData.colour==Colour::red) colourArea = red;
    else if(controlData.colour==Colour::red) colourArea = red;
    else if(controlData.colour==Colour::green) colourArea = green;
    else if(controlData.colour==Colour::blue) colourArea = blue;
    else if(controlData.colour==Colour::white) colourArea = white;
    else if(controlData.colour==Colour::cyan) colourArea = cyan;
    else if(controlData.colour==Colour::magenta) colourArea = magenta;
    else if(controlData.colour==Colour::yellow) colourArea = yellow;
    else colourArea=gray;

    QRadialGradient radialGrad(QPoint(235,235), 100);
    radialGrad.setColorAt(0.0, gray);
    radialGrad.setColorAt(0.75, colourArea);
    radialGrad.setColorAt(1.0, gray);

    QPen pen;
    pen.setColor(linegray);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);

    QPainter space(this);
    space.setPen(pen);
    if(controlData.workingSpaceStatus==true) space.setBrush(red);
    else space.setBrush(Qt::Dense7Pattern);
    space.drawEllipse(10, 10, 450, 450);

    int radius = 0;
    if(controlData.zPosition >= 70 && controlData.zPosition <= 79.0) radius = 250;
    if(controlData.zPosition >= 80 && controlData.zPosition <= 99.0) radius = 450;
    if(controlData.zPosition >= 100 && controlData.zPosition <= 119.0) radius = 375;
    if(controlData.zPosition >= 120 && controlData.zPosition <= 130.0) radius = 150;

    QPainter background(this);
    background.setPen(pen);
    background.setBrush(gray);
    background.drawEllipse(10+(450-radius)/2, 10+(450-radius)/2, radius, radius);

    QPainter painterWorkingSpace(this);
    painterWorkingSpace.setPen(pen);
    painterWorkingSpace.setBrush(radialGrad);
    painterWorkingSpace.drawEllipse(10+(450-radius)/2, 10+(450-radius)/2, radius, radius);

    QPainter painterTCP(this);

    if(controlData.gripperStatus==true) pen.setColor(oneblue);
    else pen.setColor(darkgray);

    pen.setWidth(4);
    painterTCP.setPen(pen);
    painterTCP.drawLine(235+controlData.yPosition*5+10, 235+controlData.xPosition*-5, 235+controlData.yPosition*5-10, 235+controlData.xPosition*-5);
    painterTCP.drawLine(235+controlData.yPosition*5, 235+controlData.xPosition*-5+10, 235+controlData.yPosition*5, 235+controlData.xPosition*-5-10);

    QPainter painterScale(this);
    pen.setColor(linegray);

    pen.setWidth(4);
    painterScale.setPen(pen);

    painterScale.drawLine(500, 10, 500, 460);

    painterScale.drawLine(490, 10, 510, 10);
    painterScale.drawLine(490, 85, 510, 85);
    painterScale.drawLine(490, 235, 510, 235);
    painterScale.drawLine(490, 385, 510, 385);
    painterScale.drawLine(490, 460, 510, 460);

    QPainter painterLevel(this);

    pen.setColor(oneblue);

    pen.setWidth(4);
    painterLevel.setPen(pen);

    painterLevel.drawLine(490, ((controlData.zPosition-70)*75/10)+10, 510, ((controlData.zPosition-70)*75/10)+10);
}


