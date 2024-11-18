#include "encoder.h"
#include <stdio.h>
#include "math.h"
#include "spi.h"
void read_g_MT6816(Angle*ANGLE ,float angle)
	
{
	float err_ang;
  ANGLE->now_angle=angle;
	err_ang=ANGLE->now_angle-ANGLE->lest_angle;
if(err_ang>360/2)  
{   ANGLE->CNT--;
    ANGLE->speed=err_ang-360;
}
else if(err_ang<-360/2)  
{   ANGLE->CNT++;
    ANGLE->speed=err_ang+360;
}
else ANGLE->speed=err_ang;
ANGLE->lest_angle=ANGLE->now_angle;
ANGLE->reality_angle=(ANGLE->CNT*360+ANGLE->now_angle);


}


	void read_mt6816_data(Angle*ANGLE)
{	
	 float angle_6816;
	
 	uint8_t u8Data11 = 0x00;
  uint8_t u8Data12 = 0x00;

	uint8_t TxData1=0x83;
	uint8_t TxData2=0x84;	
	
						MT6816_SPI_CS_L();
				HAL_SPI_Transmit(&MT6816_SPI_Get_HSPI,&TxData1,1,10);
				HAL_SPI_Receive(&MT6816_SPI_Get_HSPI,&u8Data11,1,10);
					MT6816_SPI_CS_H();

						MT6816_SPI_CS_L();
				HAL_SPI_Transmit(&MT6816_SPI_Get_HSPI,&TxData2,1,10);
				HAL_SPI_Receive(&MT6816_SPI_Get_HSPI,&u8Data12,1,10);
				  	MT6816_SPI_CS_H();

				angle_6816 = 360-((float)((u8Data11*256+u8Data12)/4)/16384)*360;
      read_g_MT6816(ANGLE,angle_6816);

}


void read_g_MT6835(Angle*ANGLE ,float angle)
	
{
	float err_ang;
  ANGLE->now_angle=angle;
	err_ang=ANGLE->now_angle-ANGLE->lest_angle;
if(err_ang>360/2)  
{   ANGLE->CNT--;
    err_ang-=360;
}
else if(err_ang<-360/2)  
{   ANGLE->CNT++;
    err_ang+=360;
}
 ANGLE->speed=err_ang*300;
ANGLE->lest_angle=ANGLE->now_angle;
ANGLE->reality_angle=(ANGLE->CNT*360+ANGLE->now_angle);


}




void read_mt6835_data(Angle*ANGLE)
{
	
float mt6835_data;
uint32_t 	Angle_6835;
uint16_t 	TxData;
uint16_t 	RxData[3];

	
	MT6835_SPI_CS_L();
	
	TxData = ContinuousRead|0x0003;
	HAL_SPI_TransmitReceive(&MT6835_SPI_Get_HSPI,(unsigned char *)&TxData,(unsigned char *)&RxData,3, 10);

	MT6835_SPI_CS_H();
	
	Angle_6835 = (RxData[1]<<5)|(RxData[2]>>11);
	
  mt6835_data=((float)Angle_6835/2097152)*360;
	   
	read_g_MT6835(ANGLE,mt6835_data);
	
	
}






	
	























