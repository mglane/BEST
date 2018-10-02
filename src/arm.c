/*
 * arm.c
 *
 *  Created on: Sep 28, 2017
 *      Author: Carver
 *
 *  Added correct buttons: Sep 9, 2017
 *
 *   Commented: Sep 9, 2017
 */

#include "arm.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

/*
 * process the normal functions of the arm
 * this includes:
 *   moving the arm up and down
 *   rotating the arm
 *   telescope the arm
 */
void processArm()
{
  int vertical = joystickGetAnalog(1,2);
  int rotating = joystickGetAnalog(1,4);

  motorSet(MOTOR_ARM_VERTICAL_PORT, vertical);
  motorSet(MOTOR_ARM_ROTATING_PORT, rotating);






  // Code for telescope function


if (joystickGetDigital(1,8, JOY_UP))
{
motorSet(MOTOR_ARM_TELESCOPING_PORT,127);
}
else if (joystickGetDigital(1,8, JOY_DOWN))
{
motorSet(MOTOR_ARM_TELESCOPING_PORT,-127);
}
else
{
  motorSet (MOTOR_ARM_TELESCOPING_PORT,0);
}

}
