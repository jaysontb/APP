#include "board.h"
#include "delay.h"
#include "ZDT_X42_V2.h"
#include "OLED.h"
#include "move.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "motor.h"

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

	// 定义接收数据数组、接收数据长度
	uint8_t rxCmd[128] = {0}; uint8_t rxCount = 0;
    //float motor1_pos = 0.0f;
    float motor2_pos = 0.0f;

	// //向电机1发送带同步标志的速度指令 (snF = 1)
	// ZDT_X42_V2_Velocity_Control(1, 0, 1000, 100.0f, 0);
	// delay_ms(5); // 短暂延时，确保指令被接收

	//向电机2发送带同步标志的速度指令 (snF = 1)
	ZDT_X42_V2_Velocity_Control(2, 0, 1000, 100.0f, 0);
	delay_ms(5); // 此延时已不再需要，usart_SendCmd() 通过硬件标志位确保发送完成

	// //发送同步运动指令到广播地址0，触发所有电机同时启动
	// ZDT_X42_V2_Synchronous_motion(0);
    
    while(1)
	{
        // // 实时读取电机1位置（在电机转动过程中）
        // ZDT_X42_V2_Read_Sys_Params(1, S_CPOS);        
        // // 等待返回数据
        // ZDT_X42_V2_Receive_Data(rxCmd, &rxCount);
        // if(rxCmd[0] == 1 && rxCmd[1] == 0x36 && rxCount == 8)
        // {
        //     // 获取电机实时角度返回值
        //     motor1_pos = ((uint32_t)rxCmd[3] << 24) | ((uint32_t)rxCmd[4] << 16) |  
        //           ((uint32_t)rxCmd[5] << 8) | (uint32_t)rxCmd[6];
            
        //     // 缩小10倍，并判断符号，得到真正的实时角度
        //     motor1_pos = motor1_pos * 0.1f; 
        //     if(rxCmd[2]) { motor1_pos = -motor1_pos; }
            
        //     // 在OLED上显示实时位置
        //     OLED_ShowNum(1, 1, (uint32_t)motor1_pos, 4);
        // }

        // 实时读取电机2位置（在电机转动过程中）
        ZDT_X42_V2_Read_Sys_Params(2, S_CPOS);        
        // 等待返回数据
        ZDT_X42_V2_Receive_Data(rxCmd, &rxCount); 
        
        // 验证数据有效性并解析位置
        if(rxCmd[0] == 2 && rxCmd[1] == 0x36 && rxCount == 8)
        {
            // 获取电机实时角度返回值
            motor2_pos = ((uint32_t)rxCmd[3] << 24) | ((uint32_t)rxCmd[4] << 16) |  
                  ((uint32_t)rxCmd[5] << 8) | (uint32_t)rxCmd[6];
            
            // 缩小10倍，并判断符号，得到真正的实时角度
            motor2_pos = motor2_pos * 0.1f; 
            if(rxCmd[2]) { motor2_pos = -motor2_pos; }
            
            // 在OLED上显示实时位置
            OLED_ShowNum(2, 1, (uint32_t)motor2_pos, 4);
        }
        
        delay_ms(5);  // 5ms读取一次，避免读取过于频繁
	}
}
