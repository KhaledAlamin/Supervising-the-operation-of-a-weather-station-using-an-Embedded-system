/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                        Freescale Kinetis K64
*                                               on the
*
*                                         Freescale FRDM-K64F
*                                          Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <math.h>
#include  <lib_math.h>
#include  <cpu_core.h>

#include  <app_cfg.h>
#include  <os.h>

#include  <fsl_os_abstraction.h>
#include  <system_MK64F12.h>
#include  <board.h>

#include  <bsp_ser.h>

#include "fsl_interrupt_manager.h"
#include "fsl_gpio_common.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_TASK_EQ_0_ITERATION_NBR              16u
#define  APP_TASK_EQ_1_ITERATION_NBR              18u


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_TCB       AppTaskStartTCB;
static  CPU_STK      AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

                                                                /* --------------- SEMAPHORE TASK TEST --------------- */
static  OS_TCB       App_TaskObj0TCB;
static  CPU_STK      App_TaskObj0Stk[APP_CFG_TASK_OBJ_STK_SIZE];

static  OS_TCB       App_TaskObj1TCB;
static  CPU_STK      App_TaskObj1Stk[APP_CFG_TASK_OBJ_STK_SIZE];
                                                                /* ------------ FLOATING POINT TEST TASK -------------- */
static  OS_TCB       App_TaskEq0FpTCB;
static  CPU_STK      App_TaskEq0FpStk[APP_CFG_TASK_EQ_STK_SIZE];

static  OS_TCB       App_TaskEq1FpTCB;
static  CPU_STK      App_TaskEq1FpStk[APP_CFG_TASK_EQ_STK_SIZE];

#if (OS_CFG_SEM_EN > 0u)
static  OS_SEM       App_TraceSem;
#endif

#if (OS_CFG_SEM_EN > 0u)
static  OS_SEM       App_TaskObjSem;
#endif

#if (OS_CFG_MUTEX_EN > 0u)
static  OS_MUTEX     App_TaskObjMutex;
#endif

#if (OS_CFG_Q_EN > 0u)
static  OS_Q         App_TaskObjQ;
#endif

#if (OS_CFG_FLAG_EN > 0u)
static  OS_FLAG_GRP  App_TaskObjFlag;
#endif

static  OS_TCB       TaskIrqAdc0TCB;
static  CPU_STK      TaskIrqAdc0Stk[APP_CFG_TASK_START_STK_SIZE];
static  OS_TCB       TaskIrqAdc1TCB;
static  CPU_STK      TaskIrqAdc1Stk[APP_CFG_TASK_START_STK_SIZE];
static  OS_TCB       Taskftm0TCB;
static  CPU_STK      Taskftm0Stk[APP_CFG_TASK_START_STK_SIZE];
static  OS_TCB       printTCB;
static  CPU_STK      printStk[APP_CFG_TASK_START_STK_SIZE];

static OS_SEM adc0sem;
static OS_SEM adc1sem;
static OS_SEM ftm0sem;
volatile CPU_FP32 rain;
volatile CPU_FP32 temperature;
volatile CPU_FP32 wind;
volatile uint16_t ftm0_overflow_count;
volatile uint16_t ptb2value_adc0_int_hdlr;
volatile uint16_t ptb2value_adc1_int_hdlr;
volatile uint32_t    ftm0_pulse;
/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppObjCreate (void);
static  void  AppTaskCreate(void);
static  void  AppTaskStart (void  *p_arg);

static  void  App_TaskEq0Fp(void  *p_arg);                      /* Floating Point Equation 0 task.                      */
static  void  App_TaskEq1Fp(void  *p_arg);                      /* Floating Point Equation 1 task.                      */
static  void  App_TaskObj0 (void  *p_arg);
static  void  App_TaskObj1 (void  *p_arg);

