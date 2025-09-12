#include "board.h"
#include "delay.h"
#include "ZDT_X42_V2.h"
#include "OLED.h"
#include "move.h"
#include "mpu6050.h"
#include "inv_mpu.h"

/**
	*	@brief		MAIN函数
	*	@param		无
	*	@retval		无
	*/
int main(void) 
{  
    board_init();   
    OLED_Init();    
    MPU6050_Init();
    MPU6050_DMP_Init();

    // int16_t gx,gy,gz;
    // int16_t ax,ay,az;
    float roll,pitch,yaw;
    while(1)
    {
        // MPU_Get_Gyroscope(&gx,&gy,&gz);
        // MPU_Get_Accelerometer(&ax,&ay,&az);
        MPU6050_DMP_Get_Data(&roll,&pitch,&yaw);

        OLED_ShowSignedNum(1,1,(int16_t)(roll),5);
        OLED_ShowSignedNum(2,1,(int16_t)(pitch),5);
        OLED_ShowSignedNum(3,1,(int16_t)(yaw),5);

        // OLED_ShowSignedNum(1,1,gx,5);
        // OLED_ShowSignedNum(2,1,gy,5);
        // OLED_ShowSignedNum(3,1,gz,5); 
        // OLED_ShowSignedNum(1,8,ax,5);
        // OLED_ShowSignedNum(2,8,ay,5);
        // OLED_ShowSignedNum(3,8,az,5);
        delay_ms(5);
    }
}
