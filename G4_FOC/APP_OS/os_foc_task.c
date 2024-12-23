#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "encoder.h"
#include "PID.h"
#include "math.h"
#include "foc_use.h"
#include "observer.h"
extern PLL_EASY PLL_6835;
extern foc_para_t FOC_DATA;
extern Angle mt6835;
extern mc_adc_data ADC_DATA;
extern int foc_ok;
PLL_ang PLL_OBSERVER;
PID_PI PID_IQ,PID_ID;

PID PID_SPEED;
PID PID_ANG;
float MY_SPEED;
float MY_ANG;
extern float my_iq;
extern float my_id;
observer_state flux_observer;
float ANG_SPEED;
float ANG_SPEED_ADD;
 void StartFOC_Task(void const * argument)
{
  /* USER CODE BEGIN StartFOC_Task */
		set_dtc_a(0);
		set_dtc_b(0);	
		set_dtc_c(0);		
		osDelay(100);		
for(int i=0;i<100;i++)
{
	   osDelay(1);
		 ADC_DATA.ia_off += (float)(ADC1->JDR1)*0.01f;
		 ADC_DATA.ib_off += (float)(ADC1->JDR2)*0.01f;
		 ADC_DATA.ic_off += (float)(ADC1->JDR3)*0.01f;
	
}	

		set_dtc_a(0);
		set_dtc_b(0);	
		set_dtc_c(0);		
		osDelay(100);	

 PID_Init(&PID_SPEED,
          0.1,0.01,0,
          500,
          5,5,0,
				  10);
 PID_Init(&PID_ANG,
          4,0,5,
          0,
          200,0,50,
				  200);
 PI_init(&PID_IQ ,0.00004F,5000.0F,0.0003307f,0.3246f,24.0F,10.0F);
 PI_init(&PID_ID ,0.00004F,5000.0F,0.0004909f,0.3246f,24.0F,10.0F);
 
 PLL_ESAY_init(&PLL_6835    ,0.00004F,300.0F);
 PLL_ang_init (&PLL_OBSERVER,0.00004F,60.0F);

 FOC_observer_init(&flux_observer,0.0003307f,0.0004909f,0.3246f,0.008673f,13000000,0.00004 );
		osDelay(100);	
	   foc_ok=1;

	  TickType_t xLastWakeTime;
    const TickType_t xDelay1ms = pdMS_TO_TICKS( 1 );
    xLastWakeTime = xTaskGetTickCount();

  /* Infinite loop */
  for(;;)
  {
//		ANG_SPEED+=ANG_SPEED_ADD;
//		MY_ANG=360*sin(ANG_SPEED*2*M_PI);
// 

//		MY_SPEED= PID_Position(&PID_ANG,MY_ANG,mt6835.reality_angle);
    my_iq= PID_Position(&PID_SPEED,MY_SPEED,PLL_6835.pll_speed_ver);




   vTaskDelayUntil( &xLastWakeTime, xDelay1ms );

  }
  /* USER CODE END StartFOC_Task */
}


 void StartKEY_LED_Task(void const * argument)
{
  /* USER CODE BEGIN StartKEY_LED_Task */
	

	
	
  /* Infinite loop */
  for(;;)
  {
		
		
		
    osDelay(1);
  }
  /* USER CODE END StartKEY_LED_Task */
}


