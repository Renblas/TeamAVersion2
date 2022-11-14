// Custom gyro class declaration

class gyroRotation
{
public:
    float inTurn = false;
    float startRotation = 0;
    float endRotation = 0;
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
    startRotation = GyroA.value(degrees);
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
    if (GyroA.value(degrees) - startRotation >= endRotation)
    {
        return true;
    }
    else
    {
        return false;
    }
}