#include "PID.h"
#include "main.h"

void PID_Init(PID* Pid,float kp,float ki,float kd,float sum_max,float pmax,float imax,float dmax,float outmax)
{

	Pid-> Pout=0;
	Pid-> Iout=0;
	Pid-> Dout=0;
	Pid-> out=0;
	
	Pid-> err=0.0f;
	Pid-> lest_err=0.0f;

	Pid->sum_error=0;
	Pid->sum_max=sum_max;
	Pid-> Kp=kp;
	Pid-> Ki=ki;
	Pid-> Kd=kd;
	
	Pid-> PMAX=pmax;
	Pid-> IMAX=imax;
	Pid-> DMAX=dmax;
	Pid->OutMAX=outmax;	

}

float  PID_Position(PID* Pid,float set ,float real)//Î»ÖÃ
{

	Pid->err = set - real;
	Pid->sum_error += Pid->err;

	Pid->Pout=Pid->Kp * Pid->err ;
	Pid->Pout > Pid->PMAX ? Pid->Pout = Pid->PMAX : 1;
	Pid->Pout < -Pid->PMAX ? Pid->Pout = -Pid->PMAX : 1;

	Pid->Iout=Pid->Ki * Pid->sum_error ;
	Pid->Iout > Pid->IMAX ? Pid->Iout=Pid->IMAX :1;
	Pid->Iout < -Pid->IMAX ?Pid->Iout = -Pid->IMAX :1;

	Pid->sum_error > Pid->sum_max ? Pid->sum_error=Pid->sum_max:1;
	Pid->sum_error < -Pid->sum_max ? Pid->sum_error=-Pid->sum_max:1;	

	Pid->Dout=Pid->Kd * ( Pid->err - Pid->lest_err );
	Pid->Dout > Pid->DMAX ? Pid->Dout = Pid->DMAX : 1;
	Pid->Dout < -Pid->DMAX ? Pid->Dout = -Pid->DMAX : 1;

	Pid->out=Pid->Pout+Pid->Iout+Pid->Dout;
	Pid->out > Pid->OutMAX ? Pid->out = Pid->OutMAX : 1;
	Pid->out < -Pid->OutMAX ? Pid->out = -Pid->OutMAX : 1;

	Pid->lest_err = Pid->err;

	return Pid->out;

}



