#include "Driver_Motor.h"

#define Ain1_Pin GPIO_PIN_10
#define Ain1_GPIO_Port GPIOB
#define Ain2_Pin GPIO_PIN_11
#define Ain2_GPIO_Port GPIOB
#define Bin2_Pin GPIO_PIN_13
#define Bin2_GPIO_Port GPIOB
#define Bin1_Pin GPIO_PIN_14
#define Bin1_GPIO_Port GPIOB

void MotorAdvance(void)//小车前进
{
    HAL_GPIO_WritePin(Ain1_GPIO_Port, Ain1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Ain2_GPIO_Port, Ain2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Bin1_GPIO_Port, Bin1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Bin2_GPIO_Port, Bin2_Pin, GPIO_PIN_SET);
}
