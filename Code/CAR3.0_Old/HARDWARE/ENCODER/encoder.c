#include "encoder.h"
#include "motor.h"

/*
* �������ܣ����A �������ӿڳ�ʼ��
* ����˵����A�� --> PA15  
*           B�� --> PB3
**/
/*TIM2 ������ģʽ*/
void encoder_MotorA_Init()
{
	/* �ṹ���ʼ�� */
	GPIO_InitTypeDef GPIOA_InitStructure;
	GPIO_InitTypeDef GPIOB_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
	/*����ʹ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ��TIM2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��PORTA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʹ��PORTB
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3,  GPIO_AF_TIM2);   
	/* PA15��ʼ�� */
	GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIOA_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIOA_InitStructure);
	/* PB3��ʼ�� */
	GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIOB_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIOB_InitStructure);
	/* TIM2 ��λ */
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* ����TIM2 Ϊ�������ӿ�ģʽ */
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
  TIM_ICStructInit(&TIM_ICInitStructure);    // ��ʼ��ΪĬ��ֵ
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
	/* ���� TIM2->CNT */
	TIM2->CNT = 0;
	/* ʹ��TIM2 */
  TIM_Cmd(TIM2, ENABLE);  
}

/*
* �������ܣ����D �������ӿڳ�ʼ��
* ����˵����A�� --> PA6
*           B�� --> PA7
**/
void encoder_MotorB_Init()
{
	/* �ṹ���ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
	/*����ʹ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ�� PORTA ʱ��
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);   
	/*IOʹ��*/
	//GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*TIM3 ��λ*/
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* ����TIM3 Ϊ�������ӿ�ģʽ */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
  TIM_ICStructInit(&TIM_ICInitStructure);    // ��ʼ��ΪĬ��ֵ
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
	/* ���� TIM2->CNT */
	TIM3->CNT = 0;
	/* ʹ��TIM2 */
  TIM_Cmd(TIM3, ENABLE);  
}

/*
* �������ܣ����B �������ӿڳ�ʼ��
* ����˵����A�� --> PB6
*           B�� --> PB7
**/
void encoder_MotorC_Init()
{
	/* �ṹ���ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
	/*����ʹ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʹ�� PORTB ʱ��
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);   
	/*IOʹ��*/
	//GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	/*TIM4 ��λ*/
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/* ����TIM4 Ϊ�������ӿ�ģʽ */
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
  TIM_ICStructInit(&TIM_ICInitStructure);    // ��ʼ��ΪĬ��ֵ
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
	/* ���� TIM4->CNT */
	TIM4->CNT = 0;
	/* ʹ��TIM2 */
  TIM_Cmd(TIM4, ENABLE);  
}


/*
* �������ܣ����C �������ӿڳ�ʼ��
* ����˵����A�� --> PA0
*           B�� --> PA1
**/
void encoder_MotorD_Init()
{
	/* �ṹ���ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
	/*����ʹ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ�� PORTA ʱ��
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM4);   
	/*IOʹ��*/
	//GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*TIM4 ��λ*/
	TIM_DeInit(TIM5);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	/* ����TIM4 Ϊ�������ӿ�ģʽ */
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
  TIM_ICStructInit(&TIM_ICInitStructure);    // ��ʼ��ΪĬ��ֵ
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	/* ���� TIM4->CNT */
	TIM5->CNT = 0;
	/* ʹ��TIM2 */
  TIM_Cmd(TIM5, ENABLE);  
}



/*
* ˵��
* AIN1  AIN2  1  0 -- ��  0  1 -- ��
* BIN1  BIN2  1  0 -- ��  0  1 -- ��
*
* CIN1  CIN2  1  0 -- ��  0  1 -- ��
* DIN1  DIN2  1  0 -- ��  0  1 -- ��
*
***/
/*
* �������ܣ���λʱ���ȡ����������
* ����˵����
**/
s16 Read_Encoder(u8 TIMX)
{
   s16 Encoder_TIM;    
   switch(TIMX)
	 {
	   case 1:  Encoder_TIM = TIM2->CNT;TIM2->CNT=0; break;
		 case 2:  Encoder_TIM = TIM4->CNT;TIM4->CNT=0; break;
		 case 3:  Encoder_TIM = TIM5->CNT;TIM5->CNT=0; break;	
		 case 4:  Encoder_TIM = TIM3->CNT;TIM3->CNT=0; break;	
		 default: Encoder_TIM = 0;
	 }
		return Encoder_TIM;
}


s16 Read_Encoder1(u8 MotorNum)
{
	s16 Encoder_value;
	switch(MotorNum)
	{
		case 1:
			if(AIN1 == 1 && AIN2 == 0)  // MOTOR A ��ת
			{
				Encoder_value = TIM2->CNT;
				TIM2->CNT=0;
				break;
			}
			else if(AIN1 == 0 && AIN2 == 1) // MOTOR A ��ת
			{
				Encoder_value = 65535 - TIM2->CNT;
				TIM2->CNT=0;
				break;
			}
		case 2:
			if(BIN1 == 1 && BIN2 == 0)  // MOTOR B ��ת
			{
				Encoder_value =-TIM4->CNT;
				TIM4->CNT=0;
				break;
			}
			else if(BIN1 == 0 && BIN2 == 1) // MOTOR B ��ת
			{
				Encoder_value =TIM4->CNT;
				TIM4->CNT=0;
				break;
			}
		case 3:
			if(CIN1 == 0 && CIN2 == 1)  // MOTOR C ��ת
			{
				Encoder_value = TIM5->CNT;
				TIM5->CNT=0;
				break;
			}
			else if(CIN1 == 1 && CIN2 == 0) // MOTOR C ��ת
			{
				Encoder_value = 65535 - TIM5->CNT;
				TIM5->CNT=0;
				break;
			}
		case 4:
			if(DIN1 == 0 && DIN2 == 1)  // MOTOR D ��ת
			{
				Encoder_value = TIM3->CNT;
				TIM3->CNT=0;
				break;
			}
			else if(DIN1 == 1 && DIN2 == 0) // MOTOR D ��ת
			{
				Encoder_value = 65535 - TIM3->CNT;
				TIM3->CNT=0;
				break;
			}
		default: Encoder_value = 0;
	}
	return Encoder_value;
}
