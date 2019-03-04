#include "timer.h"
#include "usart.h"
#include "led.h"
#include "motor.h"

extern int Encoder_A;
extern int Encoder_B;
extern int Encoder_C;
extern int Encoder_D;

extern int Motor_A;
extern int Motor_B;
extern int Motor_C;
extern int Motor_D;
extern int count1;
extern int testNum;
/*TIM7 ��ʼ��*/
void TIM7_Int_Init(u16 arr,u16 psc)
{
	/*�ṹ���ʼ��*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/*ʹ�� TIM7 ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
  TIM_TimeBaseInitStructure.TIM_Period = arr; //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	/*��ʼ����ʱ��TIM7*/
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);
	/*����ʱ�� 7 �����ж�*/
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //��ʱ�� 7 �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ� 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //��Ӧ���ȼ� 3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//��ʼ�� NVIC
 
	TIM_Cmd(TIM7,ENABLE); //ʹ�ܶ�ʱ�� 7
}




void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //����ж�
	{
		Encoder_A = Read_Encoder(1);
		Encoder_B = Read_Encoder(2);
		Encoder_C = Read_Encoder(3);
		Encoder_D = Read_Encoder(4);
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update); //����жϱ�־λ
}