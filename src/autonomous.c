/*
 * drivetrain.c
 *
 * process autonomously delivers the payload
 * payload = spare insulator
 * this includes:
 *   Button 8 JOY_RIGHT starts the autonomous process
 *   Button 8 JOY_LEFT acts as the kill switch
 *
 * 2019/10/19:
 *   Wrote the initial code for autonomous delivery
 *   Rebekah
 */

// Include these files
#include "autonomous.h"
#include "main.h"
#include "ir.h"

#include "debug.h"
extern int dbgmsk;

// Autonomous Delivery
void autonomousDelivery() {
  int autoCont = true;
  int motorLOutput = 0;
  int motorROutput = 0;
  int irDelay = 0;
  int pause = 0;
  int reverseCount = 0;

  enum drvState state = INIT;

  while (autoCont) {
    /*
      Implementing a kill switch just in case we need to stop autonomous delivery
      If button 8 - JOY_LEFT is pushed
      Then state = BREAKOUT
    */
    if(joystickGetDigital(1, 8, JOY_LEFT)) {
      state = BREAKOUT;
    }

    switch (state) {
      case INIT:

        // Debug statement to let the programmer know what state the robot is in
        P(D_MIN, "Initializing autonomous mode...\n");

        /*
          Starting the motors at full throttle to drive the robot foward
        */
        motorLOutput = 75;
        motorROutput = 73;
        motorSet(SERVO_PAYLOAD_PORT, 0);

        /*
          Once the intializing in through
          State = DRIVING
          Then code starts over and this time reads the case Driving: code
        */
        state = DRIVING;

        break;

      case DRIVING:
        // Debug statement to let the programmer know what state the robot is in
        P(D_MIN, "Driving...\n");
        /*
          If the right sensor starts receiving a signal
          Then the right motor output = -60
        */
        if(ir_detect_low(IR1_PORT)) {
          motorROutput = -60;
          P(D_MIN, "See a line right...\n");
        } else {
          motorROutput = 75;
        }

        /*
          If the left sensor starts receiving a signal
          Then the left motor output = -60
        */
        if(ir_detect_low(IR2_PORT)) {
          motorLOutput = -60;
          P(D_MIN, "See a line left...\n");
        } else {
          motorLOutput = 73;
        }

        /*
          If both sensors receive a signal
          Then set both motors = 30;
          */

        if(ir_detect_low(IR1_PORT) && ir_detect_low(IR2_PORT)) {
          motorLOutput = 30;
          motorROutput = 30;
        }


        /*
          If the transmission tower detecting switch is activated
          Then state = DROPOFF
        */
        if(ir_detect_high(IR3_PORT)) {
          motorLOutput = 0;
          motorROutput = 0;
          state = DROPOFF;
        }

        /*
          If both motor outputs = 0 for longer than 20 milliseconds
          Then state = DROPOFF

        if (motorLOutput == 0 && motorROutput == 0) {
            state = DROPOFF;
        }
        */

        // Debug statements to see if the code is working correctly
        P(D_MAX, "RMotor: %d, LMotor: %d\n", motorROutput, motorLOutput);

        motorSet(MOTOR_L_WHEEL_PORT, motorLOutput);
        motorSet(MOTOR_R_WHEEL_PORT, motorROutput);

        break;

      case DROPOFF:
        P(D_MIN, "Pausing before dropoff...\n");
        taskDelay(600);

        // Debug statement to let the programmer know what state the robot is in
        P(D_MIN, "Dropping off...\n");
        motorSet(SERVO_PAYLOAD_PORT, 120);

        P(D_MIN, "Pausing after dropoff...\n");
        taskDelay(600);

        state = BACKUP;

        break;

      case BACKUP:
        // Debug statement to let the programmer know what state the robot is in
        P(D_MIN, "Backing up...\n");
        /*
          If reverseCount < 100
          Then set the motors to MAX reverse
          This means the robot will backup for on second
          Once reverseCount > 100 autoCont = false, and autonomous delivery ends
        */
        if (reverseCount++ < 750) {
          motorSet(MOTOR_L_WHEEL_PORT, -MOTOR_MAX);
          motorSet(MOTOR_R_WHEEL_PORT, -MOTOR_MAX);
          taskDelay(1);
        } else {
          autoCont = false;
        }

        motorSet(SERVO_PAYLOAD_PORT, 0);

        break;

      case BREAKOUT:
        /*
          When BREAKOUT is called:
          Both motors will set to zero and stop
          And the servo will close
          Then autoCont will = false and autonomous delivery will end
        */
        motorSet(MOTOR_L_WHEEL_PORT, 0);
        motorSet(MOTOR_R_WHEEL_PORT, 0);
        motorSet(SERVO_PAYLOAD_PORT, 0);

        autoCont = false;
        break;

      default:
        break;
    }

  }

  P(D_MIN, "Completed autonomous mode...\n");

}

//Checking to see if autonomous delivery should begin
void checkAutoDrive(void) {
  static int autoDelay = 0;
  /*
    Checking to see if sensors are sending a signal
  */

  if(ir_detect_low(IR1_PORT)) {
    P(D_MIN, "Receiving signal...\n");
  }

  if(ir_detect_low(IR2_PORT)) {
    P(D_MIN, "Receiving signal...\n");
  }

  /*
    If button 8 JOY_RIGHT is pressed, and held for half a second
    Then begin autonomous delivery
  */
  if (joystickGetDigital(1, 8, JOY_RIGHT)) {
    if (autoDelay++ == 50){
      autonomousDelivery();
    }
  } else {
    autoDelay = 0;
    }
}
