/*
 * maniclaw.c
 *
 *  Created on: Sep 6, 2017
 *      Author: Allen & Lane
 *
 *  Added correct buttons: Sep 8, 2017
 *
 *  Commented: Sep 9, 2017
 */

// Include these files
#include "main.h"
#include "maniclaw.h"

#include "debug.h"
extern int dbgmsk;

// Processes when called
void processManiClaw() {
  // Variables for the Mani Claw that do not reset
  static int servoOutput;

  static bool closeManiClaw;
  static int delay;

  // If you press the top left button on the front of the controller
  // and hold it for more than 1 second
  // then closeManiClaw equals the oposite of its previous value
  if (joystickGetDigital(1, 5, JOY_UP)) {

    // check to see if the delay has passed
    // 50 is approximately 1 second (50 x 20ms = 1s)
    if (delay++ == 10) {
      closeManiClaw = !closeManiClaw;

      P(D_MIN, "ManiClaw: %d\n", closeManiClaw);
    }
  } else {
    // Otherwise delay gets reset
    delay = 0;
  }

  // If closeManiClaw equals true then servoOutput equals -100
  if (closeManiClaw) {
    servoOutput = -100;
  } else {
    // Otherwise servoOutput equals 0
    servoOutput = 0;
  }

  // Set the servo
  motorSet(SERVO_MANICLAW_PORT, servoOutput);
}
