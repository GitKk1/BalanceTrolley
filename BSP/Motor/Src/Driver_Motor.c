#include "Driver_Motor.h"

void MotorAdvance(void) // 小车前进
{
    HAL_GPIO_WritePin(Ain1_GPIO_Port, Ain1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Ain2_GPIO_Port, Ain2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Bin1_GPIO_Port, Bin1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Bin2_GPIO_Port, Bin2_Pin, GPIO_PIN_RESET);
}

void MotorRetreat(void) // 小车前进
{
    HAL_GPIO_WritePin(Ain1_GPIO_Port, Ain1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Ain2_GPIO_Port, Ain2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Bin1_GPIO_Port, Bin1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Bin2_GPIO_Port, Bin2_Pin, GPIO_PIN_SET);
}
