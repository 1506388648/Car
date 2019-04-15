/*
*********************************************************************************************************
*	                                  
*	ģ������ : uCOS-III
*	�ļ����� : mian.c
*	��    �� : V1.0
*	˵    �� : uCOS-III����ϵͳ�汾�Ķ���ʾ����
*              ʵ��Ŀ�ģ�
*                1. ѧϰuCOS-III����ϵͳ�汾�Ķ���ʾ����ʵ�֡�
*              ʵ�����ݣ�
*                1. ����ʾ�����Ľ���ʹ���ʵ���뿴��ʵ�����׵Ķ���ʾ�����̡̳�
*                2. Ĭ�������K1���������ڴ���У׼�ģ������Ҫ���ڴ�ӡ����ִ���������Ҫ��MainTask.c�ļ�
*                   �ĺ���DSO_Graph����ʹ����Ӧ���������롣ʹ�ܺ�ȫ���빤�̣����ص��������水�°���K1����
*                   ͨ�����ڴ�ӡ����ִ�������������115200������λ8����żУ��λ�ޣ�ֹͣλ1��
*                   ===============================================================
*                     ���ȼ� ʹ��ջ ʣ��ջ �ٷֱ� ������   ������
*                      Prio   Used  Free   Per    CPU     Taskname
*                        2    180    844   17%    4.63%   App Task DSO
*                       28    303    721   29%   69.48%   App Task GUI
*                        5     35    477   06%    0.00%   App Task UserIF
*                        4     91    421   17%    0.00%   App Task MsgPro
*                        3     85    427   16%    1.36%   App Task Start
*                       29     53     75   41%    0.00%   uC/OS-III Timer Task
*                       30     45     55   45%    0.17%   uC/OS-III Stat Task
*                        1     46     82   35%    0.79%   uC/OS-III Tick Task
*                       31     33     95   25%   23.53%   uC/OS-III Idle Task
*                    �����������ʹ��SecureCRT��V6���������д�������鿴��ӡ��Ϣ��
*                    App Task DSO����    ��˫ͨ��ʾ�������ݴ�������
*                    App Task Start����  ��ʵ�ְ����ʹ���ɨ�衣
*                    App Task MsgPro���� ��ʵ�ֽ�ͼ���ܣ���ͼƬ��BMP��ʽ���浽SD���С�
*                    App Task UserIF���� ����������ʱδ�õ���
*                    App Task GUI����    ��GUI����
*              ע�����
*                 1. ����û�ͨ��MDK����IAR����������FPU����ôʹ���˸�������������ڴ�����ʱ��
*                    ���Ҫʹ�ܲ���OS_OPT_TASK_SAVE_FP���мǣ���û���õ����������������Ҫ�˲�����
*                    �����˴˲����ſ��ԶԸ���Ĵ���������ջ�ͳ�ջ������
*                 2. Ϊ��֧��uC/Probe�������:
*                      (1).MDKҪ��ѡoption->output -> Debug Infomationѡ�ѡ���Ż��ȼ�0
*                      (2).IARҪѡ��ѡ���Ż��ȼ�low���������������ط��ȹ�ѡ
*                        a. option->C/C++ Compiler->Outputѡ���й�ѡGenerate debug information��
*                        b. option->linker->Outputѡ���й�ѡInclude Generate debug information in output��
*                      (3).ʹ��uCOS-III�궨��
*                          #define OS_CFG_DBG_EN             1u
*                      	   #define OS_CFG_STAT_TASK_EN       1u ͬʱ��ʼ��ͳ������
*                      	   #define CPU_CFG_INT_DIS_MEAS_EN   1u 
*                      (4).Ϊ�˷�����ԣ�����OS_CFG_APP_HOOKS_EN��OS_CFG_ARG_CHK_EN��ʹ��
*                 3. ��ʵ���Ƽ�ʹ�ô������SecureCRT��Ҫ�����ڴ�ӡЧ�������롣�������
*                    V6��������������С�
*                 4. ��ؽ��༭��������������TAB����Ϊ4���Ķ����ļ���Ҫ��������ʾ�����롣
*
*	�޸ļ�¼ :
*		�汾��   ����         ����            ˵��
*       V1.0    2018-01-06   Eric2013    1. ST�̼���1.6.1�汾
*                                        2. BSP������V1.2
*                                        3. uCOS-III�汾V3.05.00
*                                        4. uC/CPU�汾V1.30.02
*                                        5. uC/LIB�汾V1.38.01
*                                        6. FatFS�汾V0.11a
*                                        7. STemWin�汾V5.40
*                                        8. DSP��汾V1.5.2
*                                       
*	Copyright (C), 2018-2028, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"



/*
*********************************************************************************************************
*                                       ��̬ȫ�ֱ���
*********************************************************************************************************
*/  
OS_TCB  *AppTaskDsoTCB;
static  CPU_STK  *AppTaskDsoStk;

