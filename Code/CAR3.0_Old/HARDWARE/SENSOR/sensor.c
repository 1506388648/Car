#include "sensor.h"
#include "delay.h"
#include "oled.h"
#include "key.h"

extern int count1;
extern int count2;
extern int count3;

extern u8 flag_KEY1;
extern u8 flag_KEY2;
extern u8 flag_KEY3;

/* ѭ������������������ ���� �͵�ƽ
							 �����հ� ���� �ߵ�ƽ
*/


/*����ѭ����������ʼ��*/
void Sensor_Track_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);//ʹ�� GPIOD,GPIOE ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ�� GPIOE1,2,3,4
	 
}

void Sensor_TrackB_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʹ�� GPIOD,GPIOE ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��  
}

/* ���⴫�����ⲿ�жϼ�����ʼ�� */
void Sensor_Count_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//ʹ�� GPIOD,GPIOE ʱ��
	
	/* IO��ʼ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ�� SYSCFG ʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);//PE11 ������ 11
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource13);//PE11 ������ 13
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource15);//PE11 ������ 15
	
	/* ���� EXTI_Line11 13 15 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11|EXTI_Line13|EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ�� LINE11
	EXTI_Init(&EXTI_InitStructure);
	
	/* �жϳ�ʼ�� LINE10 - 15 */
	NVIC_InitStructure.NVIC_IRQChannel =  EXTI15_10_IRQn;//�ⲿ�ж� 11
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ� 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//��Ӧ���ȼ� 2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//���� NVIC
	
}


void Sensor_count_Init2()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʹ�� GPIOD,GPIOE ʱ��
	
	/* IO��ʼ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ�� SYSCFG ʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource15);//PB15 ������ 15
	
	/* ���� EXTI_Line15 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ�� LINE11
	EXTI_Init(&EXTI_InitStructure);
	
	/* �жϳ�ʼ�� LINE10 - 15 */
	NVIC_InitStructure.NVIC_IRQChannel =  EXTI15_10_IRQn;//�ⲿ�ж� 11
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ� 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//��Ӧ���ȼ� 2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//���� NVIC
}

/* �ⲿ�жϴ����� */
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);      //�ʵ���ʱ��ֹë�̸���
	/* LINE11�ж��ж� */
	if(EXTI_GetITStatus(EXTI_Line11)!=RESET)
	{ 
		/* �ж��߼� */
		if (SENSOR1 == 0)count1++;
		EXTI_ClearITPendingBit(EXTI_Line11); //��� LINE �ϵ��жϱ�־λ
	}
	
		/* LINE13�ж��ж� */
	if(EXTI_GetITStatus(EXTI_Line13)!=RESET)
	{ 
		/* �ж��߼� */
		if (SENSOR2 == 0)count2++;
		EXTI_ClearITPendingBit(EXTI_Line13); //��� LINE �ϵ��жϱ�־λ
	}
	
		/* LINE15�ж��ж� */
	if(EXTI_GetITStatus(EXTI_Line15)!=RESET)
	{ 
		/* �ж��߼� */
		if (SENSOR5 == 0)count3++;
		EXTI_ClearITPendingBit(EXTI_Line15); //��� LINE �ϵ��жϱ�־λ
	}
}
