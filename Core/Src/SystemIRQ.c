#include "SystemIRQ.h"
#include "Driver_MPU6050.h"

#if DEBUG_MODE
float test_inclination_angle = 0.0; // 定义用于存放倾斜角度的变量
#endif



/**
 * 函    数：HAL_TIM_PeriodElapsedCallback  定时器更新中断回调函数
 * 参    数：定时器句柄指针
 * 返 回 值：无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)//1ms定时器
    {
			test_inclination_angle = MPU6050_AngleCalculate(last_angle); // 计算倾斜角度
    }
}
