#ifndef _PID_H_
#define _PID_H_

#include "main.h"

typedef struct
{
	float Kp; // 比例系数
	float Ki; // 积分系数
	float Kd; // 微分系数

	float setpoint;       // 目标值
	float integral;       // 积分项
	float previous_error; // 上一次误差
	float output; // 输出值
} PID_Controller;
extern PID_Controller pid;

void PIDCompute(PID_Controller *pid, float input);
void PIDInit(PID_Controller *pid, float Kp, float Ki, float Kd);

#endif
