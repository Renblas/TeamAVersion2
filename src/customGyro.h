#include "robot.h"

// Custom gyro class declaration

class gyroRotation
{
public:
    float inTurn = false;
    float startRotation;
    float endRotation;
    bool finished = false;

    gyroRotation(float endRotation_f);
    void update();
    bool isFinished();
};


/*
 * Custom Gyro Class Definitions
 */


gyroRotation::gyroRotation(float endRotation_f)
{
    startRotation = GyroB.value(degrees);
    endRotation = endRotation_f;
}
void gyroRotation::update()
{
    if (!isFinished())
    {
        Robot.leftDrive = Robot.gyroRotateSpeed;
        Robot.rightDrive = -Robot.gyroRotateSpeed;
    }
    else
    {
    }
}
bool gyroRotation::isFinished()
{
    if (GyroB.value(degrees) - startRotation >= endRotation)
    {
        return true;
    }
    else
    {
        return false;
    }
}

