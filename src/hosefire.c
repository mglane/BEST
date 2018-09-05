/*
 * hosefire.c
 *
 *  Created on: Sep 7, 2017
 *      Author: Allen
 *
 *  Added correct buttons: Sep 8, 2017
 *
 *  Commented: Sep 9, 2017
 *
 *  Changed buttons: Sep 15, 2017
 */

#include "main.h"
#include "hosefire.h"

#include "debug.h"
extern int dbgmsk;

void processHoseFire() {
		// Variables for the Hose Fire
		int motorOutput = 0;
		static int firing;

		static int delay;

		// Check whether the hose fire button has been pressed
    if (joystickGetDigital(1, 5, JOY_DOWN)) {

    	 	// Delay motor in case button is pressed by accident

    		if (delay++ >= 20) {
    				// Rotate motor
    				motorOutput = MOTOR_MAX;

						if (delay > 50) { firing = 1; }

						P(D_MIN, "Firehose on!\n");
    		}
    }
		// Otherwise reset delay
		else {
    		delay = 0;

				if (firing) {
					g_reload = true;
					firing = 0;
				}
    }

		// Set motor
		motorSet( MOTOR_HOSE_FIRE_PORT, motorOutput);
}