static  OS_TCB   *AppTaskStartTCB;
static  CPU_STK  *AppTaskStartStk;

static  OS_TCB   *AppTaskMsgProTCB;
static  CPU_STK  *AppTaskMsgProStk;

static  OS_TCB   *AppTaskUserIFTCB;
static  CPU_STK  *AppTaskUserIFStk;

static  OS_TCB   *AppTaskGUITCB;
static  CPU_STK  *AppTaskGUIStk;


/*
*********************************************************************************************************
*                                      ��������
*********************************************************************************************************
*/
static  void  AppTaskDSO            (void     *p_arg);
static  void  AppTaskStart          (void     *p_arg);
static  void  AppTaskMsgPro         (void     *p_arg);
static  void  AppTaskUserIF         (void     *p_arg);
static  void  AppTaskCreate         (void);
static  void  DispTaskInfo          (void);
static  void  AppObjCreate          (void);
static  void  App_Printf (CPU_CHAR *format, ...);


/*
*******************************************************************************************************
*                               ����
*******************************************************************************************************
*/
OS_SEM   SEM_SYNCH;	            /* ����ͬ�� */
static  OS_SEM   AppPrintfSemp;	/* ����printf���� */

arm_rfft_fast_instance_f32 S;
uint32_t fftSize = 2048; 
uint32_t ifftFlag = 0; 
 
uint64_t AppMallocCCM[64*1024/8] __attribute__((at(0x10000000))); /* CCM RAM��̬�ڴ�� */


