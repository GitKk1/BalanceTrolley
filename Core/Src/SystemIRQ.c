#include "SystemIRQ.h"


/**
 * 函    数：HAL_TIM_PeriodElapsedCallback  定时器更新中断回调函数
 * 参    数：定时器句柄指针
 * 返 回 值：无
 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {

    }
}
