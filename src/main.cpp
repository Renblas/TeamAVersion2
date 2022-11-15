/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ur mom                                                    */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "robot.h"
#include "util.h"


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

// pre autononmous setup function
void pre_auton(void)
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    buttonCallbackInit();

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


// hi