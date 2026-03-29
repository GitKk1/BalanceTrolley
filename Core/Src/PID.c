#include "PID.h"

PID_Controller pid={
    .Kp = 2.0f, // 比例系数
    .Ki = 0.2f, // 积分系数
    .Kd = 0.1f, // 微分系数

    .setpoint = 0.0f,       // 目标值
    .integral = 0.0f,       // 积分项
    .previous_error = 0.0f, // 上一次误差
    .output = 0.0f,// 输出值
}; 


void PIDInit(PID_Controller *pid, float Kp, float Ki, float Kd)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->setpoint = 0.0f;
    pid->integral = 0.0f;
    pid->previous_error = 0.0f;
}   



void PIDCompute(PID_Controller *pid, float input) 
{
    float error = pid->setpoint - input; // 计算误差
    pid->integral += error; // 更新积分项
    float derivative = error - pid->previous_error; // 计算微分项

    pid->output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative; // 计算PID输出

    pid->previous_error = error; // 更新上一次误差
    // 输出可以通过返回值或者指针参数返回，这里假设直接使用输出变量
}
