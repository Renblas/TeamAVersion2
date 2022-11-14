
#include "customButton.h"
#include "customTimer.h"
#include "customGyro.h"


//  Main Robot Class
class robot
{
public:
    // ----- Variables -----

    // Drivetrain
    float leftDrive = 0;
    float rightDrive = 0;
    float gyroRotateSpeed = 20;
    // bool straightDrive = false;
    //  Roller & Intake
    bool enableRollerMotor = false;
    bool rollerMotorReverse = false;
    float defaultRollerMotorVelocity = 50;
    float rollerMotorVelocity = defaultRollerMotorVelocity;
    bool enableIntakeMotor = false;
    bool intakeMotorReverse = false;
    // Launcher Motor
    bool increaseLauncherSpeed = false;
    bool decreaseLauncherSpeed = false;
    float launcherSpeed_adjustPerSecond = 50;
    float launcherSpeed_default = 70;
    float launcherSpeed = launcherSpeed_default;
    bool enableDiskLauncherMotor = false;
    // fire disk stuff
    float pistonEnabledTime = 0.25;
    float pistonRetractTime = 1;
    customTimer diskTimer = customTimer(pistonEnabledTime + pistonRetractTime);
    float launcherMotorMinSpeed = 0.9;
    bool launchDiskBool = false;
    int disksLaunched = 0;
    // Endgame
    bool enableEndgame = false;
    bool enableEndgameReverse = false;
    // Screen
    bool enableImage = false;
    float screenRefreshRate = 1 / 30;
    customTimer screenTimer = customTimer(screenRefreshRate);

    // ----- Functions -----

    // constructor
    robot();
    // reset all variables to default
    void resetToDefault();
    // reset control inputs to default
    void resetInputs();
    // general function for all of user control stuff
    void updateMotors();
    // gets input from button objects / axis
    void getUserInput();
    // Process axis for reasons
    int processAxis(int input, int cutoff);
    // firing checklist for firing a disk
    void firingProtocol();
    // applies input to drivechain motors
    void updateDriveMotors();
    // applies input to roller motor
    void updateRollerMotor();
    // applies input to intake motor
    void updateIntakeMotor();
    // makes adjustments to Launcher motor speed, automatically called by updateLauncherMotor()
    void adjustLauncherMotor();
    // applies input to launcher motor
    void updateLauncherMotor();
    // Trigger Endgame
    void updateEndgameLauncher();
    // screen not currently used
    void updateScreen();
    // prints string to screen at position, clears line beforehand
    void printScreenAt(string text, int x, int y);
    // update controller screen, not currently used
    // void updateControllerScreen();

    // ----- Autonomous -----
    // assume start on 3-side; gets roller and launch 2 disk
    void auto3Side();
    // assume start on 2-side, perpendicular to roller; gets roller and launch 2 disk
    void auto2Side();
};

/*
 *   Robot Class Definitions
 */

