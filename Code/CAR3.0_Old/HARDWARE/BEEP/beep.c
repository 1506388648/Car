#include "beep.h"

/*��������ʼ�� */
void beep_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ�� GPIOB ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //BEEP �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
  GPIO_ResetBits(GPIOE,GPIO_Pin_1);//���0���رշ��������
}

/*
* �������ܣ����������� 1
* ����˵������ ��ʱ100ms ��
**/
void beep_ring()
{
	BEEP=0;
	delay_ms(100);
	BEEP=1;
	delay_ms(100);
	BEEP=0;
	delay_ms(100);
	BEEP=1;
	delay_ms(100);
	BEEP=0;
}