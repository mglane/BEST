/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

#include "arm.h"
#include "canclaws.h"
#include "maniclaw.h"
#include "drivetrain.h"
#include "hosefire.h"
#include "hoseaim.h"

#include "debug.h"
int dbgmsk = D_MIN|D_MED|D_TRACE|D_1;

/*
 * set an initial values for reverse which is used to determine which side of
 *  side of the robot is the front
 */
bool g_reverse = false;
bool g_disable_drive = false;
bool g_reload = false;

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
	state state = NORMAL;

  // go ahead and grab the semaphore for autodumping since the
	//   task we are about to create will try to grab it immediately
	//  semaphoreTake(semaAutoDump, -1);

	//	taskCreate(autoDump, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

  while (true) {
    switch (state) {
    case NORMAL:


    /*
     * Top priority: driveing test soon, and arm needs testing
     * 2nd prioraty: Mani claw test, and can claws ready to test
     * 3rd prioraty: hose fireing need to test
     * 4th prioraty: hose aiming test ASAP
     */

     /*
      * driveing two motors
      * arm one motor
      * mani claw one servo
      * can claws two servos
      * hose fireing one motor
      * hose aiming one servo
      */

      processDriveTrain();
      processArm();
      processManiClaw();
      processCanClaws();
      processHoseFire();
      processHoseAim();

      /*
       * Buttons used:
       *
       * Joysticks 2 & 3, Buttons 7 Right and Left On DriveTrain
       * Buttons 8 Up & Down On Arm
       * Buttons 8 Left & Right On CanClaws
       * Buttons 5 Up On ManiClaw
       * Buttons 6 Up & Down On HoseAim
       * Buttons 5 Down On HoseFire
       *
       *
       *  Button postions on the controller:
       *
       *   __5______6__
       *  |  7      8  |
       *  |            |
       *  |  4 3  2 1  |
       *  |  ________  |
       *  | /        \ |
       *  V           V
       */


      break;

    default:
      break;
    }

    // Don't hog CPU
    // put in a delay of 20ms
    taskDelay(20);
  }
}
