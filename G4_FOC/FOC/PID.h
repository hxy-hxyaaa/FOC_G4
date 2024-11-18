#ifndef _PID_H
#define _PID_H

#include "main.h"




void PID_Init(PID* Pid,float kp,float ki,float kd,float sum_max,float pmax,float imax,float dmax,float outmax);
float  PID_Position(PID* Pid,float set ,float real);


#endif
