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

PID_PI PID_IQ,PID_ID;

PID PID_SPEED;
float MY_SPEED;
extern float my_iq;
extern float my_id;
observer_state flux_observer;

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
          0.01,0.001,0,
          5000,
          5,5,0,
				  5);

 PI_init(&PID_IQ ,0.00004F,1000.0F,0.000107F,0.107f,24.0F,10.0F);
 PI_init(&PID_ID ,0.00004F,1000.0F,0.000107F,0.107f,24.0F,10.0F);
 
 PLL_ESAY_init(&PLL_6835,0.00004F,300.0F);

		osDelay(100);	
	   foc_ok=1;

	  TickType_t xLastWakeTime;
    const TickType_t xDelay1ms = pdMS_TO_TICKS( 1 );
    xLastWakeTime = xTaskGetTickCount();

  /* Infinite loop */
  for(;;)
  {

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


