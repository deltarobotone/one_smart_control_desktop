#ifndef WORKINGSPACE_H
#define WORKINGSPACE_H

#include <QObject>
#include <cmath>

namespace OneSmartControl
{

class Space
{
public:
    float radius = 0.0F;
    float zmin = 0.0F;
    float zmax = 0.0F;
};

class WorkingSpace : public QObject
{
    Q_OBJECT
public:
    explicit WorkingSpace(QObject *parent = nullptr);
    bool check(const float &xPosition,const float &yPosition,const float &zPosition);
    void setLevel(int level, float zmin, float zmax, float radius);

private:
    Space levels[4];
};

} // OneSmartControl

#endif // WORKINGSPACE_H
