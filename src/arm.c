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

  // Code for the rotating and up/down functions
  int vertical = joystickGetAnalog(1, 2);
  int rotating = joystickGetAnalog(1, 4);



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
