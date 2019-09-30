# include "easyprotocol.h"

SerialPort::SerialPort()
{
    serialPortHandle = new QSerialPort;
}

SerialPort::~SerialPort()
{
    if(serialPortHandle->isOpen())
    {
        serialPortHandle->clear();
        serialPortHandle->close();
    }
    delete serialPortHandle;
}

void SerialPort::open(std::string port, int baudrate)
{
    QString qstr = QString::fromStdString(port);
    QString adress = "\\\\.\\" + qstr;

    serialPortHandle->setPortName(adress);
    serialPortHandle->setBaudRate(baudrate);
    serialPortHandle->setDataBits(QSerialPort::Data8);
    serialPortHandle->setParity(QSerialPort::NoParity);
    serialPortHandle->setStopBits(QSerialPort::OneStop);
    serialPortHandle->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPortHandle->open(QIODevice::ReadWrite))
    {
        serialPortHandle->setDataTerminalReady(true);
        serialPortHandle->setRequestToSend(true);
        connected = true;
    }
    else
    {
        connected = false;
        clear();
    }
}

void SerialPort::close(void)
{
    if(serialPortHandle->isOpen())
    {
        serialPortHandle->clear();
        serialPortHandle->close();
    }
    connected = false;
}

void SerialPort::write(std::string txString, int lenght = 22)
{
    if(serialPortHandle->isOpen())
    {
        serialPortHandle->write(txString.c_str(),lenght);
        serialPortHandle->waitForBytesWritten();
    }
    return;
}

int SerialPort::read(char &buffer, int length = 2)
{
    qint64 rxlength = 0;
    if(serialPortHandle->isOpen())
    {
        serialPortHandle->waitForReadyRead(1);
        rxlength = serialPortHandle->read(&buffer,length);
    }
    return int(rxlength);
}

void SerialPort::clear()
{
    if(serialPortHandle->isOpen())
    {
        serialPortHandle->clear();
    }
}

bool SerialPort::isOpen()
{
    if(serialPortHandle->isOpen()) connected = true;
    else
    {
        connected = false;
        clear();
        close();
    }
    return connected;
}

Utils::Utils()
{
}

std::string Utils::valueToString(float value)
{
    if (value > -1000.0F && value < 1000.0F)
    {
        double upvalue = double(value * 10.0F);
        int temp = int(trunc(upvalue));
        if (temp < 0) temp = temp * -1;
        std::string strint = std::to_string(temp);
        std::string strraw = "";
        std::string strsigned = "";

        if (value > -1.0F && value < 1.0F)
        {
            strraw = "000";
            strraw.append(strint);
        }
        else if (value > -10.0F && value < 10.0F)
        {
            strraw = "00";
            strraw.append(strint);
        }
        else if (value > -100.0F && value < 100.0F)
        {
            strraw = "0";
            strraw.append(strint);
        }
        else if (value > -1000.0F && value < 1000.0F)
        {
            strraw = strint;
        }
        else
        {
            return "0000";
        }

        if (value >= 0.0F)
        {
            strsigned = "+";
            strsigned.append(strraw);
        }
        else
        {
            strsigned = "-";
            strsigned.append(strraw);
        }
        return strsigned;
    }
    return "0000";
}

Pos::Pos()
{
}

std::string Utils::posToString(Pos position)
{
    std::string strX = valueToString(position.x);
    std::string strY = valueToString(position.y);
    std::string strZ = valueToString(position.z);
    return strX + strY + strZ;
}

void Utils::fillData(std::string &txString, int length)
{
    int i = 0;
    if (int(txString.length()) < length)
    {
        i = int(txString.length());
        while (i < length)
        {
            txString = txString + '#';
            i++;
        }
    }
}

Move::Move(SerialPort & serialport) : Basic(serialport)
{
}

