#include "message.h"
#include "oled.h"
#include "string.h"
#include "usart3.h"

extern int Encoder_A;
extern int Encoder_B;
extern int Encoder_C;
extern int Encoder_D;

unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���



/* OLED��ʾ��ά��ʶ���� */
void OLED_show_Qcode()
{
	u8 flag_Qc = 1; //��ά����Ϣ�ȽϽ�� ��־λ
	//OLED_Clear();
	
	OLED_ShowCHinese(0,0,0);   //ʶ������
	OLED_ShowCHinese(16,0,4);
	OLED_ShowCHinese(32,0,5);
	OLED_ShowCHinese(48,0,6);
	OLED_ShowString(64,0,":");	
	if(USART3_RX_STA&0x8000)
	{
		flag_Qc = strcmp(USART3_RX_buf,"123");//������
		if(flag_Qc == 0){
			OLED_ShowCHinese(80, 0,1);
		  OLED_ShowCHinese(96, 0,2);
		  OLED_ShowCHinese(112,0,3);
		}
		
		flag_Qc = strcmp(USART3_RX_buf,"132");//������
		if(flag_Qc == 0){
			OLED_ShowCHinese(80, 0,1);
		  OLED_ShowCHinese(96, 0,3);
		  OLED_ShowCHinese(112,0,2);
		}
		
		flag_Qc = strcmp(USART3_RX_buf,"213");//�̺���
		if(flag_Qc == 0){
			OLED_ShowCHinese(80, 0,2);
		  OLED_ShowCHinese(96, 0,1);
		  OLED_ShowCHinese(112,0,3);
		}
		
		flag_Qc = strcmp(USART3_RX_buf,"231");//������
		if(flag_Qc == 0){
			OLED_ShowCHinese(80, 0,2);
		  OLED_ShowCHinese(96, 0,3);
		  OLED_ShowCHinese(112,0,1);
		}
		
		flag_Qc = strcmp(USART3_RX_buf,"312");//������
		if(flag_Qc == 0){
			OLED_ShowCHinese(80, 0,3);
		  OLED_ShowCHinese(96, 0,1);
		  OLED_ShowCHinese(112,0,2);
		}
		
		flag_Qc = strcmp(USART3_RX_buf,"321");//���̺�
		if(flag_Qc == 0){
			OLED_ShowCHinese(80, 0,3);
		  OLED_ShowCHinese(96, 0,2);
		  OLED_ShowCHinese(112,0,1);
		}
		
		USART3_RX_STA = 0; //���ý���λ
		beep_ring();       //ͨ�ųɹ�һ�� ��������һ��
	}
}

/* OLED ��ʾ ����ʶ��˳�� */
void OLED_show_colorSort()
{
	u8 flag_sort = 1; //��ά����Ϣ�ȽϽ�� ��־λ
	
	//OLED_Clear();
	OLED_ShowCHinese(0,3,7);   //����˳��
	OLED_ShowCHinese(16,3,8);
	OLED_ShowCHinese(32,3,9);
	OLED_ShowCHinese(48,3,10);
	OLED_ShowString(64,3,":");
	
	if(USART3_RX_STA&0x8000)
	{
		flag_sort = strcmp(USART3_RX_buf,"RGB");// RGB
		if(flag_sort == 0){
			OLED_ShowCHinese(80, 3,1);
		  OLED_ShowCHinese(96, 3,2);
		  OLED_ShowCHinese(112,3,3);
		}
		
		flag_sort = strcmp(USART3_RX_buf,"RBG");// RBG
		if(flag_sort == 0){
			OLED_ShowCHinese(80, 3,1);
		  OLED_ShowCHinese(96, 3,3);
		  OLED_ShowCHinese(112,3,2);
		}
		
		flag_sort = strcmp(USART3_RX_buf,"GRB");// GRB
		if(flag_sort == 0){
			OLED_ShowCHinese(80, 3,2);
		  OLED_ShowCHinese(96, 3,1);
		  OLED_ShowCHinese(112,3,3);
		}
		
		flag_sort = strcmp(USART3_RX_buf,"GBR");// GBR
		if(flag_sort == 0){
			OLED_ShowCHinese(80, 3,2);
		  OLED_ShowCHinese(96, 3,3);
		  OLED_ShowCHinese(112,3,1);
		}
		
		flag_sort = strcmp(USART3_RX_buf,"BRG");// BRG
		if(flag_sort == 0){
			OLED_ShowCHinese(80, 3,3);
		  OLED_ShowCHinese(96, 3,1);
		  OLED_ShowCHinese(112,3,2);
		}
		
		flag_sort = strcmp(USART3_RX_buf,"BGR");// BGR
		if(flag_sort == 0){
			OLED_ShowCHinese(80, 3,2);
		  OLED_ShowCHinese(96, 3,3);
		  OLED_ShowCHinese(112,3,1);
		}
		
		USART3_RX_STA = 0; //���ý���λ
		beep_ring();       //ͨ�ųɹ�һ�� ��������һ��
	}
	
}

/* OLED ��ʾ������ת�� */
void OLED_show_Encoders()
{
		OLED_ShowString(0,0,"A:");
		OLED_ShowString(0,2,"B:");
		OLED_ShowString(0,4,"C:");
		OLED_ShowString(0,6,"D:");
	  /* ��ʾĿ��ת�� */
		OLED_ShowNum(40,0,Encoder_A);
		OLED_ShowNum(40,2,Encoder_B);                                                                         
		OLED_ShowNum(40,4,Encoder_C);
		OLED_ShowNum(40,6,Encoder_D);
}

