/*
*********************************************************************************************************
*	                                  
*	模块名称 : 简单ADC值读取功能
*	文件名称 : DSO_MultiMeter.c
*	版    本 : V1.0
*	说    明 : 实现简单的ADC值读取。
*	修改记录 :
*		版本号    日期          作者           说明
*		V1.0    2018-01-06     Eric2013        首发 
*                                           
*	Copyright (C), 2018-2028, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"



/*
*********************************************************************************************************
*					                      宏定义
*********************************************************************************************************
*/
#define ADC2SampleCount    40


/*
*********************************************************************************************************
*					                      变量
*********************************************************************************************************
*/
static uint16_t s_usADC2Buf[ADC2SampleCount];
uint16_t g_uiAdcAvgSample = 0;


/*
*********************************************************************************************************
*	函 数 名: ADC_GetSampleAvgN
*	功能说明: 连续读取40次ADC值求平均
*	形    参: 无      	
*	返 回 值: 返回读取的ADC值
*********************************************************************************************************
*/
uint16_t ADC_GetSampleAvgN(void)
{
	uint32_t avg_sample = 0;
	uint8_t index = 0;
	
	/* 读取40次ADC值 */
	for (index = 0; index < ADC2SampleCount; index++)
	{
		/* 开启转换 */
		ADC_SoftwareStartConv(ADC2);
		
		/* 等待转换完成 */
		while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC) == RESET);
		
		/* 读取数值 */
		s_usADC2Buf[index] = ADC_GetConversionValue(ADC2);
	}
	
	/* 将获取的40个ADC值求平均 */
	for (index = 0; index < ADC2SampleCount; index++)
	{
		avg_sample += s_usADC2Buf[index];
	}
	
	avg_sample /= ADC2SampleCount;
	
	return avg_sample;
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
