/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for KEY_LED_Task */
osThreadId_t KEY_LED_TaskHandle;
const osThreadAttr_t KEY_LED_Task_attributes = {
  .name = "KEY_LED_Task",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for FOC_Task */
osThreadId_t FOC_TaskHandle;
const osThreadAttr_t FOC_Task_attributes = {
  .name = "FOC_Task",
  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 256 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartKEY_LED_Task(void *argument);
void StartFOC_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of KEY_LED_Task */
  KEY_LED_TaskHandle = osThreadNew(StartKEY_LED_Task, NULL, &KEY_LED_Task_attributes);

  /* creation of FOC_Task */
  FOC_TaskHandle = osThreadNew(StartFOC_Task, NULL, &FOC_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartKEY_LED_Task */
/**
  * @brief  Function implementing the KEY_LED_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartKEY_LED_Task */
__weak void StartKEY_LED_Task(void *argument)
{
  /* USER CODE BEGIN StartKEY_LED_Task */
	

	
	
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartKEY_LED_Task */
}

/* USER CODE BEGIN Header_StartFOC_Task */
/**
* @brief Function implementing the FOC_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFOC_Task */
__weak void StartFOC_Task(void *argument)
{
  /* USER CODE BEGIN StartFOC_Task */

  /* Infinite loop */
  for(;;)
  {

   osDelay(1);

  }
  /* USER CODE END StartFOC_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