/*
*********************************************************************************************************
*	�� �� ��: MallocInit
*	����˵��: �û�����ջ���û�TCB(������ƿ�)��ʾ�����ṹ�����ʹ��CCM RAM
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void MallocInit(void)
{
	/* ���ڲ�CCM SRAM��64KBȫ������̬�ڴ�ʹ�� */
	rt_init_mem(AppMallocCCM, 1024*64);

	/* �����ջ��������ƿ���ʹ��CCM RAM */
	AppTaskDsoTCB = (OS_TCB *)rt_alloc_mem(AppMallocCCM, sizeof(OS_TCB));
	AppTaskDsoStk = (CPU_STK *)rt_alloc_mem(AppMallocCCM, 
	                                        sizeof(CPU_STK)*APP_CFG_TASK_DSO_STK_SIZE);

	AppTaskStartTCB = (OS_TCB *)rt_alloc_mem(AppMallocCCM, sizeof(OS_TCB));
	AppTaskStartStk = (CPU_STK *)rt_alloc_mem(AppMallocCCM, 
	                                          sizeof(CPU_STK)*APP_CFG_TASK_START_STK_SIZE);

	AppTaskMsgProTCB = (OS_TCB *)rt_alloc_mem(AppMallocCCM, sizeof(OS_TCB));
	AppTaskMsgProStk = (CPU_STK *)rt_alloc_mem(AppMallocCCM, 
	                                           sizeof(CPU_STK)*APP_CFG_TASK_MsgPro_STK_SIZE);

	AppTaskUserIFTCB = (OS_TCB *)rt_alloc_mem(AppMallocCCM, sizeof(OS_TCB));
	AppTaskUserIFStk = (CPU_STK *)rt_alloc_mem(AppMallocCCM, 
	                                           sizeof(CPU_STK)*APP_CFG_TASK_USER_IF_STK_SIZE);

	AppTaskGUITCB = (OS_TCB *)rt_alloc_mem(AppMallocCCM, sizeof(OS_TCB));
	AppTaskGUIStk = (CPU_STK *)rt_alloc_mem(AppMallocCCM, 
	                                        sizeof(CPU_STK)*APP_CFG_TASK_GUI_STK_SIZE);
	

	/* ����ʾ����ͨ��1��̬�ڴ� */
    g_DSO1 = (DSO_T *)rt_alloc_mem(AppMallocCCM, sizeof(DSO_T));
	
	/* ����ʾ����ͨ��2��̬�ڴ� */
    g_DSO2 = (DSO_T *)rt_alloc_mem(AppMallocCCM, sizeof(DSO_T));
	
	/* �����α�����ṹ�������̬�ڴ� */
    g_Cursors = (CURSORS_T *)rt_alloc_mem(AppMallocCCM, sizeof(CURSORS_T));

	/* �����־λ�ṹ�������̬�ڴ� */
    g_Flag = (FLAG_T *)rt_alloc_mem(AppMallocCCM, sizeof(FLAG_T));
	
	/* ���봥���ṹ�������̬�ڴ� */
    g_TrigVol = (TRIVOLTAGE_T *)rt_alloc_mem(AppMallocCCM, sizeof(TRIVOLTAGE_T));
	
	/* ����FFT��̬�ڴ� */
    testInput_fft_2048 = (float32_t *)rt_alloc_mem(AppMallocCCM, sizeof(float32_t)*2048);
    testOutput_fft_2048 = (float32_t *)rt_alloc_mem(AppMallocCCM, sizeof(float32_t)*2048);
	
	/* ����RMS��̬�ڴ� */	
	g_RMSBUF = (float32_t *)rt_alloc_mem(AppMallocCCM, sizeof(float32_t)*600);
	
	/* ����FIR��̬�ڴ� */
    FirDataInput = (float32_t *)rt_alloc_mem(AppMallocCCM, sizeof(float32_t)*FIR_LENGTH_SAMPLES);
    FirDataOutput = (float32_t *)rt_alloc_mem(AppMallocCCM, sizeof(float32_t)*FIR_LENGTH_SAMPLES);
	firStateF32 = (float32_t *)rt_alloc_mem(AppMallocCCM, sizeof(float32_t)*FIR_StateBufSize);
}

