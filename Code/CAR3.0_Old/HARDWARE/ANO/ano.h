#ifndef __ANO_H
#define __ANO_H
#include "sys.h"
/**********Ϊ������������λ����Э�鶨��ı���****************************/
//cupΪС��ģʽ�洢��Ҳ�����ڴ洢��ʱ�򣬵�λ������0�ֽڣ���λ��1�ֽ�
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))	 //ȡ��int�ͱ����ĵ��ֽ�
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))//	ȡ�洢�ڴ˱�����һ�ڴ��ֽڵ����ݣ����ֽ�
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))


void Encoder_send_data(int target,int Encoder_data);
#endif