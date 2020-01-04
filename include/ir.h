#ifndef IR_H_
#define IR_H_

// Begin C++ extern to C
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Code to low edge of IR sensor
 *
 * @param int irPort
 * @return bool
 */
int ir_detect_low(int irPort);
int ir_detect_high(int irPort);
int ir_detect_edge(int irPort);
int ir_count_low(int irPort, int reset);
int ir_armAuto_count(int irPort);

// End C++ extern to C
#ifdef __cplusplus
}
#endif

#endif