/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: ��׼c������ڡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int main(void)
{
    OS_ERR  err;  
	
	/* ��̬�ڴ���� */
	MallocInit();
	
	/* ��ʼ��uC/OS-III �ں� */
    OSInit(&err);  

	/* ����һ����������Ҳ���������񣩡���������ᴴ�����е�Ӧ�ó������� */
	OSTaskCreate((OS_TCB       *)AppTaskStartTCB,   /* ������ƿ��ַ */           
                 (CPU_CHAR     *)"App Task Start",  /* ������ */
                 (OS_TASK_PTR   )AppTaskStart,      /* ������������ַ */
                 (void         *)0,                 /* ���ݸ�����Ĳ��� */
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO, /* �������ȼ� */
                 (CPU_STK      *)&AppTaskStartStk[0],     /* ��ջ����ַ */
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE / 10, /* ��ջ������������ʾ��10%��Ϊ����� */
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,      /* ��ջ�ռ��С */
                 (OS_MSG_QTY    )0,  /* ������֧�ֽ��ܵ������Ϣ�� */
                 (OS_TICK       )0,  /* ����ʱ��Ƭ */
                 (void         *)0,  /* ��ջ�ռ��С */  
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		
				 /*  �������£�
					OS_OPT_TASK_STK_CHK      ʹ�ܼ������ջ��ͳ������ջ���õĺ�δ�õ�
					OS_OPT_TASK_STK_CLR      �ڴ�������ʱ����������ջ
					OS_OPT_TASK_SAVE_FP      ���CPU�и���Ĵ��������������л�ʱ���渡��Ĵ���������
				 */  
                 (OS_ERR       *)&err);

	/* ����������ϵͳ������Ȩ����uC/OS-III */
    OSStart(&err);                                               
    
    (void)&err;
    
    return (0);
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskDSO
*	����˵��: ˫ͨ��ʾ�������ݴ�������
*	��    ��: ��
*	�� �� ֵ: ��
*   �� �� ��: 2  
*********************************************************************************************************
*/
static void AppTaskDSO (void *p_arg)
{
	OS_ERR      err;
	CPU_TS	    ts;
	void		*p_msg;
	OS_MSG_SIZE	 msg_size;
	uint32_t	 *ucReceive,
	
	/* ʵ������FFT���� */
	fftSize = 2048; 
	
	/* ���任 */
    ifftFlag = 0; 
	
	/* ��ʼ���ṹ��S�еĲ��� */
 	arm_rfft_fast_init_f32(&S, fftSize);
	
    while(1)
    {
		/* �������� */
		p_msg = OSTaskQPend(0,
							OS_OPT_PEND_BLOCKING,
							&msg_size,   /* �˲����ǽ��յ����ݸ��� */
							&ts,
							&err);
		
		if(err == OS_ERR_NONE)
		{
			ucReceive = (uint32_t *)p_msg;
			
			switch (*ucReceive)
            {
				/* ˫ͨ�����δ��� */
				case DspFFT2048Pro_15:
					/* ��ȡ����ADC3��λ�� */
					g_DSO1->usCurPos = 10240 - DMA2_Stream1->NDTR;
				
					/* ��ȡ����ADC1��λ�� */
					g_DSO2->usCurPos = 10240 - DMA2_Stream0->NDTR;
				
					DSO2_WaveTrig(g_DSO2->usCurPos);
					DSO1_WaveTrig(g_DSO1->usCurPos);
					DSO2_WaveProcess();
					DSO1_WaveProcess();
					break;

				/* ���ڼ򵥵�ADC���ݲɼ� */
				case DspMultiMeterPro_14:
					g_uiAdcAvgSample = ADC_GetSampleAvgN();
					break;
				
				/* �����ڵ���Ŀ�ģ���ӡ�����ִ�������Ĭ�ϲ�ʹ�� */
				case DspTaskInfo_13:
					DispTaskInfo();
					break;
				
				/* ����λ��δʹ�� */
				default:
					App_Printf("*ucReceive = %x\r\n", *ucReceive);
					break;
            }
		}
    }
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskStart
*	����˵��: ����һ�����������ڶ�����ϵͳ�����󣬱����ʼ���δ����������������Ҫʵ�ְ����ʹ�����⡣
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 3
*********************************************************************************************************
*/
static void AppTaskStart (void *p_arg)
{
	OS_ERR      err;
	uint8_t  ucCount = 0;
	
    /* �����ڱ���������澯����������������κ�Ŀ����� */	
    (void)p_arg;  
	
	/* BSP ��ʼ���� BSP = Board Support Package �弶֧�ְ����������Ϊ�ײ�������*/
	CPU_Init();  /* �˺���Ҫ���ȵ��ã���Ϊ����������ʹ�õ�us��ms�ӳ��ǻ��ڴ˺����� */
	bsp_Init();       
	BSP_Tick_Init();  
	
#if OS_CFG_STAT_TASK_EN > 0u
     OSStatTaskCPUUsageInit(&err);   
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

	/* ��������ͨ�� */
	AppObjCreate();
	
	/* ����Ӧ�ó�������� */
	AppTaskCreate();
	
    while(1)
    {
		/* 1msһ�δ���ɨ�裬���败���� */
		if(g_tTP.Enable == 1)
		{
			TOUCH_Scan();
			
			/* ����ɨ�� */
			ucCount++;
			if(ucCount == 10)
			{
				ucCount = 0;
				bsp_KeyScan();
			}
		    OSTimeDly(1, OS_OPT_TIME_DLY, &err);			
		}
		
		/* 10msһ�δ���ɨ�裬���ݴ�����GT811 */
		if(g_GT811.Enable == 1)
		{
			bsp_KeyScan();
			GT811_OnePiontScan();
		    OSTimeDly(10, OS_OPT_TIME_DLY, &err);		
		}
		
		/* 10msһ�δ���ɨ�裬���ݴ�����FT5X06 */
		if(g_tFT5X06.Enable == 1)
		{
			bsp_KeyScan();
			FT5X06_OnePiontScan();
		    OSTimeDly(10, OS_OPT_TIME_DLY, &err);
		}
    }     
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskMsgPro
*	����˵��: ʵ�ֽ�ͼ���ܣ���ͼƬ��BMP��ʽ���浽SD����
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 4
*********************************************************************************************************
*/
static void AppTaskMsgPro(void *p_arg)
{
	uint32_t ulStart, ulEnd;
	OS_ERR      err;
	uint8_t		Pic_Name = 0;
	char buf[20];

	(void)p_arg;
		  
	while(1)
	{	
		/* �ȴ���ȡ�ź���ͬ����Ϣ�����յ���ʵ�ֽ�ͼ���ܣ���ͼƬ��BMP��ʽ���浽SD���� */
		OSSemPend((OS_SEM *)&SEM_SYNCH,
				  (OS_TICK )0,
				  (OS_OPT  )OS_OPT_PEND_BLOCKING,
				  (CPU_TS  )0,
				  (OS_ERR *)&err);
		
		if(err == OS_ERR_NONE)
		{	
			sprintf(buf,"0:/PicSave/%d.bmp",Pic_Name);
			
			/* ��¼��ͼǰ��ʼʱ�� */
			ulStart = OSTimeGet(&err);
			
			/* ���������� */
			//OSSchedLock(&err);
			
			/* ���SD����û��PicSave�ļ�������д��� */
			result = f_mkdir("0:/PicSave");
			
			/* ������ͼ */
			result = f_open(&file,buf, FA_WRITE|FA_CREATE_ALWAYS);
			
			/* ��SD������BMPͼƬ */
			GUI_BMP_Serialize(_WriteByte2File, &file);
			
			/* ������ɺ�ر�file */
		    result = f_close(&file);
			
			/* ���������� */
			//OSSchedUnlock(&err);
			
			/* ��¼��ͼ��ʱ�䲢��ȡ��ͼ���̺�ʱ */
			ulEnd = OSTimeGet(&err);
			ulEnd -= ulStart;
			
			App_Printf("��ͼ��ɣ���ʱ = %dms\r\n", ulEnd);
			Pic_Name++; 		
		}										  	 	       											  
	}   
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskUserIF
*	����˵��: ��������δʹ�á�
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 5
*********************************************************************************************************
*/
static void AppTaskUserIF(void *p_arg)
{
	OS_ERR      err;
	
	(void)p_arg;	              /* ������������� */
	
  
	while (1) 
	{   		
		OSTimeDly(1000, OS_OPT_TIME_DLY, &err);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskGUI
*	����˵��: GUI����������ȼ�		  			  
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: OS_CFG_PRIO_MAX - 4u
*********************************************************************************************************
*/
static void AppTaskGUI(void *p_arg)
{
    (void)p_arg;		/* ����������澯 */
		
	while (1) 
	{
		MainTask();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  AppTaskCreate (void)
{
	OS_ERR      err;
	
	/**************����MsgPro����*********************/
	OSTaskCreate((OS_TCB       *)AppTaskMsgProTCB,             
                 (CPU_CHAR     *)"App Task MsgPro",
                 (OS_TASK_PTR   )AppTaskMsgPro, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_MsgPro_PRIO,
                 (CPU_STK      *)&AppTaskMsgProStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_MsgPro_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_MsgPro_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR       *)&err);
				 
	/**************����USER IF����*********************/
	OSTaskCreate((OS_TCB       *)AppTaskUserIFTCB,             
                 (CPU_CHAR     *)"App Task UserIF",
                 (OS_TASK_PTR   )AppTaskUserIF, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_USER_IF_PRIO,
                 (CPU_STK      *)&AppTaskUserIFStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_USER_IF_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_USER_IF_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

	/**************����GUI����*********************/			 
	OSTaskCreate((OS_TCB       *)AppTaskGUITCB,              
                 (CPU_CHAR     *)"App Task GUI",
                 (OS_TASK_PTR   )AppTaskGUI, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_GUI_PRIO,
                 (CPU_STK      *)&AppTaskGUIStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_GUI_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_GUI_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR       *)&err);	

	/**************����DSO����*********************/			 
	OSTaskCreate((OS_TCB       *)AppTaskDsoTCB,              
                 (CPU_CHAR     *)"App Task DSO",
                 (OS_TASK_PTR   )AppTaskDSO, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_DSO_PRIO,
                 (CPU_STK      *)&AppTaskDsoStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_DSO_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_DSO_STK_SIZE,
                 (OS_MSG_QTY    )5,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR       *)&err);					 
}

/*
*********************************************************************************************************
*	�� �� ��: AppObjCreate
*	����˵��: ��������ͨѶ
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  AppObjCreate (void)
{
	OS_ERR      err;

	/* 
	   �����ź�����ֵΪ1��ʱ�����ʵ�ֻ��⹦�ܣ�Ҳ����ֻ��һ����Դ����ʹ�� 
	   �������ǽ�����1�Ĵ�ӡ������Ϊ��������Դ����ֹ���ڴ�ӡ��ʱ������������ռ
	   ��ɴ��ڴ�ӡ���ҡ�
	*/
	OSSemCreate((OS_SEM    *)&AppPrintfSemp,
				(CPU_CHAR  *)"AppPrintfSemp",
				(OS_SEM_CTR )1,
				(OS_ERR    *)&err);	
	
	/* ��������ֵΪ0������ʵ������ͬ������ */
	OSSemCreate((OS_SEM    *)&SEM_SYNCH,
				(CPU_CHAR  *)"SEM_SYNCH",
				(OS_SEM_CTR )0,
				(OS_ERR    *)&err);
}

/*
*********************************************************************************************************
*	�� �� ��: App_Printf
*	����˵��: �̰߳�ȫ��printf��ʽ		  			  
*	��    ��: ͬprintf�Ĳ�����
*             ��C�У����޷��г����ݺ���������ʵ�ε����ͺ���Ŀʱ,������ʡ�Ժ�ָ��������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  App_Printf(CPU_CHAR *format, ...)
{
    CPU_CHAR  buf_str[80 + 1];
    va_list   v_args;
    OS_ERR    os_err;


    va_start(v_args, format);
   (void)vsnprintf((char       *)&buf_str[0],
                   (size_t      ) sizeof(buf_str),
                   (char const *) format,
                                  v_args);
    va_end(v_args);

	/* ������� */
    OSSemPend((OS_SEM  *)&AppPrintfSemp,
              (OS_TICK  )0u,
              (OS_OPT   )OS_OPT_PEND_BLOCKING,
              (CPU_TS  *)0,
              (OS_ERR  *)&os_err);

    printf("%s", buf_str);

   (void)OSSemPost((OS_SEM  *)&AppPrintfSemp,
                   (OS_OPT   )OS_OPT_POST_1,
                   (OS_ERR  *)&os_err);

}

/*
*********************************************************************************************************
*	�� �� ��: DispTaskInfo
*	����˵��: ��uCOS-III������Ϣͨ�����ڴ�ӡ����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DispTaskInfo(void)
{
	OS_TCB      *p_tcb;	        /* ����һ��������ƿ�ָ��, TCB = TASK CONTROL BLOCK */
	float CPU = 0.0f;
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();
    p_tcb = OSTaskDbgListPtr;
    CPU_CRITICAL_EXIT();
	
	/* ��ӡ���� */
	App_Printf("===============================================================\r\n");
	App_Printf(" ���ȼ� ʹ��ջ ʣ��ջ �ٷֱ� ������   ������\r\n");
	App_Printf("  Prio   Used  Free   Per    CPU     Taskname\r\n");

	/* ����������ƿ��б�(TCB list)����ӡ���е���������ȼ������� */
	while (p_tcb != (OS_TCB *)0) 
	{
		CPU = (float)p_tcb->CPUUsage / 100;
		App_Printf("   %2d  %5d  %5d   %02d%%   %5.2f%%   %s\r\n", 
		p_tcb->Prio, 
		p_tcb->StkUsed, 
		p_tcb->StkFree, 
		(p_tcb->StkUsed * 100) / (p_tcb->StkUsed + p_tcb->StkFree),
		CPU,
		p_tcb->NamePtr);		
	 	
		CPU_CRITICAL_ENTER();
        p_tcb = p_tcb->DbgNextPtr;
        CPU_CRITICAL_EXIT();
	}
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
