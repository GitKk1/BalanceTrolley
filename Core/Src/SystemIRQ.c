#include "SystemIRQ.h"
#include "Driver_MPU6050.h"

#if DEBUG_MODE
float test_inclination_angle = 0.0; // 定义用于存放倾斜角度的变量
#endif

double last_angle = 0.0;

/**
 * 函    数：HAL_TIM_PeriodElapsedCallback  定时器更新中断回调函数
 * 参    数：定时器句柄指针
 * 返 回 值：无
 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint8_t first_executing_flag = 1;
    if (htim->Instance == TIM3)//1ms定时器
    {
			if(first_executing_flag != 0)
			{
				last_angle = MPU6050_GetInclinationAngle();//获取小车的初始倾斜角度
				first_executing_flag = 0;
			}
			test_inclination_angle = MPU6050_AngleCalculate(last_angle); // 计算倾斜角度
    }
}
