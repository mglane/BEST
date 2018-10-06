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
#include "extraservos.h"

#include "debug.h"
extern int dbgmsk;

// Processes when called
void processExtraServos() {
  // Variables for the Trash Claw that do not reset
  static int servoOutput2;
  static int servoOutput3;
  static bool closeServo;
  static bool closeServo2;
  static int delay = 0;

  // If you press the top left button on the shoulder of the controller
  // and hold it for more than 1 second
  // then closeTrashClaw equals the oposite of its previous value
  if (joystickGetDigital(1, 7, JOY_UP)) {

    // check to see if the delay has passed
    // 50 is approximately 1 second (50 x 20ms = 1s)
    if (delay++ == 10) {
      closeServo = !closeServo;

      P(D_MIN, "ManiClaw: %d\n", closeServo);
    }
  } else {
    // Otherwise delay gets reset
    delay = 0;
  }

  // If closeTrashClaw equals true then servoOutput equals 127
  if (closeServo) {
    servoOutput2 = 70;
  } else {
    // Otherwise servoOutput equals -127
    servoOutput2 = -70;
  }

  // Set the servo
  motorSet(SERVO_PINCHER_2_PORT, servoOutput2);

  if (joystickGetDigital(1, 7, JOY_DOWN)) {

    // check to see if the delay has passed
    // 50 is approximately 1 second (50 x 20ms = 1s)
    if (delay++ == 10) {
      closeServo2 = !closeServo2;

      P(D_MIN, "ManiClaw: %d\n", closeServo2);
    }
  } else {
    // Otherwise delay gets reset
    delay = 0;
  }

  // If closeTrashClaw equals true then servoOutput equals 127
  if (closeServo2) {
    servoOutput3 = 70;
  } else {
    // Otherwise servoOutput equals -127
    servoOutput3 = -70;
  }

  // Set the servo
  motorSet(SERVO_FILAMENT_PINCHER_PORT, servoOutput2);


}
