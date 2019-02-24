#include "pwm.h"



/*
*    TIM1CH1 --> PA8
*    TIM1CH2 --> PA9
*    TIM1CH3 --> PA10
*    TIM1CH4 --> PA11
*    TIM9CH1 --> PA2
*/
/*
* �������ܣ����PWM��ʼ��
* ����˵����arr = 2000-1    psc = 840-1        PWMƵ��Ϊ50Hz
*           CLK/psc = ����Ƶ��  PWMƵ�� = ����Ƶ�� / arr
*/
void PWM_Init(u16 arr,u16 psc)
{
	/* �ṹ���ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	/* ����ʹ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//TIM1 ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);//TIM9 ʱ��ʹ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ�� PORTA ʱ��
	/*IO ����*/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,  GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_TIM1);   
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);   	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2,  GPIO_AF_TIM9);  
	/* IO ��ʼ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; //PA2 --> PA11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ� 50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2 --> PA11
	/* ��ʱ����ʼ�� */
	TIM_TimeBaseStructure.TIM_Prescaler=psc; //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr; //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��TIM1
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��TIM9
	
	TIM_OCStructInit(& TIM_OCInitStructure);                       //�ָ���ʼ
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;              //��ʱ��ģʽΪpwmģʽ1
  TIM_OCInitStructure.TIM_Pulse =0;                              //����ֵ����������ǵ͵�ƽ
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //����Ϊ��
	/*��ʼ����ʱ������ͨ��*/
	/*TIM1CH1*/
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);     
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	/*TIM1CH2*/
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	/*TIM1CH3*/
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	/*TIM1CH4*/
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	/*TIM9CH1*/
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);     
  TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
	
	/*ʹ�ܶ�ʱ��*/
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	/*ʹ�ܶ�ʱ��PWM���ģʽ*/
	TIM_Cmd(TIM9, ENABLE);
  TIM_CtrlPWMOutputs(TIM9, ENABLE);
}

/*PWM���PA8��ռ�ձ� = pwm_value / arr */
void PWM_TIM1CH1_Output(int pwm_value)
{
	TIM_SetCompare1(TIM1,pwm_value);
}