/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ur mom                                                    */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// ---- START VEXCODE CONFIGURED DEVICES ----

motor frontLeftMotor = motor(PORT1, ratio18_1, true);
motor backLeftMotor = motor(PORT2, ratio18_1, true);
motor frontRightMotor = motor(PORT9, ratio18_1, false);
motor backRightMotor = motor(PORT8, ratio18_1, false);

motor_group leftMotorGroup = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightMotorGroup = motor_group(frontRightMotor, backRightMotor);


// ---- END VEXCODE CONFIGURED DEVICES ----

// Main Robot Class
class robot {
  public:
    // variables
    int leftDrive;
    int rightDrive;
    bool totalDrive_Bool;

    

    // functions   
    robot();
    void updateMotors();
    void updateScreen();
    void getUserInput();
    int processAxis(int input, int cutoff);
};

// custom button class
class customButton {
    public:
        // variables
        bool isToggle;

        // function
        customButton(bool toggle);


};

// A global instance of competition
competition Competition;
controller Controller;
robot Robot;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}


void autonomous(void) {
  
}


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    
    Robot.getUserInput();
    Robot.updateMotors();



    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

/*
* Main will set up the competition functions and callbacks.
*/
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}


/*
*   Robot Class Definitions
*/

// Constructor definition outside the class
robot::robot() {
  
}

void robot::updateMotors() {
    leftMotorGroup.setVelocity(leftDrive, percent);
    rightMotorGroup.setVelocity(rightDrive, percent);

    leftMotorGroup.spin(fwd);
    rightMotorGroup.spin(fwd);
}

void robot::updateScreen() {

}

void robot::getUserInput() {
    leftDrive = processAxis(Controller.Axis3.value(), 5);
    rightDrive = processAxis(Controller.Axis2.value(), 5);
}

int robot::processAxis(int input, int cutoff) {
    float result = input;
    if (result <= cutoff && result >= -cutoff) result = 0;
    return result;
}

/*
*   Button class definitions
*/

customButton::customButton() {
    s
}