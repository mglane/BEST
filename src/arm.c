/*
 * arm.c
 *
 * process the normal functions of the arm
 * this includes:
 *   moving the arm up and down
 *   rotating the arm
 *   telescope the arm
 *
 * Last modified: October 2, 2018
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

  // The reverse mode code.
  if(joystickGetDigital(1, 7, JOY_DOWN)){

    // If reverseDriveTrainDelay is equal to 50, than reverse the driving motors.
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

    bool halfSpeed;
    int halfSpeedDelay;
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



  // * if the robot is in half speed mode, divide both motor
  // *  output values by 2


  if (halfSpeed) {
    rotating = (rotating >> 1);
  }
// end of halfSpeed process


  // Code for telescope function
  // One button moves the motor in one direction
  // while the other button moves the motor in the opposite direction
  int telescoping_speed;


  if (joystickGetDigital(1, 8, JOY_UP))
  {
    telescoping_speed = MOTOR_MAX;
  }
  else if (joystickGetDigital(1, 8, JOY_DOWN))
  {
    telescoping_speed = -MOTOR_MAX;
  }
  else
  {
    telescoping_speed = 0;
  }

  motorSet(MOTOR_ARM_VERTICAL_PORT, vertical);
  motorSet(MOTOR_ARM_ROTATING_PORT, rotating);

  motorSet(MOTOR_ARM_TELESCOPING_PORT, telescoping_speed);
}
