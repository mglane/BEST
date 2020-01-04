/*
 * trashclaw.c
 *
 * process opens and closes the trash claw
 *
 * Last modified: October 2, 2018
 *        Author: Allen & Carver
 *
 * 2019/10/18
 * Cleaned up lineclaw.c code
 * Rebekah
 */

// Include these files
#include "main.h"
#include "lineclaw.h"

#include "debug.h"
extern int dbgmsk;

void processLineClaw() {
  static bool closeLineClaw = 0;
  static int clawDelay = 0;
  static int clawCloseDelay = 0;
  int servoOutput = 0;

  // If you press button 5 Joy_Up
  // And hold it for more than 1 second
  // Then closeLineClaw equals true
  if (joystickGetDigital(1, 5, JOY_UP)) {

    // check to see if the delay has passed
    if (clawDelay++ >  10) {
      closeLineClaw = 1;
    }
  } else {
    clawDelay = 0;
  }

  if (joystickGetDigital(1, 5, JOY_DOWN)) {
    if (clawCloseDelay++ > 10) {
      closeLineClaw = 0;
    }
  } else {
    clawCloseDelay = 0;
  }

    // If closeLineClaw = true
    // Then servoOutPut = 45
    if(closeLineClaw) {
      servoOutput = 100;
    }else {
      servoOutput = 0;
    }
    // Setting the servoOutput

  //  P(D_MAX, "LineClaw: %d\n", servoOutput);
    motorSet(SERVO_LINECLAW_PORT, servoOutput);
}
