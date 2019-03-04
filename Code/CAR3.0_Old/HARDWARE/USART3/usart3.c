#include "usart3.h"

/**************************��������******************************/
u8 USART3_RX_buf[USART3_MAX_RECV_LEN];
u8 USART3_TX_buf[USART3_MAX_SEND_LEN];
u16 USART3_RX_STA=0;//����״̬���
/****************************************************************/

/*
* �������ܣ�����3��ʼ��
* ����˵����TXD��PB10   RXD��PB11
*/

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
	USART3->DR = (u8) ch;      
	return ch;
}
#endif


void usart3_Init(u32 bound)
{
	/*�ṹ���ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/*����ʹ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);      //ʹ��GPIOBʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);     //ʹ��USART3ʱ�� 
	/*���Ÿ���*/
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);  //GPIOB10����ΪUSART3
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);  //GPIOB11����ΪUSART3
	/*USART3 �˿ڳ�ʼ��*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;              //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;            //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;              //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);                     //��ʼ��
	/*�����жϳ�ʼ��*/
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);            //���������ж�
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         //����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;   //��ռ���ȼ�3 ��ֵԽС���ȼ�Խ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;         //�����ȼ�3,��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                           //����ָ���Ĳ�����ʼ��VIC�Ĵ���
  /* USART3��ʼ�� */
	USART_InitStructure.USART_BaudRate = bound;               //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;     //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;        //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure);                  //��ʼ������3
	USART_Cmd(USART3, ENABLE);                                 //ʹ�ܴ���3 
}


/*
* �������ܣ��ַ���תU32����
* ��ڲ����� �ַ���
* ����ֵ  ;  u32����
*/
unsigned long strtou32(char *str)
{
	unsigned long temp=0;
	unsigned long fact=1;
	unsigned char len=strlen(str);
	unsigned char i;
	for(i=len;i>0;i--)
	{
		temp+=((str[i-1]-0x30)*fact);
		fact*=10;
	}
	return temp;
}

/*
* �������ܣ� ��һ��32λ�ı���datתΪ�ַ����������1234תΪ"1234"
* ��ڲ����� dat:��ת����long�͵ı���   str:ָ���ַ������ָ�룬ת������ֽڴ��������� 
* ����ֵ  ;  ��
*/
void u32tostr(unsigned long dat,char *str)
{
	char temp[20];
	unsigned char i=0,j=0;
	i=0;
	while(dat)
	{
		temp[i]=dat%10+0x30;
		i++;
		dat/=10;
	}
	j=i;
	for(i=0;i<j;i++)
	{
		str[i]=temp[j-i-1];
	}
	if(!i) {str[i++]='0';}
	str[i]=0;
}


/*
* �������ܣ�����3�жϺ���
* ����˵����
*
*/
void USART3_IRQHandler(void)
{
	u8 Res;
	/*�����ж� ������0x0d 0x0a��β*/
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART3);//(USART3->DR) ��ȡ���յ�������
		
		if((USART3_RX_STA&0x8000)==0)//����δ���
		{
			if(USART3_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART3_RX_STA=0;//���մ���,���¿�ʼ
        else USART3_RX_STA|=0x8000; //��������� 
			}
			else
			{
				if(Res==0x0d)USART3_RX_STA|=0x4000;
        else
				{
					USART3_RX_buf[USART3_RX_STA&0X3FFF]=Res ;
					USART3_RX_STA++;
					if(USART3_RX_STA>(USART3_MAX_RECV_LEN-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����  
        }  
			}
		}
	}
}