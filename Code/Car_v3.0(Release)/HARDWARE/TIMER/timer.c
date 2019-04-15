/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, Mrtutu.
**                           All Rights Reserved
**
**                                By Mrtutu
**                           Blog: www.mrtutu.cn
**
**----------------------------------文件信息------------------------------------
** @flie    : timer.c
** @auther  : Mrtutu
** @date    : 2019-02-17
** @describe:
**
**----------------------------------版本信息------------------------------------
** 版本代号: V0.1
** 版本说明: 初始版本
**
**------------------------------------------------------------------------------
\********************************End of Head************************************/


#include "timer.h"
#include "usart.h"
#include "led.h"
#include "motor.h"
#include "encoder.h"
#include "control.h"
#include "sensor.h"

extern volatile int Motor_A,Motor_B,Motor_C,Motor_D;         // PI算法返回赋值 临时PWM值
extern volatile int Encoder_A,Encoder_B,Encoder_C,Encoder_D; // 编码器返回赋值 
extern volatile int Target_A,Target_B,Target_C,Target_D;
extern u16 TIME;
extern u16 counter;

/*
* @auther: Main
* @date  ：2019-02-17
*
* @func  : TIM7定时中断 初始化 PID控制 10ms
* @param : arr: [重装载值] 
**		   psc: [预分频值] 
* @return: None
* @note  : None
*
*/
void TIM7_Int_Init(u16 arr, u16 psc)
{
    /*结构体初始化*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /*使能 TIM7 时钟*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    TIM_TimeBaseInitStructure.TIM_Period = arr; //自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //定时器分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    /*初始化定时器TIM7*/
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);
    /*允许定时器 7 更新中断*/
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; //定时器 7 中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; //抢占优先级 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //响应优先级 1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); // 初始化 NVIC

    TIM_Cmd(TIM7, ENABLE); //使能定时器 7
}





void TIM11_Int_Init(u16 arr, u16 psc)
{
    /*结构体初始化*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /*使能 TIM11 时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
    TIM_TimeBaseInitStructure.TIM_Period = arr; //自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //定时器分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    /*初始化定时器TIM11*/
    TIM_TimeBaseInit(TIM11, &TIM_TimeBaseInitStructure);
    /*允许定时器 11 更新中断*/
    TIM_ITConfig(TIM11, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn; //定时器 13 中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //抢占优先级 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01; //响应优先级 1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); // 初始化 NVIC

    TIM_Cmd(TIM11, DISABLE); //使能定时器 7
}



void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM11,TIM_IT_Update)==SET) //溢出中断
    {
        counter += 1; // 100ms 累加一次
    }
    TIM_ClearITPendingBit(TIM11,TIM_IT_Update); //清除中断标志位
}




/*
* @auther: Mrtutu
* @date  ：2019-04-07
*
* @func  : TIM13_Int_Init   定时器13 定时中断
* @param : arr: [输入/出] 
**			 psc: [输入/出] 
* @return: None
* @note  : None  溢出时间 1s  --  arr 16800 -1   psc 5000 -1
*
*/
void TIM13_Int_Init(u16 arr, u16 psc)
{
    /*结构体初始化*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /*使能 TIM13 时钟*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
    TIM_TimeBaseInitStructure.TIM_Period = arr; //自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //定时器分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    /*初始化定时器TIM13*/
    TIM_TimeBaseInit(TIM13, &TIM_TimeBaseInitStructure);
    /*允许定时器 7 更新中断*/
    TIM_ITConfig(TIM13, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn; //定时器 13 中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //抢占优先级 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //响应优先级 1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); // 初始化 NVIC

    TIM_Cmd(TIM13, DISABLE); 
}



void TIM8_UP_TIM13_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM13,TIM_IT_Update)==SET) //溢出中断
    {
        TIME += 1; // 1s累加一次
    }
    TIM_ClearITPendingBit(TIM13,TIM_IT_Update); //清除中断标志位
}





/*
* @auther: Main
* @date  ：2019-02-17
*
* @func  : TIM7_IRQHandler  PID 中断控制逻辑
* @param : None
* @return: None
* @note  : None
*
*/
void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //溢出中断
	{
        /*********************PID***************************/
        Encoder_A = Read_Encoder(1);
        Encoder_B = Read_Encoder(2);
        Encoder_C = Read_Encoder(3);
        Encoder_D = Read_Encoder(4);
        
        Motor_A   = Incremental_PI_MotorA(Encoder_A, Target_A);
        Motor_B   = Incremental_PI_MotorB(Encoder_B, Target_B);
        Motor_C   = Incremental_PI_MotorC(Encoder_C, Target_C);
        Motor_D   = Incremental_PI_MotorD(Encoder_D, Target_D);
        
        
        Set_PWM(Motor_A, Motor_B, Motor_C, Motor_D);
        /****************************************************/       
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update); //清除中断标志位
}
/********************************End of File************************************/
