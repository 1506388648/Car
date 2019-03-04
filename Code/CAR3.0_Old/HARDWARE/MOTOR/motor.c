#include "motor.h"

/*
* �������ܣ����PWM���ٳ�ʼ�� 
* ����˵����MOTORA --> TIM8CH1 --> PC6
*           MOTORB --> TIM8CH2 --> PC7
*           MOTORC --> TIM8CH3 --> PC8
*           MOTORD --> TIM8CH4 --> PC9
*           
            MOTORA --> TIM8CH3 --> PC8
						MOTORB --> TIM8CH4 --> PC9
						MOTORC --> TIM8CH2 --> PC7
						MOTORD --> TIM8CH1 --> PC6
*           arr = 1000-1    psc =  84-1  PWMƵ�� = 2KHz   ռ�ձ� = N/arr
*/
void motor_Init(u16 arr,u16 psc)
{
	/* �ṹ���ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	/* ����ʹ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);//TIM8 ʱ��ʹ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ�� PORTC ʱ��
	/*IO ����*/
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6,  GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7,  GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8,  GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9,  GPIO_AF_TIM8);
	/* IO ��ʼ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ� 50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
	/* ��ʱ����ʼ�� */
	TIM_TimeBaseStructure.TIM_Prescaler=psc; //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr; //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//��ʼ����ʱ��TIM8
	
	TIM_OCStructInit(& TIM_OCInitStructure);                       //�ָ���ʼ
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;              //��ʱ��ģʽΪpwmģʽ1
  TIM_OCInitStructure.TIM_Pulse =0;                              //����ֵ����������ǵ͵�ƽ
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //����Ϊ��
	/*��ʼ����ʱ������ͨ��*/
	/*TIM8CH1*/
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);     
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	/*TIM8CH2*/
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	/*TIM8CH3*/
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	/*TIM8CH4*/
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	/*ʹ�ܶ�ʱ��*/
	TIM_Cmd(TIM8, ENABLE);
	/*ʹ�ܶ�ʱ��PWM���ģʽ*/
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

/*����������ų�ʼ��*/
void motor_Pin_Init()
{
	GPIO_InitTypeDef GPIO_DInitStructure; // GPIOD
	GPIO_InitTypeDef GPIO_BInitStructure; // GPIOB
	GPIO_InitTypeDef GPIO_CInitStructure; // GPIOC
	GPIO_InitTypeDef GPIO_EInitStructure; // GPIOE
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);//ʹ�� PORT ʱ��
	
	/* IO ��ʼ�� D0 D1 D2 D3*/
	GPIO_DInitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_DInitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_DInitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ� 50MHz
	GPIO_DInitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_DInitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����			
	GPIO_Init(GPIOD,&GPIO_DInitStructure); 
	/* IO ��ʼ�� B0 B2*/
	GPIO_BInitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2;
	GPIO_BInitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_BInitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ� 50MHz
	GPIO_BInitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_BInitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����			
	GPIO_Init(GPIOB,&GPIO_BInitStructure);
	/* IO ��ʼ�� C4*/
	GPIO_CInitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_CInitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_CInitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ� 50MHz
	GPIO_CInitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_CInitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����			
	GPIO_Init(GPIOC,&GPIO_CInitStructure);
	/* IO ��ʼ�� E8*/
	GPIO_EInitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_EInitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_EInitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ� 50MHz
	GPIO_EInitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_EInitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����			
	GPIO_Init(GPIOE,&GPIO_EInitStructure);
}
