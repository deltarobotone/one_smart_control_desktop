# include "easyprotocol.h"

UniversalSerialBusDevice::UniversalSerialBusDevice(QObject *parent): QObject(parent)
{
    connect(this, SIGNAL(waitForSignal()),this,SLOT(waitForResponse()));
    connect(this, SIGNAL(connectPort()),this,SLOT(connectHandle()));
    connect(this, SIGNAL(disconnectPort()),this,SLOT(disconnectHandle()));
    connect(this, SIGNAL(scanStarted()),this,SLOT(startPortScanner()));
    connect(this, SIGNAL(checkDevice()),this,SLOT(checkDeviceHandle()));
    connect(this, SIGNAL(startHandshake()),this,SLOT(handshake()));

    serialPort.moveToThread(&communicationThread);
    moveToThread(&communicationThread);
    communicationThread.start();
}

UniversalSerialBusDevice::~UniversalSerialBusDevice()
{
    if (isConnected())
    {
        disconnectDevice();
    }
    communicationThread.quit();
    communicationThread.wait(1000);
}

void UniversalSerialBusDevice::connectHandle()
{
    QString qstr = QString::fromStdString(port);
    QString adress = "\\\\.\\" + qstr;

    serialPort.setPortName(adress);
    serialPort.setBaudRate(baudrate);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort.open(QIODevice::ReadWrite))
    {
        serialPort.setDataTerminalReady(true);
        serialPort.setRequestToSend(true);
        connected = true;
        if(enable) emit checkDevice();
    }
    else
    {
        connected = false;
        clearPort();
    }
}

void UniversalSerialBusDevice::disconnectHandle()
{
    QMutex mutex;
    mutex.lock();
    if(serialPort.isOpen())
    {
        serialPort.clear();
        serialPort.close();
    }
    connected = false;
    emit deviceDisconnected();
    mutex.unlock();
}

void UniversalSerialBusDevice::connectDevice(int deviceIndex)
{
    QMutex mutex;
    mutex.lock();
    this->port = deviceList.at(deviceIndex).toStdString();
    enable=true;
    mutex.unlock();
    emit connectPort();
}

void UniversalSerialBusDevice::checkDeviceHandle()
{
    emit connectingDevice();
    emit startHandshake();
}

void UniversalSerialBusDevice::disconnectDevice()
{
    QMutex mutex;
    mutex.lock();
    enable = false;
    mutex.unlock();
    emit disconnectPort();
}

void UniversalSerialBusDevice::receive(char rxChar)
{
    QMutex mutex;
    mutex.lock();
    receivedData = rxChar;
    mutex.unlock();

    if (!init)
    {
        emit dataReceived();
        init = true;
    }
    else
    {
        if (!queueTXData.isEmpty())send();
        else emit freeChannel();
    }
    if(enable) emit waitForSignal();
}

void UniversalSerialBusDevice::send()
{
    if (!queueTXData.isEmpty())
    {
        if(block==false)
        {
            std::string txString = queueTXData.dequeue();
            if(txString != "T")
            {
                transmit(txString);
            }
            else
            {
                std::string time = queueTXData.dequeue();
                waitFor(std::stoi(time));
            }
        }
    }
}

void UniversalSerialBusDevice::transmit(std::string txString)
{
    QString timestamp = QDateTime::currentDateTime().toString("ss,zzzz");
    qDebug() << timestamp ;

    int lenght = 22;
    if(serialPort.isOpen())
    {
        serialPort.clear();
        serialPort.write(txString.c_str(),lenght);
        serialPort.waitForBytesWritten();
        emit dataTransmitted();
    }
}

void UniversalSerialBusDevice::stopTransmission()
{
    QMutex mutex;
    mutex.lock();
    queueTXData.clear();
    mutex.unlock();
}

void UniversalSerialBusDevice::write(std::string txString)
{
    QMutex mutex;
    mutex.lock();
    queueTXData.enqueue(txString);
    mutex.unlock();
    return;
}

int UniversalSerialBusDevice::readPort(char &buffer, int length = 2)
{
    qint64 rxlength = 0;
    if(serialPort.isOpen())
    {
        serialPort.waitForReadyRead(1000);
        rxlength = serialPort.read(&buffer,length);
    }
    return int(rxlength);
}

char UniversalSerialBusDevice::read()
{
    char data;
    QMutex mutex;
    mutex.lock();
    data = receivedData;
    receivedData = ' ';
    mutex.unlock();
    return data;
}

void UniversalSerialBusDevice::waitForResponse()
{
    char rxData = ' ';
    while (enable)
    {
        rxData = ' ';
        clearPort();
        if (readPort(rxData, 1) != 0)
        {
            receive(rxData);
            break;
        }
    }
}

void UniversalSerialBusDevice::waitFor(int milliseconds)
{
    block = true;
    qDebug() << "wait" ;
    QString timestamp = QDateTime::currentDateTime().toString("ss,zzzz");
    qDebug() << timestamp ;
    qDebug() << milliseconds ;
    emit dataTransmitted();
    QThread::msleep(milliseconds);
    block = false;
    send();
}

