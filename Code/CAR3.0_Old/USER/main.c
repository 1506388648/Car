#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "servo.h"
#include "oled.h"
#include "usart3.h"
#include "led.h"
#include "motor.h"
#include "encoder.h"
#include "move.h"
#include "sensor.h"
#include "beep.h"
#include "ano.h"
#include "key.h"
/**************************************************************************************

USART1: TXD(P4)	--> RXD (PB11)     ͨ��Э�飺 "check\n" -->  "OK\r\n"     ͨ�Ž���ȷ��
        RXD(P5) --> TXD (PB10)                 "Q\n"    -->  "123\r\n"    ��ά��ʶ��
				�����ʣ�9600                           "R\n"    -->  "R(123,321)" Redɫ������
				                                       "G\n"    -->  "G(123,321)" Greenɫ������
																							 "B\n"    -->  "B(123,321)" Blueɫ������
																							 "O\n"    -->  "RGB"        ɫ��˳��
				
***************************************************************************************/
/***************************************************************************************
     �����               ����                OLED����
		Servo1 :  TIM1CH1 --> PA8                 SCL --> PD10
		Servo2 :  TIM1CH2 --> PA9                 SDA --> PD8
		Servo3 :  TIM1CH3 --> PA10                
		Servo4 :  TIM1CH4 --> PA11                
        Servo5 :  TIM9CH1 --> PA2                 
		
		����20ms     �Ƕ�  ռ�ձ�                 MOTOR
        0.5  ms -->  0      2.5%   249   300        MOTORA --> TIM8CH1 --> PC6
        1    ms -->  45       5%   499              MOTORB --> TIM8CH2 --> PC7
        1.5  ms -->  90     7.5%   749              MOTORC --> TIM8CH3 --> PC8
        2    ms -->  135    10%    999              MOTORD --> TIM8CH4 --> PC9
        2.5  ms -->  180    12.5%  1249  1200       arr = 1000-1    psc =  84-1  PWMƵ�� = 2KHz   ռ�ձ� = N/arr
***************************************************************************************/

/**********************************��������****************************************/
int Encoder_A,Encoder_B,Encoder_C,Encoder_D;          //���������������ֵ
int Motor_A,Motor_B,Motor_C,Motor_D;              //���PWM����
int count1 = 0;
int count2 = 0;
int count3 = 0;
/**********************************************************************************/

/**********************************��־λ����**************************************/
u8 flag_KEY1 = 0;   //KEY1 ��־λ
u8 flag_KEY2 = 0;   //KEY2 ��־λ
u8 flag_KEY3 = 0;   //KEY3 ��־λ


/**********************************************************************************/
void delayNs(int N);
 


int main(void)
{
	/*��ʼ��˳�����Ҫ*/
	delay_init(168);	    	                         //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	usart3_Init(9600);
	servo_Init(9999,335);                          //���PWMƵ��Ϊ50Hz  ռ�ձ� duty = N/arr;
	TIM7_Int_Init(50-1,8400-1);                     //TIM7 ��ʱ�ж�ʱ��Ϊ��5ms
	motor_Init(1000-1,84-1);                         //���PWMƵ��Ϊ2KHz  ռ�ձ� duty = N/arr;
	motor_Pin_Init();
	beep_Init();
	KEY_Init();
	IIC_Init();
	OLED_Init();
	OLED_Clear();
	Sensor_Count_Init();
	Sensor_count_Init2();
	Sensor_Track_Init();
	Sensor_TrackB_Init();
	encoder_MotorA_Init();
	encoder_MotorB_Init();
	encoder_MotorC_Init();
	encoder_MotorD_Init();
	
	while(1)
	{
		/***����һ������*******/
		 while(1)
		 {
			 	AIN1 = 1;  //��ת
				AIN2 = 0; 
				PWMA = 200;
				
				BIN1 = 0;  //��ת
				BIN2 = 1;
				PWMB = 200;
				
				CIN1 = 0;  //��ת
				CIN2 = 1;
				PWMC = 210;
				
				DIN1 = 1;  //��ת
				DIN2 = 0;
				PWMD = 210;
			 if(SENSOR_FRONT1 == 1 && SENSOR_FRONT1 == 1 )break;
		 }
		 while(1)
		 {
			 move_stop();
			 delayNs(3);
			 break;
		 }
		 
		  count1 = 0;
		 
		 /****�������ѭ��ֱ�ߵ�PAD***********/
		 while(1)
		 {
			 Trackline_Front(600-100*count1);
			 if(count1 >= 6)
			 {
				 move_stop();
				 break;
			 }
		 }
		 
		 count1 = 0;
		 
		 /***��������ͣ����ɨ���ά��*******/
		 while(1)
		 {
			 move_stop();
			 beep_ring();
			 delayNs(4);
			 break;
		 }
		 
		 while(1)
		 {
			 firstAction();
			 delayNs(5);
			 break;
		 }
		 
		 /***�����ģ�����ץȡ����**********/
		 while(1)
		 {
			 move_back_400(200);
			 if(count1 >= 3)
			 {
				 move_stop();
				 break;
			 }
		 }
		 count1 = 0;
		 
		 while(1)
		 {
			 action2();
			 delayNs(8);
			 break;
		 }
		 /***�����壺��������************/
		 while(1)
		 {
			 move_stop();
			 beep_ring();
			 count1 = 0;
			 delayNs(4);
			 break;
		 }
		 
		 count1 = 0;		 
		 while(1)
		 {

			 /*��ƽ��*/
			 	AIN1 = 1;  //��ת
				AIN2 = 0; 
				PWMA = 190;
				
				BIN1 = 0;  //��ת
				BIN2 = 1;
				PWMB = 200;
				
				CIN1 = 0;  //��ת
				CIN2 = 1;
				PWMC = 210;
				
				DIN1 = 1;  //��ת
				DIN2 = 0;
				PWMD = 240;
			 	 			 
			 if(count1 >= 3)
			 {
				 move_stop();
				 break;
			 }
			 
		 }		 
		 while(1)
		 {
			 move_stop();
			 //beep_ring();
			 delayNs(4);
		 }
		 
		 while(1)
		 {
			 move_stop();
			 //beep_ring();
			 delayNs(4);
		 }
     /**end8************************************************************************************************/

		
	}
}	  


void delayNs(int N)
{
	int i;
	for(i = 0;i< N;i++)
	{
		delay_ms(200);
	}
}