/** @file main.h
 * @brief Header file for global functions
 *
 * Any experienced C or C++ programmer knows the importance of header files. For those who
 * do not, a header file allows multiple files to reference functions in other files without
 * necessarily having to see the code (and therefore causing a multiple definition). To make
 * a function in "opcontrol.c", "auto.c", "main.c", or any other C file visible to the core
 * implementation files, prototype it here.
 *
 * This file is included by default in the predefined stubs in each VEX Cortex PROS Project.
 *
 * Copyright (c) 2011-2016, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#ifndef MAIN_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define MAIN_H_

#include <API.h>

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

// A function prototype looks exactly like its declaration, but with a semicolon instead of
// actual code. If a function does not match a prototype, compile errors will occur.

// Prototypes for initialization, operator control and autonomous

/**
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous();
/**
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO();
/**
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize();
/**
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
void operatorControl();

#define MOTOR_MAX 127 // maximum value allowed for motors (0-127)

/* motor assignments */

/**
 *  motors must be separated into the low (ports 2-5)
 *  and high (ports 6-9) banks; split large and small
 *  motors into separate banks
 */
#define MOTOR_ARM_ROTATING_PORT 2
#define MOTOR_ARM_TELESCOPING_PORT 6
#define MOTOR_WHEEL_PORT 3
#define MOTOR_ARM_VERTICAL_PORT 7

#define SERVO_BRAKE_PORT 4
#define SERVO_PINCHER_1_PORT 5
#define SERVO_PINCHER_2_PORT 8
#define SERVO_FILAMENT_PINCHER_PORT 9


/**
 * Digital input assignments
 *//* Code from last year *
#define LIMIT_ARM_DOWN_PORT 1 // limit switch for arm moving down
#define LIMIT_ARM_UP_PORT 2   // limit switch for arm moving up

/**
 * Analog input assignments
 *//* Code from last year *
#define SENSOR_POT_PORT 1

/**
 * Define state machine
 *
 * States are used to put the robot into special operating modes. They
 *  can include a normal state for regular operation or other listed
 *  states that can be used to complete particular tasks.
 *
 * NORMAL - normal operations
 * UNKNOWN - watchdog state to allow to robot to get back to a steady state
 */
/* Last years code *

typedef enum state { NORMAL, UNKNOWN } state;

extern bool g_reverse; // state of robot control in forward or reverse mode
extern bool g_disable_drive; // switch to disable motors so they will not move
extern bool g_reload;

/**
 * Define semaphores and mutexs
 */
// currently commented out because we don't have automation code
//Semaphore semaAutoDump;
//Mutex mutexArmControl;

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
