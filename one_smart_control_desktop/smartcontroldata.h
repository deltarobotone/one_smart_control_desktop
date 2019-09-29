#ifndef SMARTCONTROLDATA_H
#define SMARTCONTROLDATA_H

#include <string>
#include <QString>

#include "easyprotocol.h"

namespace OneSmartControl
{

class SmartControlData
{
public:
    std::string dataid = "";
    std::string robotid = "";
    std::string deviceid = "";

    std::string colour = "";
    int intensity = 0; //%

    int xPosition = 0; //mm
    int yPosition = 0; //mm
    int zPosition = 0; //mm
    int velocity = 0;  //%
    bool workingSpaceStatus = false;

    bool gripperStatus = false;

    uint waitFortime = 0; //ms

    QString toString();
    QString toDataString();
    void fromDataString(QString str);
};

} // OneSmartControl

#endif // SMARTCONTROLDATA_H
