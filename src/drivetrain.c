/*
 * drivetrain.c
 *
 * process drives robot up and down the rail
 * this includes:
 *   LeftShoulderButton drives one direction
 *   RightShoulderButton drives in the opposite direction
 *
 * 2019/09/16:
 *   Intial code for drive motors
 *   Rebekah
 * 2019/09/17
 *  Defined motor outputs
 *  Rebekah
 * 2019/18/19
 * Worked on the autonomous delivery
 * Rebekah
 */

// Include these files
#include "drivetrain.h"
#include "main.h"
#include "ir.h"

#include "debug.h"
extern int dbgmsk;

//Process when called
void processDriveTrain() {
  int motorLOutput = 0;
  int motorROutput = 0;

  static int lockFwdDelay = 0;
  static int lockBackDelay = 0;

  static bool halfSpeed = 0;
  static int halfSpeedDelay = 0;

  /*
   * determine whether the robot should move at
   *  half speed
   * this state will be remembered so the robot
   *  stays in "half speed" mode until the button
   *  is activated again
   */
  if (joystickGetDigital(1, 7, JOY_RIGHT)) {
    // put in a delay of a half second
    //   in case the button was hit by accident
    if (halfSpeedDelay++ == 10) {
      // toggle the state of the speed and reset the counter
      halfSpeed = !halfSpeed;

    //  P(D_MIN, "Halfspeed setting: %d\n", halfSpeed);
    }
  } else {
    // the button has been released, reset the time counter
    halfSpeedDelay = 0;
  }

  motorLOutput = joystickGetAnalog(1, 3);
  motorROutput = joystickGetAnalog(1, 2);

// If button 6: JOY_UP is pressed
// Than the robot will drive forward
  if (joystickGetDigital(1, 6, JOY_UP)) {
    if(lockFwdDelay++ > 10) {
      motorLOutput = 127;
      motorROutput = 127;
    }
  } else {
    lockFwdDelay = 0;
  }

// If button 6: JOY_DOWN is pressed
// Then the robot will drive backward
  if (joystickGetDigital(1, 6, JOY_DOWN)) {
    if(lockBackDelay++ > 10) {
      motorLOutput = -127;
      motorROutput = -127;
    }
  } else {
    lockBackDelay = 0;
  }

  /*
   * if the robot is in half speed mode, divide both motor
   *  output values by 2
   */
  if (halfSpeed) {
    motorLOutput = (motorLOutput >> 1);
    motorROutput = (motorROutput >> 1);
  }

  //P(D_MAX, "RMotor: %d, LMotor: %d\n", motorROutput, motorLOutput);

  motorSet(MOTOR_L_WHEEL_PORT, motorLOutput);
  motorSet(MOTOR_R_WHEEL_PORT, motorROutput);
}
