/*
 * trashclaw.c
 *
 * process opens and closes the trash claw
 *
 * Last modified: October 2, 2018
 *        Author: Allen & Carver
 *
 */

// Include these files
#include "main.h"
#include "trashclaw.h"

#include "debug.h"
extern int dbgmsk;

// Processes when called
void processTrashClaw() {
  // Variables for the Trash Claw that do not reset
  static int servoOutput;

  static bool closeTrashClaw;
  static int delay = 0;

  // If you press the top left button on the shoulder of the controller
  // and hold it for more than 1 second
  // then closeTrashClaw equals the oposite of its previous value
  if (joystickGetDigital(1, 5, JOY_UP)) {

    // check to see if the delay has passed
    // 50 is approximately 1 second (50 x 20ms = 1s)
    if (delay++ == 10) {
      closeTrashClaw = !closeTrashClaw;

      P(D_MIN, "ManiClaw: %d\n", closeTrashClaw);
    }
  } else {
    // Otherwise delay gets reset
    delay = 0;
  }

  // If closeTrashClaw equals true then servoOutput equals 127
  if (closeTrashClaw) {
    servoOutput = 70;
  } else {
    // Otherwise servoOutput equals -127
    servoOutput = -70;
  }

  // Set the servo
  motorSet(SERVO_CLAW_PORT, servoOutput);
  motorSet(SERVO_CLAW_PORT_2, -servoOutput);
}
