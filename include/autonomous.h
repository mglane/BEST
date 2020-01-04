#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

// Begin C++ extern to C
#ifdef __cplusplus
extern "C" {
#endif

enum drvState {INIT, DRIVING, DROPOFF, BACKUP, BREAKOUT};

/**
 * Code to check if autonomous delivery has been initiated
 *
 * @param void
 * @return void
 */
void checkAutoDrive();
/*
 * Code to autonomously deliver the spare insulator the the transmission tower
*/
void autonomousDelivery();

// End C++ extern to C
#ifdef __cplusplus
}
#endif

#endif
