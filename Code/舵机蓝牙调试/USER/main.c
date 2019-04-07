#include "sys.h"
#include "delay.h"
#include "uart5.h"
#include "servo.h"
#include "timer.h"
#include "string.h"
#include <ctype.h>
#include <stdio.h>
//  RX -- PC12(TX)
//  TX -- PD2 (RX)

char* rp;
char* ch = "-";

u8 servo1[4];
u8 servo2[4];
u8 servo3[4];
u8 servo4[4];
u8 mystr[50];

int servo1_vlaue;
int servo2_vlaue;
int servo3_vlaue;
int servo4_vlaue;

int main(void)
{
    delay_init(168);      //��ʼ����ʱ����
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2

    //uart5_Init(9600);
    //TIM7_Int_Init(100 - 1, 8400 - 1);	//10ms�ж�һ��
    Servo_Init(10000 - 1, 56 - 1);                   // ���PWMƵ��Ϊ300Hz
    while(1)
    {
//        if(UART5_RX_STA & 0x8000)
//        {
//            /*  �ַ����и� */
//            sprintf(servo1, "%s", strtok(UART5_RX_BUF, ch));
//            sprintf(servo2, "%s", strtok(NULL, ch));
//            sprintf(servo3, "%s", strtok(NULL, ch));
//            sprintf(servo4, "%s", strtok(NULL, ch));
//            
//            /* �ַ���תInt */
//            servo1_vlaue = atoi(servo1);
//            servo2_vlaue = atoi(servo2);
//            servo3_vlaue = atoi(servo3);
//            servo4_vlaue = atoi(servo4);
//            
//            /* ���PWM��ֵ */
//            Servo1_SetAngle(servo1_vlaue);
//            Servo2_SetAngle(servo2_vlaue);
//            Servo3_SetAngle(servo3_vlaue);
//            Servo4_SetAngle(servo4_vlaue);
//            
//            /* ������Ϣ */
//            uart5_send_string("\r\n");
//            uart5_send_string("Transform successfully! \r\n");
//            sprintf(mystr, "S1 = %d , S2 = %d , S3 = %d , S4 = %d\r\n",servo1_vlaue,servo2_vlaue,servo3_vlaue,servo4_vlaue);
//            uart5_send_string(mystr);
//            UART5_RX_STA = 0;
//        }

    }
}
