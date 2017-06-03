/*
 * knowledge.h
 * autogenerated
*/

#include "ahrsmath.h"

#ifndef STROKES_H_
#define STROKES_H_

#define DIMENTION 3
#define STROKE_MAX_LENGTH 4096
#define KP_INIT 10.0
#define KI_INIT 0.0
#define KP_WORK 1.25
#define KI_WORK 0.025
#define INIT_EDGE 5.0
#define SEGMENTATION 128
#define GYRO_SCALE 0.00106526443603
#define ACC_SCALE 0.00239501953125
#define G_CONST 9.81
#define STROKES_COUNT 11
#define MIN_DIMENTION 3.0
#define ACCELERATION_TIME_CONST 0.2
#define GYRO_MIN 1
#define GYRO_TIMEOUT 100
#define MIN_STROKE_LENGTH 20
#define COMPARE_LIMIT 1.5
#define CALIBRATION 0
#define IDLE 1
#define STATES_OFFSET 2
#define STROKE_DONE 2
#define TOO_SHORT 3
#define STRANGE 7
#define UNSUPPORTED 6
#define NOT_IN_ACTION 1
#define TOO_LONG 4
#define IN_ACTION 0
#define TOO_SMALL 5

extern const Vector STROKES[STROKES_COUNT][SEGMENTATION];


#endif
