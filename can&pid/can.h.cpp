#include "main.h"
#include "dma.h"
#include "fdcan.h"
#include "memorymap.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

typedef struct 
{ 
    int16_t Rotor_Angle;  // ת�ӽǶ� 0~8192 0~360��
    int16_t Speed_RPM;    // ÿ���ӵ��ת��(RPM)
    int16_t Real_Current; // ʵ�ʵ������ֵ -16384~+16384
    uint16_t Temp;        // ����¶�
    int16_t Last_Angle;   // �ϴζ�ȡ���ĽǶ�
    int16_t Offset_Angle; // ��ʼλ��ƫ�ƽǶ�
    int32_t Round_Cnt;    // ת����תȦ��
    int32_t Total_Angle;  // �ܽǶ�
    uint32_t Msg_Cnt;     // ��Ϣ����
} motor_measure_t; 

/*CAN���յ�ID*/
typedef enum
{
	//add by langgo
	CAN_2006Moto1_ID = 0x201,
	CAN_2006Moto2_ID = 0x202,
	CAN_2006Moto3_ID = 0x203,
	CAN_2006Moto4_ID = 0x204
	
}CAN_Message_ID;


void get_moto_measure(motor_measure_t *ptr);
void get_moto_offset(motor_measure_t *ptr);
void CAN_Send(FDCAN_HandleTypeDef* can,int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4 );
void CAN_Open(FDCAN_HandleTypeDef* can);
uint8_t fdcanx_receive(FDCAN_HandleTypeDef *hfdcan, uint16_t *rec_id, uint8_t *buf);
