/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"


#include "drivetrain.h"
#include "arm.h"
#include "trashclaw.h"
#include "telescope.h"


#include "debug.h"
int dbgmsk = D_MIN|D_MED|D_TRACE|D_1;

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

  while (true) {

      processDriveTrain();  // process for wheel movement
      processArm();         // process to handle arm movement
      processTrashClaw();   // process for claw movement
      processTelescope();  // process for telescoping arm

      /*
       * Buttons used:
       *
       * Joystick 2: Raise and lower arm
       * Joystick 4: Rotate arm
       * Button 5 Down: Drivetrain move forward
       * Button 5 Up: Close trash claw
       * Button 6 Down: Drivetrain move backward
       * Button 6 Up: Release telescoping arm
                      Close reef claw
       * Button 7 Left: Half rotation speed
       * Button 7 Right: Reverse drivetrain direction
       * Button 7 Down: Reverse arm rotation direction
       *
       *  Button postions on the controller:
       *
       *   __5____________6__
			 *  |                  |
       *  |  7            8  |
			 *  |                  |
       *  |   |          |   |
			 *  | 4---        ---1 |
       *  |   |          |   |
       *  |  _3__________2_  |
       *  | /              \ |
       *  V                 V
       */

    taskDelay(20); // delay so cortex isn't running constantly
  }
}