static 	void  TaskIrqAdc0(void  *p_arg);
static 	void  TaskIrqAdc1(void  *p_arg);
static 	void  print(void  *p_arg);
static 	void  setup_adc0(void);
static 	void  setup_adc1(void);
static 	uint16_t  ADC_read16b_PTB2(void);
static 	uint16_t  ADC_read16b_PTB10(void);
static 	void adc0_int_hdlr (void);
static 	void adc1_int_hdlr (void);
static  void  Taskftm0         (void  *p_arg);
static  void  ftm0_int_hdlr    (void);
static  void  ftm0_setup       (void);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This the main standard entry point.
*
* Note(s)     : none.
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR   err;

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_ERR  cpu_err;
#endif

    hardware_init();
    OSSemCreate(&adc0sem,
                           "adc0sem",
                            0u,
                           &err);
    OSSemCreate(&adc1sem,
                           "adc1sem",
                            0u,
                           &err);

	OSSemCreate(&ftm0sem,
	                       "ftm0sem",
						    0u,
							&err);
    GPIO_DRV_Init(NULL, ledPins);

    INT_SYS_InstallHandler(ADC0_IRQn, adc0_int_hdlr);
      INT_SYS_EnableIRQ(ADC0_IRQn);
      INT_SYS_InstallHandler(ADC1_IRQn, adc1_int_hdlr);
        INT_SYS_EnableIRQ(ADC1_IRQn);




#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_NameSet((CPU_CHAR *)"MK64FN1M0VMD12",
                (CPU_ERR  *)&cpu_err);
