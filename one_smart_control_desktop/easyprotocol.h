#ifndef EASYPROTOCOL
#define EASYPROTOCOL

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QIODevice>
#include <QThread>
#include <iostream>
#include <cmath>

class SerialPort
{
private:
    QSerialPort *serialPortHandle;
    bool connected;
public:
    SerialPort();
    ~SerialPort();
    void open(std::string port = "COM1", int baudrate = 9600);
    void close();
    void write(std::string txString, int lenght);
    int read(char &buffer, int length);
    void clear();
    bool isOpen();
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
    bool info = false;
    SerialPort& serial;
    Utils utils;
    bool connected = false;
    void waitForRobot();
public:
    Basic(SerialPort& serialport);
    void printInfo(bool status);
    void setID(char robotid = '1', char deviceid = '1');
    void setSerialStatus(bool status);
};

class Move:public Basic
{
public:
    Move(SerialPort& serialport);
    void ptp(float positionX, float positionY, float positionZ, float speed = 50.0);
    void ptp(Pos position, float speed = 50.0);
};

class Gripper:public Basic
{
public:
    Gripper(SerialPort& serialport);
    void open();
    void close();
};

class Light:public Basic
{
public:
    Light(SerialPort& serialport);

    void on(float intensity = 100.0);
    void off();
    void setColour(std::string colour, float intensity = 100.0);
    void setIntensity(float intensity = 100.0);
};

class ExtMotor:public Basic
{
public:
    ExtMotor(SerialPort& serialport);
    void start(float speed = 255.0);
    void stop();
    void setSpeed(float speed);
};

class Functions :public Basic
{
public:
    Functions(SerialPort& serialport);
    void waitFor(unsigned long milliseconds);
};

class EasyProtocol
{
private:
    int baudrate = 9600;
    char robotid = '1';
    char deviceid = '1';
    std::string port = "COM1";
    bool connected = false;
    bool info = false;
    bool setCommunication();
    void findPorts(int baudrate, std::string& port, char& robotid);
public:
    EasyProtocol();
    ~EasyProtocol();
    SerialPort connection;
    Functions functions;
    Move move;
    Gripper gripper;
    Light light;
    ExtMotor extmotor;
    void findRobot();
    void setPort(std::string port, int baudrate = 9600);
    std::string getPort();
    void start();
    void start(char robotid, char deviceid);
    void stop();
    char getRobotID();
    char getDeviceID();
    void setRobotID(char id);
    void setDeviceID(char id);
    bool isConnected();
};

#endif
