/*
*********************************************************************************************************
*
*	模块名称 : 头文件汇总
*	文件名称 : includes.h
*	版    本 : V1.0
*	说    明 : 当前使用头文件汇总
*
*	修改记录 :
*		版本号    日期        作者     说明
*		V1.0    2015-08-02  Eric2013   首次发布
*
*	Copyright (C), 2015-2020, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

/*
*********************************************************************************************************
*                                         标准库
*********************************************************************************************************
*/
#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>


/*
*********************************************************************************************************
*                                         其它库
*********************************************************************************************************
*/
#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>
#include  <app_cfg.h>


/*
*********************************************************************************************************
*                                           OS
*********************************************************************************************************
*/
#include  <os.h>


/*
*********************************************************************************************************
*                                           宏定义
*********************************************************************************************************
*/
#define DspTaskInfo_13	        (1 << 13)  
#define DspMultiMeterPro_14	    (1 << 14)
#define DspFFT2048Pro_15	    (1 << 15)  


/*
*********************************************************************************************************
*                                        APP / BSP
*********************************************************************************************************
*/
#include "ff.h"
#include "rt_Memory.h"
#include  <bsp.h>


/*
*********************************************************************************************************
*                                          变量和函数
*********************************************************************************************************
*/
extern uint64_t AppMallocCCM[64*1024/8] __attribute__((at(0x10000000)));
extern OS_TCB   *AppTaskDsoTCB;
extern OS_SEM   SEM_SYNCH;

/*
*********************************************************************************************************
*                                          FatFS
*********************************************************************************************************
*/
extern FRESULT result;
extern FIL file;
extern UINT bw;
extern FATFS fs;

extern void MountSD(void);
extern void UnmountSD(void);
extern void _WriteByte2File(U8 Data, void * p); 

#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
