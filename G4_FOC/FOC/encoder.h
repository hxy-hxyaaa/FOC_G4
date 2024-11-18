#ifndef __ENCODER_H__
#define __ENCODER_H__
#include <spi.h>		
#include <main.h>	
#include "tim.h"




#define MT6816_SPI_CS_H()	  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
#define MT6816_SPI_CS_L()		HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_RESET);
#define MT6816_SPI_Get_HSPI		    (hspi1)





void read_mt6816_data(Angle*ANGLE);
void read_g_MT6816(Angle*ANGLE ,float angle);


/*            6835              */
#define MT6835_SPI_CS_H()	  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
#define MT6835_SPI_CS_L()		HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_RESET);
#define MT6835_SPI_Get_HSPI		    (hspi1)
//CMD
#define Read			      0x3000
#define Write 			    0x6000
#define WriteEEPROM	  	0xC000
#define SetZeroPoint	  0x5000
#define ContinuousRead	0xA000

void read_mt6835_data(Angle*ANGLE);
void read_g_MT6835(Angle*ANGLE ,float angle);

#endif /* __ENCODER_H__ */
