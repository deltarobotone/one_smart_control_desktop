#ifndef EASYPROTOCOL
#define EASYPROTOCOL

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QObject>
#include <QMutex>
#include <QThread>
#include <QQueue>
#include <QIODevice>
#include <QThread>
#include <QTimer>
#include <iostream>
#include <cmath>
#include <QDebug>

class UniversalSerialBusDevice: public QObject
{
    Q_OBJECT
private:
    QThread communicationThread;

    bool connected = false;
    bool block = false;
    bool init = false;
    bool enable = false;
    int scanStatusValue = 0;
    char receivedData = ' ';

    QList<QString> deviceList;
    QQueue<std::string> queueTXData;

    std::string port = "COM1";
    int baudrate = 9600;

    void waitFor(int milliseconds);
    void send();
    int readPort(char &buffer, int length);
    void clearPort();

public:
    explicit UniversalSerialBusDevice(QObject *parent = nullptr);
    ~UniversalSerialBusDevice();

    QSerialPort serialPort;

    QList<QString> getDeviceList();

    void connectDevice(int deviceIndex);
    void disconnectDevice();

    void write(std::string txString);
    char read();

    bool isConnected();
    void stopTransmission();

    void startDeviceDiscovery();

signals:
    void scanFinished();
    void scanStarted();

    void connectingDevice();
    void deviceConnected(char id);
    void deviceDisconnected();

    void freeChannel();
    void dataTransmitted();
    void dataReceived();

    void waitForSignal();

    void connectPort();
    void disconnectPort();

    void checkDevice();
    void startHandshake();
    void handshakeFailed();

    void updateScanValue(int value);

private slots:

    void handshake();

    void updateScanStatus();

    void receive(char rxChar);

    void transmit(std::string txString);

    void waitForResponse();

    void connectHandle();
    void disconnectHandle();
    void startPortScanner();
    void checkDeviceHandle();
};

namespace Protocol
{
const std::string gripperopen = "GRIPPEROPEN";
const std::string gripperclose = "GRIPPERCLOSE";
const std::string lighton = "LIGHTON";
const std::string lightoff = "LIGHTOFF";
const std::string lightred = "RED";
const std::string lightgreen = "GREEN";
const std::string lightblue = "BLUE";
const std::string lightyellow = "YELLOW";
const std::string lightmagenta = "MAGENTA";
const std::string lightcyan = "CYAN";
const std::string lightwhite = "WHITE";
const std::string extmotoron = "EXTMOTORON";
const std::string extmotoroff = "EXTMOTOROFF";
};

namespace Colour
{
const std::string red = Protocol::lightred;
const std::string green = Protocol::lightgreen;
const std::string blue = Protocol::lightblue;
const std::string yellow = Protocol::lightyellow;
const std::string magenta = Protocol::lightmagenta;
const std::string cyan = Protocol::lightcyan;
const std::string white = Protocol::lightwhite;
};

namespace ID
{
const std::string move = "M";
const std::string light = "L";
const std::string gripper = "G";
const std::string extMmotor = "E";
const std::string waitFor = "T";
};


class Pos
{
public:
    Pos();
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
};

class Utils
{
public:
    Utils();
    std::string valueToString(float value);
    std::string posToString(Pos position);
    void fillData(std::string &txString, int length=22);
};

class Basic
{
protected:
    char robotid ='1';
    char deviceid = '1';
    UniversalSerialBusDevice& serial;
    Utils utils;
public:
    Basic(UniversalSerialBusDevice& serialport);
    void setID(char robotid = '1', char deviceid = '1');
};

class Move:public Basic
{
public:
    Move(UniversalSerialBusDevice& serialport);
    void ptp(float positionX, float positionY, float positionZ, float speed = 50.0);
    void ptp(Pos position, float speed = 50.0);
};

class Gripper:public Basic
{
public:
    Gripper(UniversalSerialBusDevice& serialport);
    void open();
    void close();
};

class Light:public Basic
{
public:
    Light(UniversalSerialBusDevice& serialport);

    void on(float intensity = 100.0);
    void off();
    void setColour(std::string colour, float intensity = 100.0);
    void setIntensity(float intensity = 100.0);
};

class ExtMotor:public Basic
{
public:
    ExtMotor(UniversalSerialBusDevice& serialport);
    void start(float speed = 255.0);
    void stop();
    void setSpeed(float speed);
};

class Functions :public Basic
{
public:
    Functions(UniversalSerialBusDevice& serialport);
    void waitFor(unsigned long milliseconds);
};

class EasyProtocol
{
private:
    char robotid = '1';
    std::string port = "COM1";

public:
    EasyProtocol();
    ~EasyProtocol();

    UniversalSerialBusDevice connection;
    Functions functions;
    Move move;
    Gripper gripper;
    Light light;
    ExtMotor extmotor;

    std::string getPort();
    char getRobotID();
};

#endif
