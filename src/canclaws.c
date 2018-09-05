/*
 * canclaws.c
 *
 *  Created on: Sep 8, 2017
 *      Author: Allen
 *
 *  Added correct buttons: Sep 9, 2017
 *
 *   Commented: Sep 9, 2017
 */

// Include these files
#include "canclaws.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

// Function for processing
void processCanClaws() {
  // These are static so that they don't reset each time they are read
  static int topClawServoOutput;
  static int bottomClawsServoOutput;

  static bool openTopClaw;
  static bool openBottomClaws;
  static int topClawDelay;
  static int bottomClawsDelay;

  // Checks if the up button on the right side of the controller is pressed
  if (joystickGetDigital(1, 8, JOY_LEFT)) {

    // check to see if the topClawDelay has passed
    // 10 is approximately .2 second (10 x 20ms = .2s)

    // If topClawDelay is equal to 50 then openTopClaw is now the opposite value
    if (topClawDelay++ == 10) {
      openTopClaw = !openTopClaw;

      P(D_MIN, "Top claw: %d\n", openTopClaw);
    }
  }
  // Checks if the up button on the right side of the controller is not pressed
  else {
    topClawDelay = 0;
  }

  // Checks if the down button on the right side of the controller is pressed
  if (joystickGetDigital(1, 8, JOY_RIGHT)) {

    // check to see if the bottomClawsDelay has passed
    // 10 is approximately .2 second (10 x 20ms = .2s)

    // If bottomClawsDelay is equal to 50 then openBottomClaws is now the
    // opposite value
    if (bottomClawsDelay++ == 10) {
      openBottomClaws = !openBottomClaws;

      P(D_MIN, "Bottom claws: %d\n", openBottomClaws);
    }
  } else {
    // Checks if the down button on the right side of the controller is not
    // pressed
    bottomClawsDelay = 0;
  }

  // If openTopClaw is true then rotate servo to -100
  if (openTopClaw) {
    topClawServoOutput = 0;
  } else {
    // If openTopClaw is false then rotate servo to 0
    topClawServoOutput = 250;
  }

  // If openBottomClaw is true then rotate servo to -75
  if (openBottomClaws) {
    bottomClawsServoOutput = 0;
  } else {
    // If openBottomClaw is false then rotate servo to 0
    bottomClawsServoOutput = 200;
  }

  // Set servos to correct ports
  motorSet(SERVO_TOP_CAN_CLAW_PORT, topClawServoOutput);
  motorSet(SERVO_BOTTOM_CAN_CLAWS_PORT, bottomClawsServoOutput);
}