void Move::ptp(float positionX, float positionY, float positionZ, float speed)
{
    if (serial.isOpen())
    {
        Pos pos;
        pos.x = positionX;
        pos.y = positionY;
        pos.z = positionZ;
        std::string s = utils.posToString(pos);
        std::string v = utils.valueToString(speed);
        std::string txString;
        txString = txString + robotid + deviceid + "M" + s + v.erase(0, 1);
        utils.fillData(txString);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

void Move::ptp(Pos position, float speed)
{
    ptp(position.x,position.y,position.z,speed);
    return;
}

Gripper::Gripper(SerialPort & serialport) : Basic(serialport)
{
}

void Gripper::open()
{
    if (serial.isOpen())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::gripperopen;
        utils.fillData(txString);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

void Gripper::close()
{
    if (serial.isOpen())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::gripperclose;
        utils.fillData(txString);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

Light::Light(SerialPort & serialport) : Basic(serialport)
{
}

void Light::on(float intensity)
{
    if (serial.isOpen())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

void Light::off()
{
    if (serial.isOpen())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lightoff;
        utils.fillData(txString);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

void Light::setColour(std::string colour, float intensity)
{
    if (serial.isOpen())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton + '#' + colour;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

void Light::setIntensity(float intensity)
{
    if (serial.isOpen())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

ExtMotor::ExtMotor(SerialPort & serialport) : Basic(serialport)
{
}

void ExtMotor::stop()
{
    if (serial.isOpen())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoroff;
        utils.fillData(txString);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

void ExtMotor::setSpeed(float speed)
{
    if (serial.isOpen())
    {
        std::string v = utils.valueToString(speed);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoron;
        utils.fillData(txString, 18);
        txString = txString + v.erase(0, 1);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

void ExtMotor::start(float speed)
{
    if (serial.isOpen())
    {
        std::string v = utils.valueToString(speed);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoron;
        utils.fillData(txString, 18);
        txString = txString + v.erase(0, 1);
        serial.clear();
        serial.write(txString);
        waitForRobot();
    }
    return;
}

Functions::Functions(SerialPort & serialport) : Basic(serialport)
{
}

void Functions::waitFor(unsigned long milliseconds)
{
    if (serial.isOpen())
    {
        QThread::msleep(milliseconds);
    }
}

EasyProtocol::EasyProtocol() :
    functions(connection),
    move(connection),
    gripper(connection),
    light(connection),
    extmotor(connection)
{
}
EasyProtocol::~EasyProtocol()
{
    if (connection.isOpen())
    {
        connection.clear();
        connection.close();
    }
}
void EasyProtocol::findRobot()
{
    findPorts(baudrate, port, robotid);
}
void EasyProtocol::setPort(std::string port, int baudrate)
{
    this->port = port;
    this->baudrate = baudrate;
}

std::string EasyProtocol::getPort(){return port;};

void EasyProtocol::start()
{
    connected = setCommunication();
    move.setSerialStatus(connected);
    gripper.setSerialStatus(connected);
    light.setSerialStatus(connected);
    extmotor.setSerialStatus(connected);
    functions.setSerialStatus(connected);

}
void EasyProtocol::start(char robotid, char deviceid)
{
    this->robotid = robotid;
    this->deviceid = deviceid;
    move.setID(this->robotid, this->deviceid);
    gripper.setID(this->robotid, this->deviceid);
    light.setID(this->robotid, this->deviceid);
    extmotor.setID(this->robotid, this->deviceid);
    functions.setID(this->robotid, this->deviceid);
    connected = setCommunication();
    move.setSerialStatus(connected);
    gripper.setSerialStatus(connected);
    light.setSerialStatus(connected);
    extmotor.setSerialStatus(connected);
    functions.setSerialStatus(connected);
}
void EasyProtocol::stop()
{
    connection.clear();
    connection.close();
    connected = false;
    move.setSerialStatus(connected);
    gripper.setSerialStatus(connected);
    light.setSerialStatus(connected);
    extmotor.setSerialStatus(connected);
    functions.setSerialStatus(connected);
}

bool EasyProtocol::setCommunication()
{
    connection.open(port, baudrate);

    if (connection.isOpen())
    {
        for (int i = 0; i < 10; i++)
        {
            char rxchar = ' ';
            connection.clear();
            QThread::msleep(500);
            if (connection.read(rxchar, 1) != 0)
            {
                if (rxchar == robotid)
                {
                    return true;
                }
            }
        }
        return false;
    }
    else
    {
        connection.close();
        return false;
    }
}

void EasyProtocol::findPorts(int baudrate, std::string &port, char& robotid)
{
    for (int i = 0; i < 256; i++)
    {
        std::string nr = std::to_string(i);
        std::string portnr = "COM" + nr;

        connection.open(portnr, baudrate);

        if (connection.isOpen())
        {
            char rxchar = ' ';
            char check = ' ';

            connection.clear();
            QThread::msleep(500);
            if (connection.read(rxchar, 1) != 0)
            {
                if (rxchar != ' ' && rxchar != check)
                {
                    check = rxchar;
                    rxchar = ' ';
                }
            }

            connection.clear();
            QThread::msleep(500);
            if (connection.read(rxchar, 1) != 0)
            {
                if (check != ' ' && rxchar == check)
                {
                    robotid = rxchar;
                    port = portnr;
                    connection.close();
                    break;

                }
            }
            connection.close();
        }
        QThread::msleep(20);
    }
    return;
}


char EasyProtocol::getRobotID(){return robotid;};
char EasyProtocol::getDeviceID(){return deviceid;};
void EasyProtocol::setRobotID(char id){robotid = id;};
void EasyProtocol::setDeviceID(char id){deviceid=id;};
bool EasyProtocol::isConnected(){return connected;};

Basic::Basic(SerialPort &serialport) :
    robotid('1'),
    deviceid('1'),
    serial(serialport),
    utils()
{
}

void Basic::waitForRobot()
{
    char rxData;
    if (serial.isOpen())
    {
        while (true)
        {
            rxData = ' ';
            serial.clear();
            if (serial.read(rxData, 1) != 0)
            {
                if (rxData == '0')
                {
                }
                if (rxData == robotid) break;
            }
        }
    }
}


void Basic::setID(char robotid, char deviceid)
{
    this->robotid = robotid;
    this->deviceid = deviceid;
}

void Basic::setSerialStatus(bool status)
{
    connected = status;
}
