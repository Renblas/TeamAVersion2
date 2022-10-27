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

/*
*   ----------  REFERENCE  ---------
*   
*   Gear Ratios:
*       red, 100 rpm, ratio6_1
*       green, 200 rpm, ratio18_1
*       blue, 600 rpm, ratio36_1
*       special black, max 3600 rpm, just set as blue but when need rpm multiply by 6
*
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
motor intakeMotor = motor(PORT10, /*GREEN?*/ ratio18_1, false);
// Roller Motor
motor rollerMotor = motor(PORT11, /*GREEN?*/ ratio18_1, false);
// Roller Motor
motor launcherMotor = motor(PORT13, ratio36_1, false);
// EndgameMotor
motor endgameMotor = motor(PORT12, ratio6_1, false);

// Pneumatics
digital_out launcherPneumatics;

/*
 *    ---- END VEXCODE CONFIGURED DEVICES ----
 */

//  Main Robot Class
class robot
{
public:
    // variables
    int leftDrive;
    int rightDrive;
    bool totalDrive_Bool;

    // functions
    robot();
    void updateDriveMotors();
    void updateRollerMotor();
    void updateLauncher();
    void updateScreen();
    void getUserInput();
    int processAxis(int input, int cutoff);
};

// custom button class
class customButton
{
public:
    // variables
    bool isToggle = false;
    bool rawPressed = false;
    bool pressed = true;

    std::string buttonName;

    // function
    customButton(bool toggle, std::string buttonName);
    void onPressInput();
    void checkRelease();
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

// buttons
void l1_press();
customButton button_l1 = customButton(false, "l1");
void l2_press();
customButton button_l2 = customButton(false, "l2");
void r1_press();
customButton button_r1 = customButton(false, "r1");
void r2_press();
customButton button_r2 = customButton(false, "r2");

// pre autononmous setup function
void pre_auton(void)
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // set keyboard callbacks
    Controller.ButtonL1.pressed(l1_press);
    Controller.ButtonL1.pressed(l2_press);
    Controller.ButtonL1.pressed(r1_press);
    Controller.ButtonL1.pressed(r2_press);

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
    // User control code here, inside the loop
    while (1)
    {

        Robot.getUserInput();
        Robot.updateDriveMotors();

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

void robot::updateDriveMotors()
{
    leftMotorGroup.setVelocity(leftDrive, percent);
    rightMotorGroup.setVelocity(rightDrive, percent);

    leftMotorGroup.spin(fwd);
    rightMotorGroup.spin(fwd);
}

void robot::updateScreen()
{
}

void robot::getUserInput()
{
    leftDrive = processAxis(Controller.Axis3.value(), 5);
    rightDrive = processAxis(Controller.Axis2.value(), 5);

    button_l1.isReleased();
    button_l2.isReleased();
    button_r1.isReleased();
    button_r2.isReleased();
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
    {
        return true;
    }
    else if (buttonName == "l2" && !Controller.ButtonL2.pressing())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void customButton::checkRelease() {
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
        pressed != pressed;
    } else {
        pressed = rawPressed;
    }
}

void l1_press() {
    button_l1.onPressInput();
}
void l2_press() {
    button_l2.onPressInput();
}
void r1_press() {
    button_r1.onPressInput();
}
void r2_press() {
    button_r2.onPressInput();
}

// hi