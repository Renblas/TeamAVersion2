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
 *   ----------  REFERENCE  ---------
 *
 *   Gear Ratios:
 *       red, 100 rpm, ratio6_1
 *       green, 200 rpm, ratio18_1
 *       blue, 600 rpm, ratio36_1
 *       special black, max 3600 rpm, just set as blue but when need rpm multiply by 6
 *
 *   Controls:
 *       ---- Buttons on Back ----
 *       L1 - emergency untoggles intake and while held reverses intake, aka emergency clear
 *       L2 - Toggle, turns on intake and sucks disks (pun intended)
 *       R1 - Toggle, turns on disk launcher at current speed (default 85%)
 *       R2 -
 *
 *       ---- Arrow Pad ----
 *       Up - Roller Motor Clockwise
 *       Down - Roller Motor Counter-Clockwise
 *       Left - Increase Disk Launcher Speed
 *       Right - Decrease Ddisk Launcher Speed
 *
 *       ---- Letter Pad ----
 *       X (top) - Launch disk if criteria are met
 *       B (bottom) -
 *       Y (left) -
 *       A (right) - Launch Endgame string thing
 *
 *       ---- Axis ----
 *       Axis 4 (Left Knob X-Direction) -
 *       Axis 3 (Left Knob Y-Direction) - Left Drivetrain Motors fwd/back
 *       Axis 1 (Right Knob X-Direction) -
 *       Axis 2 (Right Knob Y-Direction) - Right Drivetrain Motors fwd/back
 *
 */

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
motor intakeMotor = motor(PORT10, ratio18_1, false);
// Roller Motor
motor rollerMotor = motor(PORT11, ratio18_1, false);
// Roller Motor
motor launcherMotor = motor(PORT13, ratio36_1, false);
// EndgameMotor
motor endgameMotor = motor(PORT12, ratio6_1, false);

// Pneumatics
// triport ThreeWirePort = vex::triport(PORT22);
// digital_out launcherPneumatics = digital_out(Brain.ThreeWirePort.A);

/*
 *    ---- END VEXCODE CONFIGURED DEVICES ----
 */

//  Main Robot Class
class robot
{
public:
    // ----- Variables -----

    // Drivetrain
    int leftDrive = 0;
    int rightDrive = 0;
    // bool straightDrive = false;
    //  Roller & Intake
    bool enableRollerMotor = false;
    bool rollerMotorReverse = false;
    bool enableIntakeMotor = false;
    bool intakeMotorReverse = false;
    // Launcher
    bool increaseLauncherSpeed = false;
    bool decreaseLauncherSpeed = false;
    float launcherSpeed_adjustPerSecond = 50;
    float launcherSpeed = 85;
    bool enableDiskLauncherMotor = false;
    bool launchDiskBool = false;
    // Endgame
    bool triggerEndgame = false;

    // ----- Functions -----

    // constructor
    robot();
    // general function for all of user control stuff
    void updateUserControl();
    // gets input from button objects / axis
    void getUserInput();
    // Process axis for reasons
    int processAxis(int input, int cutoff);
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
    // screen not currently used
    // void updateScreen();
    // update controller screen, not currently used
    // void updateControllerScreen();
};

// custom button class
class customButton
{
public:
    // ----- Variables -----
    bool isToggle = false;
    bool rawPressed = false;
    bool pressed = true;

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

/*
 *   Global Variables
 */

competition Competition;
controller Controller;
robot Robot;

// ENABLE TESTING MODE BOOL, SET TO FALSE WHEN AT COMPETITION
// true = program calls either auto or manual at start
// false = does nothing, waits for callbacks
bool enableTesting = true;

// is in competition
bool inCompetition = true;

// Every button has its own object and global function, global function is for callbacks

// Back Buttons
void l1_press();
customButton button_l1 = customButton(false, "l1");
void l2_press();
customButton button_l2 = customButton(true, "l2");
void r1_press();
customButton button_r1 = customButton(true, "r1");
void r2_press();
customButton button_r2 = customButton(false, "r2");
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
    Controller.ButtonR1.pressed(r1_press);
    // Controller.ButtonR2.pressed(r2_press);
    Controller.ButtonUp.pressed(up_press);
    Controller.ButtonDown.pressed(down_press);
    Controller.ButtonLeft.pressed(left_press);
    Controller.ButtonRight.pressed(right_press);
    Controller.ButtonX.pressed(x_press);
    // Controller.ButtonB.pressed(b_press);
    // Controller.ButtonY.pressed(y_press);
    Controller.ButtonA.pressed(a_press);

    // is in competition
    if (!Competition.isCompetitionSwitch() && !Competition.isFieldControl())
    {
        inCompetition = false;
    }
}

void autonomous(void)
{
}

void usercontrol(void)
{
    while (1)
    {
        Robot.updateUserControl();

        wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
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
void robot::updateUserControl()
{
    Robot.getUserInput();
    Robot.updateDriveMotors();
    Robot.updateLauncherMotor();
    Robot.updateIntakeMotor();
    Robot.updateRollerMotor();

    if (/* condition */ false)
    {
        // do endgame
    }
}
void robot::updateDriveMotors()
{
    leftMotorGroup.setVelocity(leftDrive, percent);
    rightMotorGroup.setVelocity(rightDrive, percent);

    leftMotorGroup.spin(fwd);
    rightMotorGroup.spin(fwd);
}
void robot::adjustLauncherMotor()
{
    if (increaseLauncherSpeed)
    {
        launcherSpeed += launcherSpeed_adjustPerSecond / 50;
    }
    if (decreaseLauncherSpeed)
    {
        launcherSpeed -= launcherSpeed_adjustPerSecond / 50;
    }
}
void robot::updateLauncherMotor()
{
    adjustLauncherMotor();
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
        rollerMotor.setVelocity(100, percent);
    }
    else if (rollerMotorReverse)
    {
        rollerMotor.setVelocity(-100, percent);
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
void robot::getUserInput()
{
    // Arrow Button Input
    enableRollerMotor = button_up.pressed;
    rollerMotorReverse = button_down.pressed;
    increaseLauncherSpeed = button_left.pressed;
    decreaseLauncherSpeed = button_right.pressed;
    // Back Button Input
    enableIntakeMotor = button_l2.pressed;
    intakeMotorReverse = button_l1.pressed;
    enableDiskLauncherMotor = button_r1.pressed;

    // Letter Buttons
    launchDiskBool = button_x.pressed;
    triggerEndgame = button_a.pressed;

    // Axis Input
    leftDrive = processAxis(Controller.Axis3.value(), 5);
    rightDrive = processAxis(Controller.Axis2.value(), 5);

    // check buttons
    button_l1.isReleased();
    button_l2.isReleased();
    button_r1.isReleased();
    button_r2.isReleased();
    button_up.isReleased();
    button_down.isReleased();
    button_left.isReleased();
    button_right.isReleased();
    // button_x.isReleased();
    // button_y.isReleased();
    button_a.isReleased();
    button_b.isReleased();
}
int robot::processAxis(int input, int cutoff)
{
    float result = input;
    if (result <= cutoff && result >= -cutoff)
        result = 0;
    return result;
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

// hi