QList<QString> UniversalSerialBusDevice::getDeviceList(){return deviceList;};

void UniversalSerialBusDevice::clearPort()
{
    if(serialPort.isOpen())serialPort.clear();
}

bool UniversalSerialBusDevice::isConnected()
{
    bool status = false;

    QMutex mutex;
    mutex.lock();
    if(serialPort.isOpen()) connected = true;
    else connected = false;
    status=connected;
    mutex.unlock();

    return status;
}

void UniversalSerialBusDevice::startDeviceDiscovery()
{
    scanStatusValue=0;
    emit updateScanValue(scanStatusValue);
    emit scanStarted();
    QThread::msleep(30);
}

void UniversalSerialBusDevice::updateScanStatus()
{
    scanStatusValue++;
    emit updateScanValue(scanStatusValue);
}

void UniversalSerialBusDevice::startPortScanner()
{
    deviceList.clear();
    for (int i = 0; i < 256; i++)
    {
        emit updateScanStatus();

        std::string nr = std::to_string(i);
        port = "COM" + nr;

        emit connectPort();
        QThread::msleep(30);

        if (isConnected())
        {
            deviceList.append(QString::fromStdString(port));
        }
        emit disconnectDevice();
        QThread::msleep(30);
    }
    emit scanFinished();
    QThread::msleep(30);
}

void UniversalSerialBusDevice::handshake()
{
    QThread::msleep(50);

    if (isConnected())
    {
        QThread::msleep(500);
        char rxchar = ' ';
        char check = ' ';

        readPort(rxchar);

        if (rxchar != ' ' && rxchar != check)
        {
            check = rxchar;
            rxchar = ' ';
            QThread::msleep(500);
        }

        readPort(rxchar);
        if (check != ' ' && rxchar == check)
        {
            emit deviceConnected(rxchar);
            emit waitForSignal();
            return;
        }
        emit handshakeFailed();
    }
    emit disconnectPort();
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

Move::Move(UniversalSerialBusDevice & serialport) : Basic(serialport)
{
}

void Move::ptp(float positionX, float positionY, float positionZ, float speed)
{
    if (serial.isConnected())
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
        serial.write(txString);
    }
    return;
}

void Move::ptp(Pos position, float speed)
{
    ptp(position.x,position.y,position.z,speed);
    return;
}

Gripper::Gripper(UniversalSerialBusDevice & serialport) : Basic(serialport)
{
}

void Gripper::open()
{
    if (serial.isConnected())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::gripperopen;
        utils.fillData(txString);
        serial.write(txString);
    }
    return;
}

void Gripper::close()
{
    if (serial.isConnected())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::gripperclose;
        utils.fillData(txString);
        serial.write(txString);
    }
    return;
}

Light::Light(UniversalSerialBusDevice & serialport) : Basic(serialport)
{
}

void Light::on(float intensity)
{
    if (serial.isConnected())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        serial.write(txString);
    }
    return;
}

void Light::off()
{
    if (serial.isConnected())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lightoff;
        utils.fillData(txString);
        serial.write(txString);
    }
    return;
}

void Light::setColour(std::string colour, float intensity)
{
    if (serial.isConnected())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton + '#' + colour;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        serial.write(txString);
    }
    return;
}

void Light::setIntensity(float intensity)
{
    if (serial.isConnected())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        serial.write(txString);
    }
    return;
}

ExtMotor::ExtMotor(UniversalSerialBusDevice & serialport) : Basic(serialport)
{
}

void ExtMotor::stop()
{
    if (serial.isConnected())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoroff;
        utils.fillData(txString);
        serial.write(txString);
    }
    return;
}

void ExtMotor::setSpeed(float speed)
{
    if (serial.isConnected())
    {
        std::string v = utils.valueToString(speed);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoron;
        utils.fillData(txString, 18);
        txString = txString + v.erase(0, 1);
        serial.write(txString);
    }
    return;
}

void ExtMotor::start(float speed)
{
    if (serial.isConnected())
    {
        std::string v = utils.valueToString(speed);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoron;
        utils.fillData(txString, 18);
        txString = txString + v.erase(0, 1);
        serial.write(txString);
    }
    return;
}

Functions::Functions(UniversalSerialBusDevice & serialport) : Basic(serialport)
{
}

void Functions::waitFor(unsigned long milliseconds)
{
    if (serial.isConnected())
    {
        serial.write("T");
        serial.write(std::to_string(milliseconds));
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
    if (connection.isConnected())
    {
        connection.disconnectDevice();
    }
}

std::string EasyProtocol::getPort(){return port;};
char EasyProtocol::getRobotID(){return robotid;};

Basic::Basic(UniversalSerialBusDevice &serialport) :
    robotid('1'),
    deviceid('1'),
    serial(serialport),
    utils()
{
}

void Basic::setID(char robotid, char deviceid)
{
    this->robotid = robotid;
    this->deviceid = deviceid;
}
