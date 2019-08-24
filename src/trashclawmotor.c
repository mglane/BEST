/*
 * drivetrain.c
 *
 * process drives robot up and down the rail
 * this includes:
 *   LeftShoulderButton drives one direction
 *   RightShoulderButton drives in the opposite direction
 *
 * Last modified: October 2, 2018
 *        Author: Allen & Carver
 *
 */

// Include these files
#include "trashclawmotor.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

//Process when called
void processTrashclawmotor() {
  // Static variables for reverse mode.
  static int reverseTrashclawmDelay = 0;
  static int reverseTrashclawm = 1;

  // A variable for the speed of the driving motors.
  int trashclaw_speed;


  // If the correct buttons are pressed, set the driving speed.
  if (joystickGetDigital(1,8, JOY_UP)) {

    trashclaw_speed = MOTOR_MAX * reverseTrashclawm;
    P(D_MIN, "trashclawmotor\n");

  } else if (joystickGetDigital(1,8, JOY_DOWN))  {

    trashclaw_speed = -MOTOR_MAX * reverseTrashclawm;
    P(D_MIN, "trashclawmotor\n");

  } else { // Otherwise set the speed to zero.

    trashclaw_speed = 0;

  }

  // Set the motor's speed.
  motorSet(MOTOR_ARM_TELESCOPING_PORT, trashclaw_speed);
}
