#include "ano.h"
#include "usart3.h"
#include "math.h"
/******************************************
** ˵����
	1�� ���͸���λ��������֡����
		@��ͷ--������--����--���ݣ�һ�����������忴Э��˵����-У��
		@ǰ2���ֽ�Ϊ֡ͷ0xAAAA
		@��3���ֽ�Ϊ֡ID��Ҳ���ǹ����֣�Ӧ����Ϊ0xF1~0xFA�е�һ��
		@��4���ֽ�Ϊ�������ݳ���(dlc)
		@��5���ֽڿ�ʼ����5+dlc-1���ֽ�ΪҪ������������ݶΣ�ÿ�����ݳ�Ϊ���ֽ���ǰ�����ֽ��ں�
		@��5+dlc���ֽ�ΪCheckSum,Ϊ��1���ֽڵ���5+dlc-1���ֽ������ֽڵ�ֵ��Ӻ󣬱�������ĵͰ�λ��ΪCheckSum
	2�� �ⲿֱ�ӵ������������
	3�� ��Ҫ�ڴ��ļ���������Ҫ���͵������ļ��е����ݡ�
	4�� ���͵����ݱ����� int_16 �͵�����
*****************************************/

void usart3_send_char(u8 c)
{
    while((USART3->SR & 0X40) == 0); //�ȴ���һ�η������
    USART3->DR = c;
}


void send_Test()
{
    float count;
    for(count = 0.0; count < 360; count += 0.1)Encoder_send_data(10, 10 * sin(count));
}


void Encoder_send_data(int target, int Encoder_data)
{
    u8 send_buf[50]; //�������ݻ���
    u8 _cnt = 0;
    u8 i;
    u8 sum = 0;	//����Ϊ����sumУ���ֽڣ���0xAAҲ�������ֽڣ�һֱ��sum�ֽ�ǰһ�ֽ�

    send_buf[_cnt++] = 0xAA; //0xAAΪ֡ͷ
    send_buf[_cnt++] = 0x05; //0x05Ϊ���ݷ���Դ��������ο�����Э�飬���ֽ��û������������
    send_buf[_cnt++] = 0xAF; //0xAFΪ����Ŀ�ĵأ�AF��ʾ��λ����������ο�����Э��
    send_buf[_cnt++] = 0xF1; //0xF1����ʾ��֡ΪF1�û��Զ���֡����Ӧ�߼������F1����֡
    send_buf[_cnt++] = 0; //���ֽڱ�ʾ���ݳ��ȣ�������=0����������ٸ�ֵ�������Ͳ����˹����㳤����

    send_buf[_cnt++] = BYTE3(target); //��Ҫ���͵����ݷ������ͻ�����
    send_buf[_cnt++] = BYTE2(target);
    send_buf[_cnt++] = BYTE1(target);
    send_buf[_cnt++] = BYTE0(target);

    send_buf[_cnt++] = BYTE3(Encoder_data); //��Ҫ���͵����ݷ������ͻ�����
    send_buf[_cnt++] = BYTE2(Encoder_data);
    send_buf[_cnt++] = BYTE1(Encoder_data);
    send_buf[_cnt++] = BYTE0(Encoder_data);
    
    send_buf[4] = _cnt - 5; //_cnt�����������ݳ��ȣ���5Ϊ��ȥ֡��ͷ5���������ֽ�

    for(i = 0; i < _cnt; i++)
        sum += send_buf[i];

    send_buf[_cnt++] = sum;	//��sumУ�����ݷ������һ�ֽ�

    for(i = 0; i < _cnt; i++)usart3_send_char(send_buf[i]);
}