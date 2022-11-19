/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ur mom                                                    */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <string>

using namespace vex;
using std::string;

/*
 *    ---- START VEXCODE CONFIGURED DEVICES ----
 */

// Drive Motors
motor frontLeftMotor = motor(PORT1, ratio18_1, true);
motor backLeftMotor = motor(PORT2, ratio18_1, true);
motor frontRightMotor = motor(PORT9, ratio18_1, false);
motor backRightMotor = motor(PORT8, ratio18_1, false);
// Drive Motor groups
motor_group leftMotorGroup = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightMotorGroup = motor_group(frontRightMotor, backRightMotor);

// Intake Motor
motor intakeMotor = motor(PORT10, ratio6_1, false);
// Roller Motor
motor rollerMotor = motor(PORT7, ratio6_1, false);
// Roller Motor
motor launcherMotor = motor(PORT3, ratio36_1, true);
// EndgameMotor
motor endgameMotor = motor(PORT4, ratio6_1, false);

triport ThreeWirePort = vex::triport(vex::PORT22);
digital_out launcherPneumatics = digital_out(ThreeWirePort.A);
//digital_out endGamePneumatics = digital_out(ThreeWirePort.C);
gyro Gyro = gyro(ThreeWirePort.B);

/*
 *    ---- END VEXCODE CONFIGURED DEVICES ----
 */

class customTimer
{
public:
    // variables
    float time = 0;
    float maxTime = 0;
    // functions
    customTimer(float max);
    void update();
    void reset();
    bool done();
};

class gyroRotation
{
public:
    float inTurn = false;
    float startRotation = 0;
    float endRotation = 0;
    bool finished = false;
    bool isLeft;

    gyroRotation(float endRotation_f, bool dir);
    void update();
    bool isFinished();
};

//  Main Robot Class
class robot
{
public:
    // ----- Variables -----

    // Drivetrain
    float leftDrive = 0;
    float rightDrive = 0;
    float gyroRotateSpeed = 10;
    // bool straightDrive = false;
    //  Roller & Intake
    bool enableRollerMotor = false;
    bool rollerMotorReverse = false;
    float defaultRollerMotorVelocity = 90;
    float rollerMotorVelocity = defaultRollerMotorVelocity;
    bool enableIntakeMotor = false;
    bool intakeMotorReverse = false;
    // Launcher Motor
    bool increaseLauncherSpeed = false;
    bool decreaseLauncherSpeed = false;
    float launcherSpeed_adjustPerSecond = 50;
    float launcherSpeed_default = 90;
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
    // beta 3 shooter engame
    bool endGameTriggered = false;
    customTimer endGamePiston_Timer = customTimer(1);

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
    void autoDebug();
};

// custom button class
class customButton
{
public:
    // ----- Variables -----
    bool isToggle = false;
    bool rawPressed = false;
    bool pressed = false;

    std::string buttonName;

    // ----- Functions -----

    // constructor
    customButton(bool toggle, std::string buttonName);
    // function called when callback occurs
    void onPressInput();
    // called once per frame, holds logic for if it is realeased
    void checkRelease();
    // called by above, is master list for determining if button is being pressed
    bool isReleased();
};

// declared functions
string boolToString(bool input);
float absValue(float input);

/*
 *   Global Variables
 */

competition Competition;
controller Controller;
robot Robot;

// ENABLE TESTING MODE BOOL, SET TO FALSE WHEN AT COMPETITION
// true = program calls either auto or manual at start
// false = does nothing, waits for callbacks
bool enableTesting = false;

// is in competition, automatically checked; default is true
// DO NOT CHANGE!!!!!!!!
bool inCompetition = true;

// "3side" = 3 sided auton; "2side" = 2 sided auton; "debug" = debug auton
string autonFuncToRun = "2side";

string currentTask;
// Every button has its own object and global function, global function is for callbacks

// Back Buttons
void l1_press();
customButton button_l1 = customButton(false, "l1");
void l2_press();
customButton button_l2 = customButton(true, "l2");
void r1_press();
customButton button_r1 = customButton(false, "r1");
void r2_press();
customButton button_r2 = customButton(true, "r2");
// Arrow buttons
void up_press();
customButton button_up = customButton(false, "up");
void down_press();
customButton button_down = customButton(false, "down");
void left_press();
customButton button_left = customButton(false, "left");
void right_press();
customButton button_right = customButton(false, "right");
// Letter Buttons
void x_press();
customButton button_x = customButton(false, "x");
void b_press();
customButton button_b = customButton(false, "b");
void y_press();
customButton button_y = customButton(false, "y");
void a_press();
customButton button_a = customButton(false, "a");

