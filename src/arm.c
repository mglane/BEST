/*
 * arm.c
 *
 *  Created on: Sep 6, 2017
 *      Author: Allen & Lane
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
 *   opening and closing the claw
 */
void processArm() {
  int motorOutput = 0; // Moter output

  if (joystickGetDigital(1, 8, JOY_UP)) {
    // check to see if the up limit switch has been tripped
    if (digitalRead(LIMIT_ARM_UP_PORT)) {
      // the up limit switch has not been tripped
      // we are safe to keep moving up

      // If reverse equals true then motorOutput equals -MOTOR_MAX
      if (g_reverse) {
        motorOutput = -MOTOR_MAX;
      } else {
        // Otherwise motorOutput equals MOTOR_MAX
        motorOutput = MOTOR_MAX;
      }

      g_disable_drive = true;

      P(D_MIN, "Arm going up.\n");
    }
  } else {
    g_disable_drive = false;
  }

  if (joystickGetDigital(1, 8, JOY_DOWN)) {
    // check to see if the down limit switch has been tripped
    if (digitalRead(LIMIT_ARM_DOWN_PORT)) {
      // the downlimit switch has not been tripped
      // we are safe to keep moving down

      // If reverse equals true then motorOutput equals MOTOR_MAX
      if (g_reverse) {
        motorOutput = MOTOR_MAX;
      } else {
        // Otherwise motorOutput equals -MOTOR_MAX
        motorOutput = -MOTOR_MAX;
      }

      P(D_MIN, "Arm going down.\n");
    }
  }

  motorSet(MOTOR_ARM_PORT, motorOutput);
}