#endif

    OSA_Init();                                                 /* Init uC/OS-III.                                      */

    OSTaskCreate(&AppTaskStartTCB,                              /* Create the start task                                */
                 "App Task Start",
                  AppTaskStart,
                  0u,
                  APP_CFG_TASK_START_PRIO,
                 &AppTaskStartStk[0u],
                 (APP_CFG_TASK_START_STK_SIZE / 10u),
                  APP_CFG_TASK_START_STK_SIZE,
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 &err);

    OSA_Start();                                                /* Start multitasking (i.e. give control to uC/OS-III). */

    while (DEF_ON) {                                            /* Should Never Get Here                                */
        ;
    }
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Notes       : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{       OS_ERR    os_err;

    (void)p_arg;                                                /* See Note #1                                          */


    CPU_Init();                                                 /* Initialize the uC/CPU Services.                      */
    Mem_Init();                                                 /* Initialize the Memory Management Module              */
    Math_Init();                                                /* Initialize the Mathematical Module                   */


#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&os_err);                            /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

    BSP_Ser_Init(115200u);

   /* APP_TRACE_DBG(("Creating Application Objects...\n\r"));
    AppObjCreate();                                              Create Applicaiton Kernel Objects

    APP_TRACE_DBG(("Creating Application Tasks...\n\r"));
    AppTaskCreate();
     Create Application Tasks
*/



       OSTaskCreate(&TaskIrqAdc0TCB,								/* Create the start task                                */
                        "TaskIrqAdc0",
   					 TaskIrqAdc0,
                         0u,
                         APP_CFG_TASK_START_PRIO,
                        &TaskIrqAdc0Stk[0u],
                        (APP_CFG_TASK_START_STK_SIZE / 10u),
                         APP_CFG_TASK_START_STK_SIZE,
                         0u,
                         0u,
                         0u,
                        (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                        &os_err);

       OSTaskCreate(&TaskIrqAdc1TCB,								/* Create the start task                                */
                           "TaskIrqAdc1",
      					 TaskIrqAdc1,
                            0u,
                            APP_CFG_TASK_START_PRIO,
                           &TaskIrqAdc1Stk[0u],
                           (APP_CFG_TASK_START_STK_SIZE / 10u),
                            APP_CFG_TASK_START_STK_SIZE,
                            0u,
                            0u,
                            0u,
                           (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                           &os_err);

       OSTaskCreate(&Taskftm0TCB,								/* Create the wind task                                */
                                     "ftm0Task",
     								 Taskftm0,
                                      0u,
                                      APP_CFG_TASK_START_PRIO,
                                     &Taskftm0Stk[0u],
                                     (APP_CFG_TASK_START_STK_SIZE / 10u),
                                      APP_CFG_TASK_START_STK_SIZE,
                                      0u,
                                      0u,
                                      0u,
                                     (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                                     &os_err);

       OSTaskCreate(&printTCB,								/* Create the start task                                */
                              "print",
         					 print,
                               0u,
                               APP_CFG_TASK_START_PRIO,
                              &printStk[0u],
                              (APP_CFG_TASK_START_STK_SIZE / 10u),
                               APP_CFG_TASK_START_STK_SIZE,
                               0u,
                               0u,
                               0u,
                              (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                              &os_err);

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        GPIO_DRV_TogglePinOutput(BOARD_GPIO_LED_GREEN);
        OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &os_err);

    }
}


/*
*********************************************************************************************************
*                                            AppObjCreate()
*
* Description:  Creates the application kernel objects.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Caller(s)   :  App_TaskStart().
*
* Note(s)     :  none.
*********************************************************************************************************
*/

static  void  AppObjCreate (void)
{
    OS_ERR  os_err;


#if (OS_CFG_SEM_EN > 0u)
    OSSemCreate(&App_TaskObjSem,
                "Sem Test",
                 0u,
                 &os_err);

    OSSemCreate(&App_TraceSem,
                "Trace Lock",
                1u,
                &os_err);
#endif

#if (OS_CFG_MUTEX_EN > 0u)
    OSMutexCreate(&App_TaskObjMutex,
                  "Mutex Test",
                  &os_err);
#endif

#if (OS_CFG_Q_EN > 0u)
    OSQCreate(&App_TaskObjQ,
              "Queue Test",
              1u,
              &os_err);
#endif

#if (OS_CFG_FLAG_EN > 0u)
    OSFlagCreate(&App_TaskObjFlag,
                 "Flag Test",
                  DEF_BIT_NONE,
                 &os_err);
#endif
}


/*
*********************************************************************************************************
*                                           AppTaskCreate()
*
* Description :  This function creates the application tasks.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Caller(s)   :  App_TaskStart().
*
* Note(s)     :  none.
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    OS_ERR  os_err;

                                                                /* ---------- CREATE KERNEL OBJECTS TEST TASK --------- */
    OSTaskCreate(&App_TaskObj0TCB,
                 "Kernel Objects Task 0",
                  App_TaskObj0,
                  0u,
                  APP_CFG_TASK_OBJ_PRIO,
                 &App_TaskObj0Stk[0u],
                  APP_CFG_TASK_OBJ_STK_SIZE_LIMIT,
                  APP_CFG_TASK_OBJ_STK_SIZE,
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);

    OSTaskCreate(&App_TaskObj1TCB,
                 "Kernel Objects Task 0",
                  App_TaskObj1,
                  0u,
                  APP_CFG_TASK_OBJ_PRIO,
                 &App_TaskObj1Stk[0u],
                  APP_CFG_TASK_OBJ_STK_SIZE_LIMIT,
                 (APP_CFG_TASK_OBJ_STK_SIZE - 1u),
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);

                                                                /* ------------- CREATE FLOATING POINT TASK ----------- */
    OSTaskCreate(&App_TaskEq0FpTCB,
                 "FP  Equation 1",
                  App_TaskEq0Fp,
                  0u,
                  APP_CFG_TASK_EQ_PRIO,
                 &App_TaskEq0FpStk[0u],
                  APP_CFG_TASK_EQ_STK_SIZE_LIMIT,
                 (APP_CFG_TASK_EQ_STK_SIZE - 1u),
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 &os_err);

    OSTaskCreate(&App_TaskEq1FpTCB,
                 "FP  Equation 1",
                  App_TaskEq1Fp,
                  0u,
                  APP_CFG_TASK_EQ_PRIO,
                 &App_TaskEq1FpStk[0],
                  APP_CFG_TASK_EQ_STK_SIZE_LIMIT,
                 (APP_CFG_TASK_EQ_STK_SIZE - 1u),
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 &os_err);
}


/*
*********************************************************************************************************
*                                            App_TaskObj0()
*
* Description : Test uC/OS-III objects.
*
* Argument(s) : p_arg is the argument passed to 'App_TaskObj0' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Caller(s)   : This is a task
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_TaskObj0 (void  *p_arg)
{
    OS_ERR  os_err;

    (void)p_arg;


    while (DEF_TRUE) {
#if (OS_CFG_SEM_EN > 0u)
        OSSemPost(&App_TaskObjSem,
                   OS_OPT_POST_1,
                  &os_err);
#endif

#if (OS_CFG_MUTEX_EN > 0u)
        OSMutexPend(&App_TaskObjMutex,
                     0u,
                     OS_OPT_PEND_BLOCKING,
                     0u,
                    &os_err);

        OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &os_err);

        OSMutexPost(&App_TaskObjMutex,
                     OS_OPT_POST_NONE,
                    &os_err);
#endif

#if (OS_CFG_Q_EN > 0u)
        OSQPost(        &App_TaskObjQ,
                (void *) 1u,
                         1u,
                         OS_OPT_POST_FIFO,
                        &os_err);

#endif

#if (OS_CFG_FLAG_EN > 0u)
        OSFlagPost(&App_TaskObjFlag,
                    DEF_BIT_00,
                    OS_OPT_POST_FLAG_SET,
                   &os_err);
#endif
        OSTimeDlyHMSM(0u, 0u, 0u, 10u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &os_err);
        APP_TRACE_INFO(("Object test task 0 running ....\n\r"));
    }
}


/*
*********************************************************************************************************
*                                            App_TaskObj1()
*
* Description : Test uC/OS-III objects.
*
* Argument(s) : p_arg is the argument passed to 'App_TaskObj1' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Caller(s)   : This is a task
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_TaskObj1 (void  *p_arg)
{
    OS_ERR       os_err;
    OS_MSG_SIZE  msg_size;


    (void)p_arg;

    while (DEF_TRUE) {

#if (OS_CFG_SEM_EN > 0u)
        OSSemPend(&App_TaskObjSem,
                   0u,
                   OS_OPT_PEND_BLOCKING,
                   0u,
                  &os_err);
#endif

#if (OS_CFG_MUTEX_EN > 0u)
        OSMutexPend(&App_TaskObjMutex,
                     0u,
                     OS_OPT_PEND_BLOCKING,
                     0u,
                    &os_err);

        OSMutexPost(&App_TaskObjMutex,
                     OS_OPT_POST_NONE,
                     &os_err);

#endif

#if (OS_CFG_Q_EN > 0u)
        OSQPend(&App_TaskObjQ,
                 0u,
                 OS_OPT_PEND_BLOCKING,
                &msg_size,
                 0u,
                &os_err);
#endif

#if (OS_CFG_FLAG_EN > 0u)
        OSFlagPend(&App_TaskObjFlag,
                    DEF_BIT_00,
                    0u,
                   (OS_OPT_PEND_FLAG_SET_ALL + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING),
                    0u,
                   &os_err);
#endif
        OSTimeDlyHMSM(0u, 0u, 0u, 10u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &os_err);
        APP_TRACE_INFO(("Object test task 1 running ....\n\r"));
    }
}


/*
*********************************************************************************************************
*                                           App_TaskEq0Fp()
*
* Description : This task finds the root of the following equation.
*               f(x) =  e^-x(3.2 sin(x) - 0.5 cos(x)) using the bisection mehtod
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskEq0Fp' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  App_TaskEq0Fp (void  *p_arg)
{
    CPU_FP32    a;
    CPU_FP32    b;
    CPU_FP32    c;
    CPU_FP32    eps;
    CPU_FP32    f_a;
    CPU_FP32    f_c;
    CPU_FP32    delta;
    CPU_INT08U  iteration;
    RAND_NBR    wait_cycles;


    while (DEF_TRUE) {
        eps       = 0.00001;
        a         = 3.0;
        b         = 4.0;
        delta     = a - b;
        iteration = 0u;
        if (delta < 0) {
            delta = delta * -1.0;
        }

        while (((2.00 * eps) < delta) ||
               (iteration    > 20u  )) {
            c   = (a + b) / 2.00;
            f_a = (exp((-1.0) * a) * (3.2 * sin(a) - 0.5 * cos(a)));
            f_c = (exp((-1.0) * c) * (3.2 * sin(c) - 0.5 * cos(c)));

            if (((f_a > 0.0) && (f_c < 0.0)) ||
                ((f_a < 0.0) && (f_c > 0.0))) {
                b = c;
            } else if (((f_a > 0.0) && (f_c > 0.0)) ||
                       ((f_a < 0.0) && (f_c < 0.0))) {
                a = c;
            } else {
                break;
            }

            delta = a - b;
            if (delta < 0) {
               delta = delta * -1.0;
            }
            iteration++;

            wait_cycles = Math_Rand();
            wait_cycles = wait_cycles % 1000;

            while (wait_cycles > 0u) {
                wait_cycles--;
            }

            if (iteration > APP_TASK_EQ_0_ITERATION_NBR) {
                APP_TRACE_INFO(("App_TaskEq0Fp() max # iteration reached\n\r"));
                break;
            }
        }

        APP_TRACE_INFO(("Eq0 Task Running ....\n\r"));

        if (iteration == APP_TASK_EQ_0_ITERATION_NBR) {
            APP_TRACE_INFO(("Root = %f; f(c) = %f; #iterations : %d \n\r", c, f_c, iteration));
        }
    }
}



/*
*********************************************************************************************************
*                                           App_TaskEq1Fp()
*
* Description : This task finds the root of the following equation.
*               f(x) = x^2 -3 using the bisection mehtod
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskEq()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  App_TaskEq1Fp (void  *p_arg)
{
    CPU_FP32    a;
    CPU_FP32    b;
    CPU_FP32    c;
    CPU_FP32    eps;
    CPU_FP32    f_a;
    CPU_FP32    f_c;
    CPU_FP32    delta;
    CPU_INT08U  iteration;
    RAND_NBR    wait_cycles;


    while (DEF_TRUE) {
        eps       = 0.00001;
        a         = 1.0;
        b         = 4.0;
        delta     = a - b;
        iteration = 0u;

        if (delta < 0) {
            delta = delta * -1.0;
        }

        while ((2.00 * eps) < delta) {
            c   = (a + b) / 2.0;
            f_a = a * a - 3.0;
            f_c = c * c - 3.0;

            if (((f_a > 0.0) && (f_c < 0.0)) ||
                ((f_a < 0.0) && (f_c > 0.0))) {
                b = c;
            } else if (((f_a > 0.0) && (f_c > 0.0)) ||
                       ((f_a < 0.0) && (f_c < 0.0))) {
                a = c;
            } else {
                break;
            }

            delta = a - b;
            if (delta < 0) {
               delta = delta * -1.0;
            }
            iteration++;

            wait_cycles = Math_Rand();
            wait_cycles = wait_cycles % 1000;

            while (wait_cycles > 0u) {
                wait_cycles--;
            }

            if (iteration > APP_TASK_EQ_1_ITERATION_NBR) {
                APP_TRACE_INFO(("App_TaskEq1Fp() max # iteration reached\n\r"));
                break;
            }
        }

        APP_TRACE_INFO(("Eq1 Task Running ....\n\r"));

        if (iteration == APP_TASK_EQ_1_ITERATION_NBR) {
            APP_TRACE_INFO(("Root = %f; f(c) = %f; #iterations : %d \n\r", c, f_c, iteration));
        }
    }
}
static void setup_adc0( void )                                                                            /* ADC SETUP*/
{
SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
ADC0_CFG1 |= ADC_CFG1_MODE(3); /* 16bits ADC*/
ADC0_SC1A |= ADC_SC1_ADCH(31); /* Disable the module, ADCH = 1111 */
}
static void setup_adc1( void )                                                                            /* ADC SETUP*/
{
SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;
ADC1_CFG1 |= ADC_CFG1_MODE(3); /* 16bits ADC*/
ADC1_SC1A |= ADC_SC1_ADCH(31); /* Disable the module, ADCH = 1111 */
}

static uint16_t ADC_read16b_PTB2(void)                                                                     /* PTB2 ADC READ*/
{
ADC0_SC1A = 12 & ADC_SC1_ADCH_MASK; // Write to SC1A to start
// conversion
while(ADC0_SC2 & ADC_SC2_ADACT_MASK)
; //Wait for the conversion to start
while(!(ADC0_SC1A & ADC_SC1_COCO_MASK))
; //Wait for the conversion to complete
return ADC0_RA; // Return the read value
}

static uint16_t ADC_read16b_PTB10(void)                                                                      /* PTB3 ADC READ*/
{
ADC1_SC1A = 14 & ADC_SC1_ADCH_MASK; // Write to SC1A to start
// conversion
while(ADC1_SC2 & ADC_SC2_ADACT_MASK)
; //Wait for the conversion to start
while(!(ADC1_SC1A & ADC_SC1_COCO_MASK))
; //Wait for the conversion to complete
return ADC1_RA; // Return the read value
}

static void adc0_int_hdlr( void )                                                                             /* ADC INTERRUPT HANDLER*/
{
OS_ERR os_err;
CPU_CRITICAL_ENTER();
OSIntEnter();
ptb2value_adc0_int_hdlr = ADC0_RA;
OSSemPost( &adc0sem, OS_OPT_POST_1 | OS_OPT_POST_NO_SCHED, &os_err );
CPU_CRITICAL_EXIT();
OSIntExit();
}
static void adc1_int_hdlr( void )                                                                             /* ADC INTERRUPT HANDLER*/
{
OS_ERR os_err;
CPU_CRITICAL_ENTER();
OSIntEnter();
ptb2value_adc1_int_hdlr = ADC1_RA;
OSSemPost( &adc1sem, OS_OPT_POST_1 | OS_OPT_POST_NO_SCHED, &os_err );
CPU_CRITICAL_EXIT();
OSIntExit();
}


/* RAIN SENSOR*/


static void TaskIrqAdc0( void *p_arg )                                                     // TASK FOR RAIN TO BE SAMPLED EVERY 60 SECS
{
OS_ERR os_err;
CPU_FP32 ptb2fvalue;
(void)p_arg;
setup_adc0();
while (DEF_TRUE) {
ADC0_SC1A = (12 & ADC_SC1_ADCH_MASK) | ADC_SC1_AIEN_MASK;
OSSemPend(&adc0sem, 0u, OS_OPT_PEND_BLOCKING, 0u, &os_err);
ptb2fvalue = (3.3*ptb2value_adc0_int_hdlr)/(65536);

rain=ptb2fvalue*20/3.3;                                                     /* RAIN CALCULATION*/

//BSP_Ser_Printf( "%f Volt\n\r", ptb2fvalue );

OSTimeDlyHMSM(0u, 0u, 60u, 0u,OS_OPT_TIME_HMSM_STRICT, &os_err);
}
}


/* TEMPERATURE SENSOR*/


static void TaskIrqAdc1( void *p_arg )                                                          //TASK FOR TEMPERATURE TO BE SAMPLED FOR EVERY 60 SECS
{
OS_ERR os_err;
CPU_FP32 ptb3fvalue;
(void)p_arg;
setup_adc1();
while (DEF_TRUE) {
ADC1_SC1A = (14 & ADC_SC1_ADCH_MASK) | ADC_SC1_AIEN_MASK;
OSSemPend(&adc1sem, 0u, OS_OPT_PEND_BLOCKING, 0u, &os_err);
ptb3fvalue = (3.3*ptb2value_adc1_int_hdlr)/(65536);

temperature=((80*ptb3fvalue)/3.3)-20;                                      /* TEMPERATURE CALCULATION*/

//BSP_Ser_Printf( "%f MM\n\r", ptb11fvalue );

OSTimeDlyHMSM(0u, 0u, 60u, 0u,OS_OPT_TIME_HMSM_STRICT, &os_err);
}
}
static void ftm0_setup( void )
{
INT_SYS_EnableIRQ(FTM0_IRQn);
INT_SYS_InstallHandler(FTM0_IRQn, ftm0_int_hdlr);
SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK; //Turn on FTM0 timer
FTM0_CONF = 0xC0; //Set the timer in Debug mode, with BDM mode = 0xC0
FTM0_FMS = 0x0; //Enable modifications to the FTM0 configuration
FTM0_MODE |= (FTM_MODE_WPDIS_MASK|FTM_MODE_FTMEN_MASK); //Enable writing
FTM0_CNTIN = FTM_CNTIN_INIT(0); //Initial value of 16 bit counter
FTM0_MOD = FTM_MOD_MOD(0xFFFF); //Modulo of the count over 16 bits
FTM0_SC = (FTM_SC_PS(0)| //ENABLE THE FTM0 with prescaler
FTM_SC_CLKS(0x1)| //set to FTM_C_PS(0)=1
FTM_SC_TOIE_MASK); //CLOCK set to 60Mhz
//interrupt enabled
/*
* Dual-edge capturing for FTM0_CH2 (PTC3) and FTM0_CH3
*/
FTM0_COMBINE = FTM_COMBINE_DECAPEN1_MASK; //Set channel 2 as input for dual capture
FTM0_C2SC = FTM_CnSC_ELSA_MASK; //Capture Rising Edge only on channel 2
FTM0_C3SC = (FTM_CnSC_ELSB_MASK|FTM_CnSC_CHIE_MASK); //Capture Falling Edge
//on channel 3 and
//enable the interrupt
}

static void ftm0_int_hdlr( void )
{
OS_ERR err;
CPU_ERR cpu_err;
CPU_CRITICAL_ENTER();
OSIntEnter();
FTM0_SC &= 0x7F; //clear the Timer Overflow (TOF) bit
if(FTM0_STATUS&0x8) //Check if the FTM0_CH3 captured the event
{
FTM0_STATUS &= 0x0; //Clear the flag
//FTM0_C3V holds the timer value when falling edge has occurred
//FTM0_C2V holds the timer value when the rising edge has occurred
if( FTM0_C2V > FTM0_C3V)
ftm0_pulse = 0xFFFF+FTM0_C3V-FTM0_C2V+(ftm0_overflow_count-1)*65536;
else
ftm0_pulse = FTM0_C3V-FTM0_C2V+(ftm0_overflow_count-1)*65536;
OSSemPost( &ftm0sem, OS_OPT_POST_1 | OS_OPT_POST_NO_SCHED, &err );
ftm0_overflow_count=0;
}
else if(FTM0_STATUS & 0x4) { //count overflow if nothing happen on ch3
	ftm0_overflow_count++; }
CPU_CRITICAL_EXIT();
OSIntExit();
}



static void Taskftm0( void *p_arg )
{
OS_ERR os_err;
CPU_FP32 freq;

(void)p_arg;
ftm0_setup();
while (DEF_TRUE) {
//Setting DECAP1 bit to launch the dual capture process
	FTM0_COMBINE |= FTM_COMBINE_DECAP1_MASK;
	if (ftm0_pulse != 0) {
	OSSemPend(&ftm0sem, 0u, OS_OPT_PEND_BLOCKING, 0u, &os_err);
	freq=(30000000.0/(1.0*ftm0_pulse));
	wind=freq*0.75;
	ftm0_pulse=0;

	} else {
		wind=0;
	}

//BSP_Ser_Printf( "%f Hz\n\r", freq);
OSTimeDlyHMSM(0u, 0u, 1u, 0u, OS_OPT_TIME_HMSM_STRICT, &os_err);
}
}

static void print( void *p_arg )
{
OS_ERR os_err;

(void)p_arg;
static uint32_t count;
count=0;
while (DEF_TRUE) {

BSP_Ser_Printf( "<%d> <%f [m/s]> <%f [mm]> <%f [C]> \n\r",count,wind,rain,temperature );
count++;
OSTimeDlyHMSM(0u, 0u, 1u, 0u,
OS_OPT_TIME_HMSM_STRICT, &os_err);
}
}