// pre autononmous setup function
void pre_auton(void)
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // set keyboard callbacks
    Controller.ButtonL1.pressed(l1_press);
    Controller.ButtonL2.pressed(l2_press);
    // Controller.ButtonR1.pressed(r1_press);
    Controller.ButtonR2.pressed(r2_press);
    Controller.ButtonUp.pressed(up_press);
    Controller.ButtonDown.pressed(down_press);
    // Controller.ButtonLeft.pressed(left_press);
    // Controller.ButtonRight.pressed(right_press);
    // Controller.ButtonX.pressed(x_press);
    Controller.ButtonB.pressed(b_press);
    Controller.ButtonY.pressed(y_press);
    Controller.ButtonA.pressed(a_press);

    // is in competition
    if (!Competition.isCompetitionSwitch() && !Competition.isFieldControl())
    {
        inCompetition = false;
    }
}

void autonomous(void)
{
    Gyro.startCalibration();
    while (Gyro.isCalibrating())
    {
        wait(20, msec);
    }

    if (autonFuncToRun == "3side")
    {
        currentTask = "AUTONOMOUS_3_SIDE";
        // Robot.updateScreen();
        Robot.auto3Side();
    }
    else if (autonFuncToRun == "2side")
    {
        currentTask = "AUTONOMOUS_2_SIDE";
        Brain.Screen.print("hi");
        Robot.auto2Side();
    }
    else if (autonFuncToRun == "debug")
    {
        Robot.autoDebug();
    }
}

void usercontrol(void)
{
    Robot.resetToDefault();
    currentTask = "USER_CONTROL";

    while (1)
    {
        Robot.getUserInput();
        Robot.updateMotors();
        Robot.updateScreen();

        wait(20, msec);
    }
}

/*
 * Main will set up the competition functions and callbacks.
 */
