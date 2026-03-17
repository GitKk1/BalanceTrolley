#include "Driver_MPU6050.h"
#include "i2c.h"
// 加速度      角速度
int16_t AX, AY, AZ, GX, GY, GZ; // 定义用于存放各个数据的变量
double last_angle = 0.0;
/**
 * 函    数：MPU6050初始化函数
 * 参    数：hi2c: I2C外设句柄
 * 返 回 值：HAL状态: HAL_OK 成功, 其他为失败
 */

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
  HAL_StatusTypeDef status;
  uint8_t data;

  // 1. 唤醒设备（退出睡眠模式）
  data = 0x01; // 写入0x01到电源管理寄存器
  status = HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_PWR_MGMT_1,
                             I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
  if (status != HAL_OK)
    return status;
  HAL_Delay(100); // 等待设备稳定

  // 1. 唤醒设备（退出睡眠模式）
  data = 0x00; // 写入0x00到电源管理寄存器
  status = HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_PWR_MGMT_2,
                             I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
  if (status != HAL_OK)
    return status;
  HAL_Delay(100); // 等待设备稳定

  // 2. 设置采样率分频（默认1kHz采样率）
  data = 0x09; // 1kHz/(1+9)=100Hz
  status = HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_SMPLRT_DIV,
                             I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
  if (status != HAL_OK)
    return status;

  // 3. 配置DLPF（数字低通滤波器）
  data = 0x06; // 加速度计带宽5Hz，陀螺仪带宽5Hz
  status = HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_CONFIG,
                             I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
  if (status != HAL_OK)
    return status;

  // 4. 配置陀螺仪量程
  data = 0x18; // ±2000°/s
  status = HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_GYRO_CONFIG,
                             I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
  if (status != HAL_OK)
    return status;

  // 5. 配置加速度计量程
  data = 0x18; // ±16g
  status = HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_ACCEL_CONFIG,
                             I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
  if (status != HAL_OK)
    return status;

  return HAL_OK;
}

/**
 * 函    数：MPU6050获取数据
 * 参    数：AccX AccY AccZ 加速度计X、Y、Z轴的数据，使用输出参数的形式返回，范围：-32768~32767
 * 参    数：GyroX GyroY GyroZ 陀螺仪X、Y、Z轴的数据，使用输出参数的形式返回，范围：-32768~32767
 * 返 回 值：无
 */
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
  uint8_t DataH, DataL; // 定义数据高8位和低8位的变量

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, I2C_MEMADD_SIZE_8BIT, 100);
  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_ACCEL_XOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, I2C_MEMADD_SIZE_8BIT, 100);
  *AccX = (DataH << 8) | DataL; // 数据拼接，通过输出参数返回

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_ACCEL_YOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, I2C_MEMADD_SIZE_8BIT, 100);
  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_ACCEL_YOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, I2C_MEMADD_SIZE_8BIT, 100);
  *AccY = (DataH << 8) | DataL; // 数据拼接，通过输出参数返回

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_ACCEL_ZOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, I2C_MEMADD_SIZE_8BIT, 100);
  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_ACCEL_ZOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, I2C_MEMADD_SIZE_8BIT, 100);
  *AccZ = (DataH << 8) | DataL; // 数据拼接，通过输出参数返回

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_GYRO_XOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, I2C_MEMADD_SIZE_8BIT, 100);
  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_GYRO_XOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, I2C_MEMADD_SIZE_8BIT, 100);
  *GyroX = (DataH << 8) | DataL; // 数据拼接，通过输出参数返回

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_GYRO_YOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, I2C_MEMADD_SIZE_8BIT, 100);
  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_GYRO_YOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, I2C_MEMADD_SIZE_8BIT, 100);
  *GyroY = (DataH << 8) | DataL; // 数据拼接，通过输出参数返回

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_GYRO_ZOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, I2C_MEMADD_SIZE_8BIT, 100);
  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_GYRO_ZOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, I2C_MEMADD_SIZE_8BIT, 100);
  *GyroZ = (DataH << 8) | DataL; // 数据拼接，通过输出参数返回
}

/**
 * 函    数：MPU6050得到小车倾斜角度
 * 参    数：无
 * 返 回 值：inclination_angle 小车当前的倾斜角度
 */
double MPU6050_GetInclinationAngle(void)
{
  double inclination_angle = 0.0;
  MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
  inclination_angle = atan2((double)AY, (double)AX) / 3.14159 * 180;
  return inclination_angle;
}

/**
 * 函    数：MPU6050得到小车倾斜的角度
 * 参    数：无
 * 返 回 值：inclination_angle 小车倾斜的角度
 */
float MPU6050_AngleCalculate(double temp_last_angle)
{
  float inclination_angle = 0.0f;
  MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
  // 角度计算公式：初始角度 + (陀螺仪Z轴数据 / 总刻度) * 量程 * 时间间隔
  inclination_angle = temp_last_angle + ((GZ / 32768) * 2000) * 0.001;
	last_angle = inclination_angle;
  return inclination_angle;
}
