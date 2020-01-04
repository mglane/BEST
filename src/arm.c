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
 *2019/09/23
 * Commented out reverse arm rotation
 * Rebekah
 */

#include "arm.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

void processArm()
{

  // Code for raising and lowering the arm
  int vertical = 0;

  static int armUDelay = 0;
  static int armDDelay = 0;

  if(joystickGetDigital(1, 7, JOY_UP)) {
    if(armUDelay++ > 10){
      vertical = 127;
    }
  } else {
    armUDelay = 0;
  }

  if(joystickGetDigital(1, 7, JOY_DOWN)) {
    if(armDDelay++ > 5){
      vertical = -127;
    }
  } else {
    armDDelay = 0;
  }

  // Code for extending and retracting the arm
  int extend = 0;

  static int extendDelay = 0;
  static int retractDelay =0;

  if(joystickGetDigital(1, 8, JOY_UP)) {
    if(extendDelay++ > 5){
      extend = 127;
    }
  } else {
    extendDelay = 0;
  }

  if(joystickGetDigital(1, 8, JOY_DOWN)) {
    if(retractDelay++ > 10){
      extend = -127;
    }
  } else {
    retractDelay = 0;
  }

//  P(D_MAX, "SmallRMotor: %d, SmallLMotor: %d\n", vertical, extend);

  motorSet(MOTOR_ARM_VERTICAL_PORT, vertical);
  motorSet(MOTOR_ARM_EXTEND_PORT, extend);

}