int main()
{
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    Robot.printScreenAt("testing enabled... " + boolToString(enableTesting), 1, 1);

    // call manual if debug and testing
    if (enableTesting && !inCompetition)
    {
        usercontrol();
    }

    // Prevent main from exiting with an infinite loop.
    while (true)
    {
        wait(100, msec);
    }
}

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
        intakeMotor.setVelocity(75, percent);
    }
    else if (intakeMotorReverse)
    {
        intakeMotor.setVelocity(-75, percent);
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
/*void robot::updateEndgameLauncher()
{
    if (enableEndgame)
    {
        if (!endGameTriggered)
        {
            endGamePneumatics.set(true);
            endGameTriggered = true;
        }
    }

    if (endGameTriggered && !endGamePiston_Timer.done())
    {
        endGamePiston_Timer.update();
    }
    else if (endGamePiston_Timer.done())
    {
        endGamePneumatics.set(false);
    }
}*/
void robot::auto3Side()
{
    customTimer driveToRoller_Timer = customTimer(1);
    customTimer spinRoller_Timer = customTimer(0.5);
    customTimer driveFromRoller_Timer = customTimer(1);

    gyroRotation turnToLowGoal = gyroRotation(90, false);
    bool turnComplete = false;

    while (true)
    {
        // on frame start, reset inputs
        resetInputs();

        if (!driveToRoller_Timer.done())
        {
            leftDrive = 12;
            rightDrive = 12;

            driveToRoller_Timer.update();
        }
        else if (!spinRoller_Timer.done())
        {
            enableRollerMotor = true;
            rollerMotorVelocity = 25;

            leftDrive = 5;
            rightDrive = 5;

            spinRoller_Timer.update();
        }
        else if (!driveFromRoller_Timer.done())
        {
            leftDrive = -10;
            rightDrive = -10;

            driveFromRoller_Timer.update();
        }
        else if (!turnComplete)
        {
            turnToLowGoal.update();
            if (turnToLowGoal.isFinished())
            {
                turnComplete = true;
            }
        }
        else if (disksLaunched < 2 || !diskTimer.done())
        {
            launcherSpeed = 60;
            enableDiskLauncherMotor = true;
            launchDiskBool = true;
        }

        // end of frame, apply to motors
        updateMotors();
        updateScreen();

        wait(20, msec);
    }
}
void robot::auto2Side()
{

    customTimer driveBack_Timer = customTimer(1);

    gyroRotation turnToRoller = gyroRotation(90, true);
    bool turnToRoller_done = false;

    customTimer moveToRoller = customTimer(1.5);
    customTimer spinRoller_Timer = customTimer(0.5);
    customTimer leaveRoller_Timer = customTimer(0.25);

    while (true)
    {
        resetInputs();

        if (disksLaunched < 2 || !diskTimer.done())
        {
            launcherSpeed = 50;
            enableDiskLauncherMotor = true;
            launchDiskBool = true;
        }
        else if (!driveBack_Timer.done())
        {
            leftDrive = 30;
            rightDrive = 30;

            driveBack_Timer.update();
        }
        else if (!turnToRoller_done)
        {
            turnToRoller.update();

            if (turnToRoller.isFinished())
            {
                turnToRoller_done = true;
            }
        }
        else if (!moveToRoller.done())
        {
            leftDrive = 10;
            rightDrive = 10;

            moveToRoller.update();
        }
        else if (!spinRoller_Timer.done())
        {
            enableRollerMotor = true;
            rollerMotorVelocity = 50;

            leftDrive = 5;
            rightDrive = 5;

            spinRoller_Timer.update();
        }
        else if (!leaveRoller_Timer.done())
        {
            leftDrive = -5;
            rightDrive = -5;

            leaveRoller_Timer.done();
        }

        updateMotors();

        wait(20, msec);
    }
}
void robot::autoDebug()
{

    gyroRotation turn90 = gyroRotation(90, false);

    while (true)
    {
        resetInputs();

        turn90.update();

        Robot.updateMotors();
        wait(20, msec);
    }
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

/*
 *   Custom Timer class definitions
 */
customTimer::customTimer(float max)
{
    maxTime = max;
    time += maxTime;
}
void customTimer::update()
{
    if (time > 0)
    {
        time -= ((float)20 / (float)1000);
    }
}
bool customTimer::done()
{
    if (time <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void customTimer::reset()
{
    time += maxTime;
}

/*
 *   Button class definitions
 */

customButton::customButton(bool toggle, string buttonName_f)
{
    isToggle = toggle;
    buttonName = buttonName_f;
}
bool customButton::isReleased()
{
    if (buttonName == "l1" && !Controller.ButtonL1.pressing())
        return true;
    else if (buttonName == "l2" && !Controller.ButtonL2.pressing())
        return true;
    else if (buttonName == "r1" && !Controller.ButtonR1.pressing())
        return true;
    else if (buttonName == "r2" && !Controller.ButtonR2.pressing())
        return true;
    else if (buttonName == "up" && !Controller.ButtonUp.pressing())
        return true;
    else if (buttonName == "down" && !Controller.ButtonDown.pressing())
        return true;
    else if (buttonName == "left" && !Controller.ButtonLeft.pressing())
        return true;
    else if (buttonName == "right" && !Controller.ButtonRight.pressing())
        return true;
    else if (buttonName == "x" && !Controller.ButtonX.pressing())
        return true;
    else if (buttonName == "y" && !Controller.ButtonY.pressing())
        return true;
    else if (buttonName == "a" && !Controller.ButtonA.pressing())
        return true;
    else if (buttonName == "b" && !Controller.ButtonB.pressing())
        return true;
    else
        return false;
}
void customButton::checkRelease()
{
    if (isReleased())
    {
        rawPressed = false;

        if (!isToggle)
        {
            pressed = rawPressed;
        }
    }
}
void customButton::onPressInput()
{
    Brain.Screen.printAt(0, 1, "Pressed");
    rawPressed = true;

    if (isToggle)
    {
        pressed = !pressed;
    }
    else
    {
        pressed = rawPressed;
    }
}

// gyroRotation class definitions

gyroRotation::gyroRotation(float endRotation_f, bool dir)
{
    endRotation = endRotation_f;
    isLeft = dir;
}
void gyroRotation::update()
{
    float curRotation = Gyro.rotation(degrees);

    if (!isFinished())
    {
        if (endRotation - curRotation <= absValue(360 - endRotation) - curRotation)
        {
            Robot.leftDrive = Robot.gyroRotateSpeed;
            Robot.rightDrive = -Robot.gyroRotateSpeed;
        }
        else
        {
            Robot.leftDrive = -Robot.gyroRotateSpeed;
            Robot.rightDrive = Robot.gyroRotateSpeed;
        }

        Brain.Screen.clearLine(6);
        Brain.Screen.setCursor(6, 1);
        Brain.Screen.print(Gyro.rotation(degrees));
    }
    else
    {
    }
}
bool gyroRotation::isFinished()
{
    if (Gyro.rotation(degrees) >= (endRotation - 4) && Gyro.rotation(degrees) <= (endRotation + 4))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Button Callback Functions

void l1_press()
{
    button_l1.onPressInput();
}
void l2_press()
{
    button_l2.onPressInput();
}
void r1_press()
{
    button_r1.onPressInput();
}
void r2_press()
{
    button_r2.onPressInput();
}
void up_press()
{
    button_up.onPressInput();
}
void down_press()
{
    button_down.onPressInput();
}
void left_press()
{
    button_left.onPressInput();
}
void right_press()
{
    button_right.onPressInput();
}
void x_press()
{
    button_x.onPressInput();
}
void b_press()
{
    button_b.onPressInput();
}
void y_press()
{
    button_y.onPressInput();
}
void a_press()
{
    button_a.onPressInput();
}

// Util Functions

string boolToString(bool input)
{
    string a;
    if (input)
    {
        a = "TRUE";
    }
    else
    {
        a = "FALSE";
    }
    return a;
}

float absValue(float input)
{
    if (input < 0)
    {
        input *= -1;
    }
    return input;
}
// hi