// Constructor definition outside the class
robot::robot()
{
}
void robot::resetToDefault()
{
    resetInputs();
    launcherSpeed = launcherSpeed_default;
    rollerMotorVelocity = defaultRollerMotorVelocity;
}
void robot::resetInputs()
{
    leftDrive = 0;
    rightDrive = 0;

    enableDiskLauncherMotor = false;
    launchDiskBool = false;

    enableIntakeMotor = false;
    intakeMotorReverse = false;

    enableRollerMotor = false;
    rollerMotorReverse = false;

    enableEndgame = false;
    enableEndgameReverse = false;
}
void robot::updateMotors()
{
    updateDriveMotors();
    updateIntakeMotor();
    updateRollerMotor();
    updateLauncherMotor();
    firingProtocol();
    updateEndgameLauncher();
}
void robot::getUserInput()
{
    // Arrow Button Input
    enableRollerMotor = button_a.pressed;
    rollerMotorReverse = button_b.pressed;
    // increaseLauncherSpeed = button_left.pressed;
    // decreaseLauncherSpeed = button_right.pressed;
    //  Back Button Input
    enableIntakeMotor = button_l2.pressed;
    intakeMotorReverse = button_l1.pressed;
    enableDiskLauncherMotor = button_r2.pressed;

    // Letter Buttons
    launchDiskBool = button_y.pressed;
    enableEndgame = button_up.pressed;
    enableEndgameReverse = button_down.pressed;

    if (intakeMotorReverse && enableIntakeMotor)
    {
        enableIntakeMotor = false;
        button_l2.pressed = false;
    }

    // Axis Input
    leftDrive = processAxis(Controller.Axis3.position(), 5);
    rightDrive = processAxis(Controller.Axis2.position(), 5);

    // check buttons
    button_l1.checkRelease();
    button_l2.checkRelease();
    button_r1.checkRelease();
    button_r2.checkRelease();
    button_up.checkRelease();
    button_down.checkRelease();
    // button_left.checkRelease();
    // button_right.checkRelease();
    // button_x.checkRelease();
    button_y.checkRelease();
    button_a.checkRelease();
    button_b.checkRelease();
}
int robot::processAxis(int input, int cutoff)
{
    float result = input;
    if (result <= cutoff && result >= -cutoff)
        result = 0;
    return result;
}
void robot::firingProtocol()
{
    // if diskTimer is at 0, proceed; else count down timer
    if (diskTimer.done())
    {
        printScreenAt("timer done", 1, 5);
        // if launcher motor is enabled AND the current velocity is X percent of set speed, proceed
        if (enableDiskLauncherMotor &&
            launcherMotor.velocity(percent) >= launcherMotorMinSpeed * launcherSpeed)
        {
            printScreenAt("Launcher Good", 1, 6);
            // if you actually want to fire disk, proceed
            if (launchDiskBool)
            {
                printScreenAt("FIRE ZE FLAMMENWERFER", 1, 7);
                launcherPneumatics.set(true);
                disksLaunched += 1;
                diskTimer.reset();
            }
        }
    }
    diskTimer.update();

    // if timer is less than time needed to extend, retract
    if (diskTimer.time <= (diskTimer.maxTime - pistonEnabledTime))
    {
        launcherPneumatics.set(false);
    }
}
void robot::updateDriveMotors()
{
    leftMotorGroup.setVelocity(leftDrive, percent);
    rightMotorGroup.setVelocity(rightDrive, percent);

    leftMotorGroup.spin(fwd);
    rightMotorGroup.spin(fwd);
}
/*void robot::adjustLauncherMotor()
{
    if (increaseLauncherSpeed)
    {
        launcherSpeed += launcherSpeed_adjustPerSecond / 50;
    }
    if (decreaseLauncherSpeed)
    {
        launcherSpeed -= launcherSpeed_adjustPerSecond / 50;
    }
}*/
void robot::updateLauncherMotor()
{
    // adjustLauncherMotor();
    if (enableDiskLauncherMotor)
    {
        launcherMotor.setVelocity(launcherSpeed, percent);
    }
    else
    {
        launcherMotor.setVelocity(0, percent);
    }
    launcherMotor.spin(fwd);
}
void robot::updateRollerMotor()
{
    if (enableRollerMotor)
    {
        rollerMotor.setVelocity(rollerMotorVelocity, percent);
    }
    else if (rollerMotorReverse)
    {
        rollerMotor.setVelocity(-rollerMotorVelocity, percent);
    }
    else
    {
        rollerMotor.setVelocity(0, percent);
    }
    rollerMotor.spin(fwd);
}
void robot::updateIntakeMotor()
{
    if (enableIntakeMotor)
    {
        intakeMotor.setVelocity(100, percent);
    }
    else if (intakeMotorReverse)
    {
        intakeMotor.setVelocity(-100, percent);
    }
    else
    {
        intakeMotor.setVelocity(0, percent);
    }
    intakeMotor.spin(fwd);
}
void robot::updateEndgameLauncher()
{
    if (enableEndgame)
    {
        endgameMotor.setVelocity(100, percent);
    }
    else if (enableEndgameReverse)
    {
        endgameMotor.setVelocity(-100, percent);
    }
    else
    {
        endgameMotor.setVelocity(0, percent);
    }
    endgameMotor.spin(fwd);
}
void robot::updateScreen()
{
    screenTimer.update();
    if (screenTimer.done())
    {
        printScreenAt("testing enabled... " + boolToString(enableTesting), 1, 1);
        printScreenAt("running... " + currentTask, 1, 2);

        Brain.Screen.clearLine(3);
        Brain.Screen.setCursor(3, 1);
        Brain.Screen.print(diskTimer.time);

        Brain.Screen.clearLine(4);
        Brain.Screen.setCursor(4, 1);
        Brain.Screen.print(diskTimer.maxTime - pistonEnabledTime);

        screenTimer.reset();
    }
}
void robot::printScreenAt(string text, int x, int y)
{
    Brain.Screen.clearLine(y);
    Brain.Screen.setCursor(y, x);
    Brain.Screen.print(text.c_str());
}