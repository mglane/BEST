/*
 * Edited from last year
 */

#include "drivetrain.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

void processDriveTrain() {

  // We want to be able to reverse the motor; LeftShoulderDown moves it one direction
  // and RightShoulderDown moves the motor the opposite direction

  // read the button values for the wheel motors

if (joystickGetDigital(1,5, JOY_DOWN))
{
  motorSet(MOTOR_WHEEL_PORT,127);
  P(D_MIN, "Driving forward\n");

}
else if (joystickGetDigital(1,6, JOY_DOWN))
{
  motorSet(MOTOR_WHEEL_PORT,-127);
  P(D_MIN, "Driving backward\n");
}
else
{
  motorSet (MOTOR_WHEEL_PORT,0);
}

}
