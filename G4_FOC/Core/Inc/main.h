/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
//����һЩ���õ��������Ͷ̹ؼ��� 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  



typedef struct{

	float Pout;
	float Iout;
	float Dout;
	float out;
	
	float err;
	float lest_err;	
	float sum_error;
	float sum_max;
	
	float Kp;
	float Ki;
	float Kd;
	
	float PMAX;
	float IMAX;
	float DMAX;
	float OutMAX;	
}PID;


typedef struct
{


  float theta;   // �Ƕ�
  float sin_val; // �˽Ƕȶ�Ӧ������ֵ
  float cos_val; // �˽Ƕȶ�Ӧ������ֵ

  float i_a; // A �����
  float i_b; // B �����
  float i_c; // C �����

  float v_a; // A ���ѹ
  float v_b; // B ���ѹ
  float v_c; // C ���ѹ

  float i_d; // D ����ϵ����
  float i_q; // Q ����ϵ����

  float v_d; // D ����ϵ��ѹ
  float v_q; // Q ����ϵ��ѹ

  float i_alpha; // Alpha ����ϵ����
  float i_beta;  // Beta ����ϵ����

  float v_alpha; // Alpha ����ϵ��ѹ
  float v_beta;  // Beta ����ϵ��ѹ

  int dtc_a; // A �� PWM ռ�ձ�
  int dtc_b; // B �� PWM ռ�ձ�
  int dtc_c; // C �� PWM ռ�ձ�

} foc_para_t;

typedef struct
{
	float ia;
	float ib;
	float ic;
	
	float reality_ia;
	float reality_ib;
	float reality_ic;
	
	float ia_off;
	float ib_off;
	float ic_off;
 
} mc_adc_data;

typedef struct{
float now_angle;
float lest_angle;
float CNT;
float reality_angle; //�Ƕ�
float	reality_radian;//����
float speed;
float speed_L;
float deviation_ang;		

}Angle;



#define set_dtc_a(value)     __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, value)
#define set_dtc_b(value)     __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, value)
#define set_dtc_c(value)     __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, value)



// ����FOC�㷨����ĳ���
#define M_PI (3.14159265358f)         // Բ����
#define M_2PI (6.28318530716f)        // 2��Բ����
#define SQRT3 (1.73205080757f)        // 3��ƽ����
#define SQRT3_BY_2 (0.86602540378f)   // 3��ƽ������һ��
#define ONE_BY_SQRT3 (0.57735026919f) // 1����3��ƽ����
#define TWO_BY_SQRT3 (1.15470053838f) // 2����3��ƽ����

#define SQ(x) ((x) * (x))             // ��ƽ��
#define ABS(x) ((x) > 0 ? (x) : -(x)) // �����ֵ

#define min(x, y) (((x) < (y)) ? (x) : (y)) // ȡ��Сֵ
#define max(x, y) (((x) > (y)) ? (x) : (y)) // ȡ�ϴ�ֵ


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_15
#define LED3_GPIO_Port GPIOC
#define K4_Pin GPIO_PIN_6
#define K4_GPIO_Port GPIOC
#define K2_Pin GPIO_PIN_7
#define K2_GPIO_Port GPIOC
#define K3_Pin GPIO_PIN_8
#define K3_GPIO_Port GPIOC
#define K4C9_Pin GPIO_PIN_9
#define K4C9_GPIO_Port GPIOC
#define SPI1_CS_Pin GPIO_PIN_2
#define SPI1_CS_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
