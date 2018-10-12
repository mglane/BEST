/*
 * drivetrain.c
 *
 * process drives robot up and down the rail
 * this includes:
 *   LeftShoulderButton drives one direction
 *   RightShoulderButton drives in the opposite direction
 *
 * Last modified: October 2, 2018
 *        Author: Allen & Carver
 *
 */

// Include these files
#include "drivetrain.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

//Process when called
void processDriveTrain() {
  // Static variables for reverse mode.
  static int reverseDriveTrainDelay = 0;
  static int reverseDriveTrain = 1;
  //g_halfSpeed = false;
  //g_halfSpeedDelay = 0;
  // A variable for the speed of the driving motors.
  int drive_speed;


  // The reverse mode code.
  if(joystickGetDigital(1, 7, JOY_RIGHT)){

    // If reverseDriveTrainDelay is equal to 50, than reverse the driving motors.
    if(reverseDriveTrainDelay++ == 20){
      reverseDriveTrain *= -1;
    }
  }
  // If the button is released reset the delay.
  else {
    reverseDriveTrainDelay = 0;
  }



  // If the correct buttons are pressed, set the driving speed.
  if (joystickGetDigital(1,5, JOY_DOWN))
  {
    drive_speed = MOTOR_MAX * reverseDriveTrain;
    P(D_MIN, "Driving forward\n");

  }
  else if (joystickGetDigital(1,6, JOY_DOWN))
  {
    drive_speed = -MOTOR_MAX * reverseDriveTrain;
    P(D_MIN, "Driving backward\n");
  }
  // Otherwise set the speed to zero.
  else
  {
    drive_speed = 0;
  }

  // Set the motor's speed.
  motorSet(MOTOR_WHEEL_PORT, drive_speed);
}
