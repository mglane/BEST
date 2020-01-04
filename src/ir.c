/*
 * ir.c
 *
 * Library to handle basic BEST IR sensor.
 *
 */

// Include these files
#include "ir.h"
#include "main.h"

#include "debug.h"
extern int dbgmsk;

int g_ir_count;

int ir_detect_low(int irPort) {
  if (digitalRead(irPort) == LOW) {
    P(D_MED, "IR signal low: Port %d\n", irPort);

    return true;
  }

  return false;
}

int ir_detect_high(int irPort) {
  if (digitalRead(irPort) == HIGH) {
    P(D_MED, "IR signal high: Port %d\n", irPort);

    return true;
  }

  return false;
}

int ir_detect_edge(int irPort) {
  static int prevState = HIGH;
  int state;

  state = digitalRead(irPort);

  if (state != prevState) {
    P(D_MED, "IR signal edge: Port %d\n", irPort);

    prevState = state;

    return true;
  }

  prevState = state;

  return false;
}

int ir_count_low(int irPort, int reset) {
  static int count = 0;
  // keep an array of the previous states so we can track multiple IR
  //  sensors at the same time.
  static int prevState[10] = {HIGH};
  int state;

  // allow the counter to be reset
  if (reset == 1) { count = 0; }

  state = digitalRead(irPort);

  if ((state == LOW) && (prevState[irPort] != LOW)) {
    count++;

    P(D_MED, "IR Port %d count: %d\n", irPort, count);
  }

  prevState[irPort] = state;

  return count;
}

// we are using the ir_count_low function to automate the arm
int ir_armAuto_count(int irPort) {
  static int armCount = 0;

  static int prevArmState[10] = {HIGH};
  int armState;

  armState = digitalRead(irPort);

  if ((armState == LOW) && (prevArmState[irPort] != LOW)) {
    armCount++;

    P(D_MED, "IR Port %d count: %d\n", irPort, armCount);
}

  prevArmState[irPort] = armState;

  if (armCount == 3) {
    armCount = 0;
  }

  return armCount;
}
