#ifndef _FOC_I_H
#define _FOC_I_H

#include "main.h"

void FOC_COUNTER_I(foc_para_t *foc,
									 float ang,
									 float IQ,float ID);
									 
void FOC_I(foc_para_t *foc,
	                 PID* Pid_IQ,PID* Pid_ID,
									 float ang,
									 float IA,float IB,float IC,
									 float IQ,float ID);									 
									 
void foc_task(void);




#endif
