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
#include "robot.h"

using namespace vex;
using std::string;

// declared functions
string boolToString(bool input);


//  Global Variables

robot Robot;

// ENABLE TESTING MODE BOOL, SET TO FALSE WHEN AT COMPETITION
// true = program calls either auto or manual at start
// false = does nothing, waits for callbacks
bool enableTesting = false;

// is in competition, automatically checked; default is true
// DO NOT CHANGE!!!!!!!!
bool inCompetition = true;

// true = 3 sided auton; false = 2 sided auton
bool auton3Position = false;

string currentTask;
// Every button has its own object and global function, global function is for callbacks

// Back Buttons
void l1_press();
void l2_press();
void r1_press();
void r2_press();
// Arrow buttons
void up_press();
void down_press();
void left_press();
void right_press();
// Letter Buttons
void x_press();
void b_press();
void y_press();
void a_press();

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
    if (auton3Position)
    {
        currentTask = "AUTONOMOUS_3_SIDE";
        // Robot.updateScreen();
        Robot.auto3Side();
    }
    else
    {
        currentTask = "AUTONOMOUS_2_SIDE";
        Robot.auto2Side();
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

void robot::auto3Side()
{
    bool spunRoller = false;

    customTimer driveToRoller_Timer = customTimer(0.5);
    customTimer spinRoller_Timer = customTimer(5); // Theoretical time to spin roller; see README 0.48
    customTimer driveAtEnd_Timer = customTimer(0.5);

    while (true)
    {
        // on frame start, reset inputs
        resetInputs();

        // first task: fire two disks
        /*if (disksLaunched < 2)
        {
            launcherSpeed = 100;
            enableDiskLauncherMotor = true;
            launchDiskBool = true;
            if (disksLaunched >= 1)
            {
                enableIntakeMotor = true;
            }
        }*/

        // second task:
        /*else*/ if (!spunRoller && !diskTimer.done())
        {
            if (!driveToRoller_Timer.done())
            {
                leftDrive = 20;
                rightDrive = 20;
                driveToRoller_Timer.update();
            }
            else if (!spinRoller_Timer.done())
            {
                enableRollerMotor = true;
                rollerMotorVelocity = 100;
                spinRoller_Timer.update();
                if (spinRoller_Timer.done())
                    spunRoller = true;
            }
            else if (!driveAtEnd_Timer.done())
            {
                leftDrive = -10;
                rightDrive = -10;
                driveAtEnd_Timer.update();
            }
        }

        // end of frame, apply to motors
        updateMotors();
        updateScreen();

        wait(20, msec);
    }
}
void robot::auto2Side()
{
    bool spunRoller = false;

    customTimer driveToTurn_Timer = customTimer(1.75);
    customTimer turn90_Timer = customTimer(1.15); // time to turn 90 degrees, based off of 5.2 sec full rotation
    customTimer driveToRoller_Timer = customTimer(1);
    customTimer spinRoller_Timer = customTimer(0.5); // Theoretical time to spin roller; see README 0.48
    customTimer driveAtEnd_Timer = customTimer(0.5);
    customTimer testTimer = customTimer(1);

    while (true)
    {
        resetInputs();

        if (!spunRoller)
        {
            if (!driveToTurn_Timer.done())
            {
                leftDrive = 20;
                rightDrive = 20;
                driveToTurn_Timer.update();
            }
            else if (!turn90_Timer.done())
            {
                leftDrive = 20;
                rightDrive = -10;
                turn90_Timer.update();
            }
            else if (!driveToRoller_Timer.done())
            {
                leftDrive = 20;
                rightDrive = 20;
                driveToRoller_Timer.update();
            }
            else if (!testTimer.done())
            {
                leftDrive = -10;
                rightDrive = -10;
                rollerMotorVelocity = 50;
                enableRollerMotor = true;
                testTimer.update();
            }

            /*else if (!spinRoller_Timer.done())
            {
                enableRollerMotor = true;
                rollerMotorVelocity = 50;
                leftDrive = 7.5;
                rightDrive = 7.5;
                spinRoller_Timer.update();
                if (spinRoller_Timer.done()) spunRoller = true;
            }
            else if (!driveAtEnd_Timer.done())
            {
                leftDrive = -10;
                rightDrive = -10;
                driveAtEnd_Timer.update();
            }*/
        }

        updateMotors();

        wait(20, msec);
    }
}

// gyroRotation class definitions

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

// hi