#ifndef __DRIVER_MPU6050_H_
#define __DRIVER_MPU6050_H_


#include "main.h"

#define MPU6050_ADDR		0xD0

/* 采样率分频器寄存器
 * 用于设置传感器数据输出速率，实际输出频率 = 陀螺仪输出频率 / (1 + SMPLRT_DIV)
 * 陀螺仪输出频率通常为1kHz（取决于DLPF设置） */
#define MPU6050_SMPLRT_DIV      0x19

/* 配置寄存器
 * 主要配置数字低通滤波器(DLPF)的带宽，用于滤波原始传感器数据，降低噪声 */
#define MPU6050_CONFIG          0x1A

/* 陀螺仪配置寄存器
 * 设置陀螺仪的量程范围：±250, ±500, ±1000, ±2000 °/s */
#define MPU6050_GYRO_CONFIG     0x1B

/* 加速度计配置寄存器
 * 设置加速度计的量程范围：±2g, ±4g, ±8g, ±16g */
#define MPU6050_ACCEL_CONFIG    0x1C

/* 加速度计X轴数据高8位寄存器 */
#define MPU6050_ACCEL_XOUT_H    0x3B
/* 加速度计X轴数据低8位寄存器 */
#define MPU6050_ACCEL_XOUT_L    0x3C
/* 加速度计Y轴数据高8位寄存器 */
#define MPU6050_ACCEL_YOUT_H    0x3D
/* 加速度计Y轴数据低8位寄存器 */
#define MPU6050_ACCEL_YOUT_L    0x3E
/* 加速度计Z轴数据高8位寄存器 */
#define MPU6050_ACCEL_ZOUT_H    0x3F
/* 加速度计Z轴数据低8位寄存器 */
#define MPU6050_ACCEL_ZOUT_L    0x40


/* 温度传感器数据高8位寄存器
 * 温度计算公式：Temperature = TEMP_OUT / 340 + 36.53 (°C) */
#define MPU6050_TEMP_OUT_H      0x41
/* 温度传感器数据低8位寄存器 */
#define MPU6050_TEMP_OUT_L      0x42


/* 陀螺仪X轴数据高8位寄存器 */
#define MPU6050_GYRO_XOUT_H     0x43
/* 陀螺仪X轴数据低8位寄存器 */
#define MPU6050_GYRO_XOUT_L     0x44
/* 陀螺仪Y轴数据高8位寄存器 */
#define MPU6050_GYRO_YOUT_H     0x45
/* 陀螺仪Y轴数据低8位寄存器 */
#define MPU6050_GYRO_YOUT_L     0x46
/* 陀螺仪Z轴数据高8位寄存器 */
#define MPU6050_GYRO_ZOUT_H     0x47
/* 陀螺仪Z轴数据低8位寄存器 */
#define MPU6050_GYRO_ZOUT_L     0x48

/* 电源管理寄存器1
 * 最重要的控制寄存器之一：
 * - 设备复位
 * - 休眠模式控制
 * - 时钟源选择（内部8MHz，陀螺仪PLL等）
 * - 温度传感器使能 */
#define MPU6050_PWR_MGMT_1      0x6B

/* 电源管理寄存器2
 * 控制各传感器通道的使能/待机：
 * - 加速度计XYZ轴独立使能
 * - 陀螺仪XYZ轴独立使能 */
#define MPU6050_PWR_MGMT_2      0x6C

/* 设备ID寄存器
 * 读取该寄存器应返回固定值0x68（或0x69，取决于AD0引脚电平）
 * 用于验证I2C通信是否正常及设备是否正确连接 */
#define MPU6050_WHO_AM_I        0x75


HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
double MPU6050_GetInclinationAngle(void);
float MPU6050_AngleCalculate(double initial_angle);

#endif
