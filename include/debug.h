/** @file debug.h
 * @brief Header file for debug functions
 *
 * Functions to allow for quick output to terminal console.
 *
 * Set DEBUG to 1 to activate when developing and wanting debug messages.
 * Set DEBUG to 0 in a production environment so resources are not wasted
 *  processing the messages.
 *
 * D(msk, fmt, args...) - debug print out to terminal; lists file, function, and line number
 * P(msk, fmt, args...) - print message to terminal
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#ifndef DEBUG
#define DEBUG 1
#endif

#define D_MIN   0x00010000  // Minimum level
#define D_MED   0x00020000  // Medium level
#define D_MAX   0x00040000  // Maximum level
#define D_FLUSH 0x00080000  // Usefull by a program crash
#define D_TRACE 0x00100000
#define D_1     0x00000001

/*
 * example definition for dbgmsk is D_MIN|D_MED|D_MAX|D_TRACE|D_1
 */
extern int dbgmsk;

#if DEBUG
  #define D(msk, fmt, args...) if(msk & dbgmsk) { printf("%s - %s: %d: ", __FILE__, __FUNCTION__, __LINE__ ); printf(fmt, ## args ); }
  #define P(msk, fmt, args...) if(msk & dbgmsk) { printf(fmt, ## args ); if(msk & D_FLUSH); }
#else  /* DEBUG */
  #define D(msk, fmt, ...) do { if (0 && (msk & dbgmsk)) printf(fmt); } while (0)
  #define P(msk, fmt, ...) do { if (0 && (msk & dbgmsk)) printf(fmt); } while (0)
#endif  /* DEBUG */

/*

Examples:

Ex. module1.c:

#include "debug.h"

static int dbgmsk;  // using local dbgmsk
module1_setdbg(int msk) { dbgmsk = msk; D(D_TRACE,"dbgmsk1=%x\n", dbgmsk); }

foo1() {  P(D_1, "foo1 function\n" );
  ....
}
foo2() {}
...

Ex. foo3.c

#include "debug.h"
extern int dbgmsk; // using global dbgmsk

Ex. main:

#include "debug.h"
int dbgmsk = 0; // this is the global dbgmsk

int main() {
  dbgf = stderr; // or your logfile
  dbgmsk = D_MIN;
  module1_setdbg(D_MIN|D_MED|D_TRACE|D_1);
  ....
}

Source: https://stackoverflow.com/questions/987637/define-debug-1
*/

#endif  /* DEBUG_H_ */
