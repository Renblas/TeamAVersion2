#include "vex.h"

/*
 *    ---- START VEXCODE CONFIGURED DEVICES ----
 */
brain Brain;
competition Competition;
controller Controller;

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
motor rollerMotor = motor(PORT7, ratio6_1, false);
// Roller Motor
motor launcherMotor = motor(PORT3, ratio36_1, true);
// EndgameMotor
motor endgameMotor = motor(PORT4, ratio6_1, false);

triport ThreeWirePort = vex::triport(vex::PORT22);
digital_out launcherPneumatics = digital_out(ThreeWirePort.A);
gyro GyroB = gyro(ThreeWirePort.B);

/*
 *    ---- END VEXCODE CONFIGURED DEVICES ----
 */