///****************************************************************************
// *  Copyright (C) 2018 RoboMaster.
// *
// *  This program is free software: you can redistribute it and/or modify
// *  it under the terms of the GNU General Public License as published by
// *  the Free Software Foundation, either version 3 of the License, or
// *  (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *  GNU General Public License for more details.
// *
// *  You should have received a copy of the GNU General Public License
// *  along with this program. If not, see <http://www.gnu.org/licenses/>.
// ***************************************************************************/
// 
//#include "pid.h"

///**
//  * @brief  init pid parameter
//  * @param  pid struct
//    @param  parameter
//  * @retval None
//  */
//void pid_init(pid_struct_t *pid,
//              float kp,
//              float ki,
//              float kd,
//              float i_max,
//              float out_max)
//{
//  pid->kp      = kp;
//  pid->ki      = ki;
//  pid->kd      = kd;
//  pid->i_max   = i_max;
//  pid->out_max = out_max;
//}

///**
//  * @brief  pid calculation
//  * @param  pid struct
//    @param  reference value
//    @param  feedback value
//  * @retval calculation result
//  */
//float pid_calc(pid_struct_t *pid, float ref, float fdb)
//{
//  pid->ref = ref;
//  pid->fdb = fdb;
//  pid->err[1] = pid->err[0];
//  pid->err[0] = pid->ref - pid->fdb;
//  
//  pid->p_out  = pid->kp * pid->err[0];
//  pid->i_out += pid->ki * pid->err[0];
//  pid->d_out  = pid->kd * (pid->err[0] - pid->err[1]);
//  pid->i_out = LIMIT_MIN_MAX(pid->i_out, pid->i_max, pid->i_max);
//  
//  pid->output = pid->p_out + pid->i_out + pid->d_out;
//  pid->output = LIMIT_MIN_MAX(pid->output, pid->out_max, pid->out_max);
//  return pid->output;
//}

//float LIMIT_MIN_MAX(float i_out,float i_max,float i_min)
//{
//	if(i_out>i_max)
//	{
//		return i_max;
//	}
//	else if(i_out<-i_min)
//	{
//		return i_min;
//	}
//	
//	return i_out;
//}




#include "pid.h"

// ����PID�ṹ��


// ��ʼ������ʽPID����
void IncrementalPID_init(IncrementalPID_struct_t *pid,
                         float kp,
                         float ki,
                         float kd,
                         float i_max,
                         float out_max) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->i_max = i_max;
    pid->out_max = out_max;
    pid->err[0] = 0;
    pid->err[1] = 0;
    pid->err[2] = 0;
    pid->last_output = 0;
}

// ����ʽPID���㺯��
float IncrementalPID_calc(IncrementalPID_struct_t *pid, float ref, float fdb) {
    pid->err[2] = pid->err[1];
    pid->err[1] = pid->err[0];
    pid->err[0] = ref - fdb;  // ���㵱ǰ���

    // �������������
    float p_increment = pid->kp * (pid->err[0] - pid->err[1]);
    // �������������
    float i_increment = pid->ki * pid->err[0];
    // ����΢��������
    float d_increment = pid->kd * (pid->err[0] - 2 * pid->err[1] + pid->err[2]);

    // �������޷�
    if (i_increment > pid->i_max) {
        i_increment = pid->i_max;
    } else if (i_increment < -pid->i_max) {
        i_increment = -pid->i_max;
    }

    // �������������
    float output_increment = p_increment + i_increment + d_increment;

    // ���㵱ǰ������
    float output = pid->last_output + output_increment;

    // ����޷�
    if (output > pid->out_max) {
        output = pid->out_max;
    } else if (output < -pid->out_max) {
        output = -pid->out_max;
    }

    // ������һʱ�̵����ֵ
    pid->last_output = output;

    return output;
}

//int main() {
//    IncrementalPID_struct_t pid;
//    float kp = 0.5;
//    float ki = 0.1;
//    float kd = 0.2;
//    float i_max = 10;
//    float out_max = 20;
//    float reference_value = 100;  // �ο�ֵʾ��
//    float feedback_value = 80;    // ����ֵʾ��

//    IncrementalPID_init(&pid, kp, ki, kd, i_max, out_max);

//    float output = IncrementalPID_calc(&pid, reference_value, feedback_value);

//    printf("���������: %.2f\n", output);

//    return 0;
//}
