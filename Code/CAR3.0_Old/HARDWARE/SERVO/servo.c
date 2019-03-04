#include "servo.h"
#include "delay.h"

/*
*  Servo1 :  TIM1CH1 --> PA8
*  Servo2 :  TIM1CH2 --> PA9
*  Servo3 :  TIM1CH3 --> PA10
*  Servo4 :  TIM1CH4 --> PA11
*  Servo5 :  TIM9CH1 --> PA2
*/

/********************************��������*************************************/
static int servo1_last_angle = 0;
static int servo2_last_angle = 0;
static int servo3_last_angle = 0;
static int servo4_last_angle = 0;
static int servo5_last_angle = 0;
/*****************************************************************************/

/*
* �������ܣ����PWM��ʼ��
* ����˵����arr = 2000-1    psc = 840-1        PWMƵ��Ϊ50Hz
*/
void servo_Init(u16 arr,u16 psc)
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

/*
* �������ܣ�1�Ŷ���Ƕ����
* ����˵�����Ƕȷ�Χ�� 100�����Ƕ� --- 160 ��ȫ�պ� 
*/
void Servo1_SetAngle(int angle)
{
	int pwm_value;
	//if(angle<100||angle>160)angle=100;
	pwm_value = 5*angle+300;
	TIM_SetCompare1(TIM1,pwm_value);
}

/*
* �������ܣ�2�Ŷ���Ƕ����
* ����˵�����Ƕȷ�Χ��0 -- 180
*/
void Servo2_SetAngle(int angle)
{
	int pwm_value;
	//if(angle<0||angle>180)angle=20;
	pwm_value = 5*angle+300;
	TIM_SetCompare2(TIM1,pwm_value);
}

/*
* �������ܣ�3�Ŷ���Ƕ����
* ����˵�����Ƕȷ�Χ��70 -- 180
*/
void Servo3_SetAngle(int angle)
{
	int pwm_value;
	//if(angle<70||angle>180)angle=80;
	pwm_value = 5*angle+300;
	TIM_SetCompare3(TIM1,pwm_value);
}

/*
* �������ܣ�4�Ŷ���Ƕ����
* ����˵�����Ƕȷ�Χ��0 -- 150
*/
void Servo4_SetAngle(int angle)
{
	int pwm_value;
	//if(angle<0||angle>150)angle=0;
	pwm_value = 5*angle+300;
	TIM_SetCompare4(TIM1,pwm_value);
}

/*
* �������ܣ�5�Ŷ���Ƕ����
* ����˵�����Ƕȷ�Χ��0 -- 180
*/
void Servo5_SetAngle(int angle)
{
	int pwm_value;
	//if(angle<40||angle>120)angle=80;
	pwm_value = 5*angle+300;
	TIM_SetCompare1(TIM9,pwm_value);
}



/*
* �������ܣ�һ�Ŷ�� �Ƕ���� ��ֵϸ��
* ����˵������Ч���Ͷ��ת�٣������ȶ���
*/
void Servo1_SpeedRegulation(int next_angle)
{
	int N;
	int i;
	N  = abs(next_angle - servo1_last_angle);
	if (servo1_last_angle < next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo1_last_angle += 1;
			Servo1_SetAngle(servo1_last_angle);
			delay_ms(20);
		}
	}
	if(servo1_last_angle > next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo1_last_angle -= 1;
			Servo1_SetAngle(servo1_last_angle);
			delay_ms(20);
		}
	}
}


/*
* �������ܣ����Ŷ�� �Ƕ���� ��ֵϸ��
* ����˵������Ч���Ͷ��ת�٣������ȶ���
*/
void Servo2_SpeedRegulation(int next_angle)
{
	int N;
	int i;
	N  = abs(next_angle - servo2_last_angle);
	if (servo2_last_angle < next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo2_last_angle += 1;
			Servo2_SetAngle(servo2_last_angle);
			delay_ms(20);
		}
	}
	if(servo2_last_angle > next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo2_last_angle -= 1;
			Servo2_SetAngle(servo2_last_angle);
			delay_ms(20);
		}
	}
}


/*
* �������ܣ����Ŷ�� �Ƕ���� ��ֵϸ��
* ����˵������Ч���Ͷ��ת�٣������ȶ���
*/
void Servo3_SpeedRegulation(int next_angle)
{
	int N;
	int i;
	N  = abs(next_angle - servo3_last_angle);
	if (servo3_last_angle < next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo3_last_angle += 1;
			Servo3_SetAngle(servo3_last_angle);
			delay_ms(20);
		}
	}
	if(servo3_last_angle > next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo3_last_angle -= 1;
			Servo3_SetAngle(servo3_last_angle);
			delay_ms(20);
		}
	}
}


/*
* �������ܣ��ĺŶ�� �Ƕ���� ��ֵϸ��
* ����˵������Ч���Ͷ��ת�٣������ȶ���
*/
void Servo4_SpeedRegulation(int next_angle)
{
	int N;
	int i;
	N  = abs(next_angle - servo4_last_angle);
	if (servo4_last_angle < next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo4_last_angle += 1;
			Servo4_SetAngle(servo4_last_angle);
			delay_ms(20);
		}
	}
	if(servo4_last_angle > next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo4_last_angle -= 1;
			Servo4_SetAngle(servo4_last_angle);
			delay_ms(20);
		}
	}
}


/*
* �������ܣ���Ŷ�� �Ƕ���� ��ֵϸ��
* ����˵������Ч���Ͷ��ת�٣������ȶ���
*/
void Servo5_SpeedRegulation(int next_angle)
{
	int N;
	int i;
	N  = abs(next_angle - servo5_last_angle);
	if (servo5_last_angle < next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo5_last_angle += 1;
			Servo5_SetAngle(servo5_last_angle);
			delay_ms(20);
		}
	}
	if(servo5_last_angle > next_angle)
	{
		for(i = 0; i < N; i++)
		{
			servo5_last_angle -= 1;
			Servo5_SetAngle(servo5_last_angle);
			delay_ms(20);
		}
	}
}
