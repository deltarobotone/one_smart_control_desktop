#include "workingspace.h"

OneSmartControl::WorkingSpace::WorkingSpace(QObject *parent) : QObject(parent)
{

}

bool OneSmartControl::WorkingSpace::check(const float &xPosition,const float &yPosition,const float &zPosition)
{
    for (int i = 0; i < 4; i++)
    {
        if (zPosition >= levels[i].zmin && zPosition <= levels[i].zmax)
        {
            float radius = 0.0F;

            radius = float(sqrt((pow(double(xPosition), 2.0)) + (pow(double(yPosition), 2.0))));

            if (radius <= levels[i].radius)
            {
                return false;
            }
        }

    }
    return true;
}

void OneSmartControl::WorkingSpace::setLevel(int level, float zmin, float zmax, float radius)
{
    if (level > 0 && level <= 4)
    {
        levels[level - 1].radius = radius;
        levels[level - 1].zmin = zmin;
        levels[level - 1].zmax = zmax;
    }
}
