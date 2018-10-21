/*
 * telescope.c
 *
 * servo for telescoping arm
 *
 * Last modified: October 11, 2018
 *        Author: Carver
 *
 */

// Include these files
#include "main.h"
#include "telescope.h"

#include "debug.h"
extern int dbgmsk;

// Processes when called
void processTelescope() {
  // Variables for the Trash Claw that do not reset
  static int telescope;
  static bool closeServo;
  static int delay = 0;

  // If you press the top left button on the shoulder of the controller
  // and hold it for more than 1 second
  // then closeTrashClaw equals the oposite of its previous value
  if (joystickGetDigital(1, 6, JOY_UP)) {

    // check to see if the delay has passed
    // 50 is approximately 1 second (50 x 20ms = 1s)
    if (delay++ == 10) {
      closeServo = !closeServo;

      P(D_MIN, "TelescopingArm: %d\n", closeServo);
    }
  } else {
    // Otherwise delay gets reset
    delay = 0;
  }

  // If closeServo equals true then servoOutput equals 127
  if (closeServo) {
    telescope = 127;
  } else {
    // Otherwise servoOutput equals -127
    telescope = -127;
  }

  // Set the servo
  motorSet(SERVO_TELESCOPE_PORT, telescope);
}
