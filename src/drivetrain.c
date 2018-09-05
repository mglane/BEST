/*
 * Edited from last year
 */

#include "drivetrain.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

void processDriveTrain() {
  int motorLOutput = 0;
  int motorROutput = 0;

  static bool halfSpeed;
  static int halfSpeedDelay;

  // We want to be able to reverse the state of the motors
  static int reverseDelay;

  // read the joystick values for the wheel motors

  // check if the arm is being raised and disable the drive motors
  if (!g_disable_drive) {
    if (g_reverse) {
      motorLOutput = -joystickGetAnalog(1, 2);
      motorROutput = -joystickGetAnalog(1, 3);
    } else {
      motorLOutput = joystickGetAnalog(1, 3);
      motorROutput = joystickGetAnalog(1, 2);
    }
  } else {
    motorLOutput = 0;
    motorROutput = 0;
  }

  /*
   * determine whether the robot should move at
   *  half speed
   * this state will be remembered so the robot
   *  stays in "half speed" mode until the button
   *  is activated again
   */
  if (joystickGetDigital(1, 7, JOY_LEFT)) {
    // put in a delay of a half second
    //   in case the button was hit by accident
    if (halfSpeedDelay++ == 10) {
      // toggle the state of the speed and reset the counter
      halfSpeed = !halfSpeed;

      P(D_MIN, "Halfspeed setting: %d\n", halfSpeed);
    }
  } else {
    // the button has been released, reset the time counter
    halfSpeedDelay = 0;
  }

  /*
   * if the robot is in half speed mode, divide both motor
   *  output values by 2
   */
  if (halfSpeed) {
    motorLOutput = (motorLOutput >> 1);
    motorROutput = (motorROutput >> 1);
  }

  if (joystickGetDigital(1, 7, JOY_RIGHT)) {
    if (reverseDelay++ == 10) {
      g_reverse = !g_reverse;

      P(D_MIN, "Drivetrain Reverse Mode: %d\n", g_reverse);
    }
  } else {
    reverseDelay = 0;
  }

  P(D_MAX, "RMotor: %d, LMotor: %d\n", motorROutput, motorLOutput);

  motorSet(MOTOR_L_WHEEL_PORT, motorLOutput);
  motorSet(MOTOR_R_WHEEL_PORT, motorROutput);
}
