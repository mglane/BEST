/*
 * arm.c
 *
 * process the normal functions of the arm
 * this includes:
 *   moving the arm up and down
 *   rotating the arm
 *   telescope the arm
 *
 * Last modified: October 13, 2018
 *        Author: Carver
 *
 */

#include "arm.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

void processArm()
{

  // Static variables for reverse mode.
  static int reverseArmDelay = 0;
  static int reverseArm = 1;
  // Static veriables for halving the rotation speed of the arm
  static bool halfrotSpeed = 0;
  static int halfrotSpeedDelay = 10;

  // The reverse mode code.
  if(joystickGetDigital(1, 7, JOY_DOWN)){

    // If reverseDriveTrainDelay is equal to 20, than reverse the driving motors.
    if(reverseArmDelay++ == 20){
      reverseArm *= -1;
    }
  }
  // If the button is released reset the delay.
  else {
    reverseArmDelay = 0;
  }

  // Code for the rotating and up/down functions
  int vertical = joystickGetAnalog(1, 2);
  int rotating = joystickGetAnalog(1, 4) * reverseArm;

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
    if (halfrotSpeedDelay++ == 10) {
      // toggle the state of the speed and reset the counter
      halfrotSpeed = !halfrotSpeed;

      P(D_MIN, "Halfspeed setting: %d\n", halfrotSpeed);
    }
  } else {
    // the button has been released, reset the time counter
    halfrotSpeedDelay = 0;
  }

  // * if the robot is in half speed mode, divide both motor
  // *  output values by 2

  if (halfrotSpeed) {
    rotating = (rotating >> 1);
  }
  // end of halfSpeed process

  motorSet(MOTOR_ARM_VERTICAL_PORT, vertical);
  motorSet(MOTOR_ARM_ROTATING_PORT, rotating);

}
