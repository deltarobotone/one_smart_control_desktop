#include "smartcontroldata.h"

QString OneSmartControl::SmartControlData::toString()
{
    QString dataString;

    if(dataid==ID::waitFor)
    {
        dataString = "Wait for >> " + QString::number(waitFortime) + " ms ";
    }

    if(dataid==ID::move)
    {
        dataString = "Move to >> X: " + QString::number(xPosition) + " mm " + "> Y: " + QString::number(yPosition) + " mm " + "> Z: " + QString::number(zPosition) + " mm " + "> speed: " + QString::number(velocity)+ " %";
    }

    if(dataid==ID::gripper)
    {
        if(gripperStatus == true) dataString = "Gripper >> close";
        else dataString = "Gripper >> open";
    }

    if(dataid==ID::light)
    {
        QString colourData;
        bool lightStatus = false;
        if(colour == Colour::red)
        {
            colourData = "red";
            lightStatus = true;
        }
        else if(colour == Colour::green)
        {
            colourData = "green";
            lightStatus = true;
        }
        else if(colour == Colour::blue)
        {
            colourData = "blue";
            lightStatus = true;
        }
        else if(colour == Colour::cyan)
        {
            colourData = "cyan";
            lightStatus = true;
        }
        else if(colour == Colour::magenta)
        {
            colourData = "magenta";
            lightStatus = true;
        }
        else if(colour == Colour::yellow)
        {
            colourData = "yellow";
            lightStatus = true;
        }
        else if(colour == Colour::white)
        {
            colourData = "white";
            lightStatus = true;
        }
        else
        {
            colourData = "off";
            lightStatus = false;
        }

        if(lightStatus == true)
        {
            dataString = "Light >> on > colour: " + colourData + " > intensity: " + QString::number(intensity) + " %";
        }
        else
        {
            dataString = "Light >> off";
        }
    }

    return dataString;
}

QString OneSmartControl::SmartControlData::toDataString()
{
    QString dataString;

    if(dataid==ID::waitFor)
    {
        dataString = QString::fromStdString(ID::waitFor) + " " + QString::number(waitFortime);
    }

    if(dataid==ID::move)
    {
        dataString = QString::fromStdString(ID::move) + " " + QString::number(xPosition) + " " + QString::number(yPosition) + " " + QString::number(zPosition) + " " + QString::number(velocity) + " " + QString::number(workingSpaceStatus);
    }

    if(dataid==ID::gripper)
    {
        if(gripperStatus == true) dataString = QString::fromStdString(ID::gripper) + " " + "1";
        else dataString = QString::fromStdString(ID::gripper) + " " + "0";
    }

    if(dataid==ID::light)
    {
        QString colourData;
        bool lightStatus = false;
        if(colour == Colour::red)
        {
            colourData = "1";
            lightStatus = true;
        }
        else if(colour == Colour::green)
        {
            colourData = "2";
            lightStatus = true;
        }
        else if(colour == Colour::blue)
        {
            colourData = "3";
            lightStatus = true;
        }
        else if(colour == Colour::cyan)
        {
            colourData = "4";
            lightStatus = true;
        }
        else if(colour == Colour::magenta)
        {
            colourData = "5";
            lightStatus = true;
        }
        else if(colour == Colour::yellow)
        {
            colourData = "6";
            lightStatus = true;
        }
        else if(colour == Colour::white)
        {
            colourData = "7";
            lightStatus = true;
        }
        else
        {
            colourData = "off";
            lightStatus = false;
        }

        if(lightStatus == true)
        {
            dataString = QString::fromStdString(ID::light) + " " + "1" + " " + colourData + " " + QString::number(intensity);
        }
        else
        {
            dataString = QString::fromStdString(ID::light) + " " + "0";
        }
    }

    return dataString;
}

void OneSmartControl::SmartControlData::fromDataString(QString dataString)
{
    QStringList datalist;
    datalist = dataString.split(" ");

    if( datalist.at(0).toStdString()==ID::waitFor)
    {
        dataid = datalist.at(0).toStdString();
        robotid = "";
        deviceid = "";

        colour = "";
        intensity = 0;

        xPosition = 0;
        yPosition = 0;
        zPosition = 0;
        velocity = 0;

        workingSpaceStatus = false;

        gripperStatus = false;

        waitFortime = datalist.at(1).toUInt();
    }

    if( datalist.at(0).toStdString()==ID::move)
    {
        dataid = datalist.at(0).toStdString();
        robotid = "";
        deviceid = "";

        colour = "";
        intensity = 0;

        xPosition = datalist.at(1).toInt();
        yPosition = datalist.at(2).toInt();
        zPosition = datalist.at(3).toInt();
        velocity = datalist.at(4).toInt();

        if(datalist.at(5).toInt()==0) workingSpaceStatus = false;
        if(datalist.at(5).toInt()==1) workingSpaceStatus = true;

        gripperStatus = false;

        waitFortime = 0;
    }

    if( datalist.at(0).toStdString()==ID::gripper)
    {
        dataid = datalist.at(0).toStdString();
        robotid = "";
        deviceid = "";

        colour = "";
        intensity = 0;

        xPosition = 0;
        yPosition = 0;
        zPosition = 0;
        velocity = 0;

        workingSpaceStatus = false;

        if(datalist.at(1).toInt()==0) gripperStatus = false;
        if(datalist.at(1).toInt()==1) gripperStatus = true;

        waitFortime = 0;
    }

    if( datalist.at(0).toStdString()==ID::light)
    {
        dataid = datalist.at(0).toStdString();
        robotid = "";
        deviceid = "";

        if (datalist.at(1).toInt()==0)
        {
            colour = Protocol::lightoff;
            intensity = 0;
        }
        if (datalist.at(1).toInt()==1)
        {
            switch (datalist.at(2).toInt())
            {
            case 1: colour = Colour::red;
                break;
            case 2: colour = Colour::green;
                break;
            case 3: colour = Colour::blue;
                break;
            case 4: colour = Colour::cyan;
                break;
            case 5: colour = Colour::magenta;
                break;
            case 6: colour = Colour::yellow;
                break;
            case 7: colour = Colour::white;
                break;
            }
            intensity = datalist.at(3).toInt();
        }

        xPosition = 0;
        yPosition = 0;
        zPosition = 0;
        velocity = 0;

        workingSpaceStatus = false;
        gripperStatus = false;

        waitFortime = 0;
    }
}
