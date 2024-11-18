#include "FOC_I.h"
#include "main.h"
#include "foc_use.h"
#include "PID.h"
#include "adc.h"
#include "tim.h"
#include "encoder.h"
#include "math.h"
#include "observer.h"
#include "arm_math.h"
mc_adc_data ADC_DATA;

foc_para_t FOC_DATA;
Angle mt6835;
float ang_14;
float ang_E,ang_E_ERR=193;
float my_iq,my_id;
int foc_ok=0;//初始化
int foc_cnt=0;
PLL_EASY PLL_6835;

float my_ang,my_mt;
extern PID_PI PID_IQ;
extern PID_PI PID_ID;
extern observer_state flux_observer;

float normalize_angle(float angle)
{
	float a = fmod(angle/57.295779513f, 2 * M_PI); // 取余运算可以用于归一化
	return a >= 0 ? a : (a + 2 * M_PI);
}

float absolute_value(float data)
{
	return data>=0 ? data : -data;
}



void foc_task(void)
{
	if(foc_ok==1)
	{
			
//	/*SPI*/
  read_mt6835_data(&mt6835);
	ang_14=mt6835.now_angle*14+ang_E_ERR;
  while (ang_14 <    0) { ang_14 +=  360; }
	while (ang_14 >= 360) { ang_14 -=  360; }
  ang_E=ang_14*0.0174532925199F;
   PLL_ESAY_set(&PLL_6835 ,ang_E);
   PLL_ESAY_run(&PLL_6835);	
	

//	/*ADC*/
	ADC_DATA.ia=(float)(ADC1->JDR1)-ADC_DATA.ia_off;
	ADC_DATA.ib=(float)(ADC1->JDR2)-ADC_DATA.ib_off;		
	ADC_DATA.ic=(float)(ADC1->JDR3)-ADC_DATA.ic_off;		
	ADC_DATA.reality_ia=ADC_DATA.ia*0.0080586f;
	ADC_DATA.reality_ib=ADC_DATA.ib*0.0080586f;		
	ADC_DATA.reality_ic=ADC_DATA.ic*0.0080586f;
		
	FOC_DATA.i_b=ADC_DATA.reality_ia;

	FOC_DATA.i_a=ADC_DATA.reality_ib;		

	FOC_DATA.i_c=ADC_DATA.reality_ic;			
	
		


	  clarke_transform(&FOC_DATA);//CLARKE
		
 
    FOC_DATA.theta=ang_E;
    sin_cos_val(&FOC_DATA);//角度		
		
	  park_transform(&FOC_DATA);//PACK

   PI_set (&PID_IQ ,my_iq,FOC_DATA.i_q);
   PI_run (&PID_IQ);
   FOC_DATA.v_q=  (PI_get (&PID_IQ)/24)*1500;
	 
   PI_set (&PID_ID ,my_id,FOC_DATA.i_d);
   PI_run (&PID_ID);
   FOC_DATA.v_d=  (PI_get (&PID_ID)/24)*1500;

    inverse_park(&FOC_DATA);//PARK逆
	  svpwm_midpoint(&FOC_DATA);  


		 
		
//		/*PWM*/
		set_dtc_a(FOC_DATA.v_a+1500);
		set_dtc_b(FOC_DATA.v_b+1500);	
		set_dtc_c(FOC_DATA.v_c+1500);			
		
	
	}

	else 
  {
	
	}
		htim1.Instance->RCR=1;

}

