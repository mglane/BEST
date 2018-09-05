/*
 * hoseaim.c
 *
 *  Created on: Sep 6, 2017
 *      Author: Allen & Lane
 *
 *   Commented: Sep 9, 2017
 *
 *  Added correct buttons: Sep 15, 2017
 */

// Include these files
#include "hoseaim.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

// Processes when called
void processHoseAim() {
  // Static(Non reseting) variables for Hose Aim
  static int servoOutput;
  static int uDelay;
  static int dDelay;

  // Motor controls for HoseAim
  if (joystickGetDigital(1, 6, JOY_UP)) {
    // Add 5 every time pressed
    if (uDelay++ == 5) {
      if (servoOutput > -100) {
        servoOutput -= 5;
      }

      P(D_MIN, "Hose Aim: %d\n", servoOutput);
    }
  } else {
    uDelay = 0;
  }
  if (joystickGetDigital(1, 6, JOY_DOWN)) {
    // Subtract 5 every time pressed
    if (dDelay++ == 5) {
      if (servoOutput < 60) {
        servoOutput += 5;
      }

      P(D_MIN, "Hose Aim: %d\n", servoOutput);
    }
  } else {
    dDelay = 0;
  }

  if (g_reload) {
    motorSet(SERVO_HOSE_AIM_PORT, -100);
    taskDelay(500);
    g_reload = false;
  }

  // Set the servo
  motorSet(SERVO_HOSE_AIM_PORT, servoOutput);
}
