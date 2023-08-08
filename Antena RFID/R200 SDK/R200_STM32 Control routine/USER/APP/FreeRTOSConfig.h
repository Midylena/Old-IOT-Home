/*
 * FreeRTOS Kernel V10.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#include "bsp.h"
#include "stdio.h"
/* 针对不同的编译器调用不同的stdint.h文件 */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif
/*FreeRTOS基础配置配置*/
#define configUSE_STATS_FORMATTING_FUNCTIONS    1                            //与宏configUSE_TRACE_FACILITY同时为1时会编译下面3个函数 prvWriteNameToBuffer(),vTaskList(),vTaskGetRunTimeStats()
#define configSUPPORT_STATIC_ALLOCATION         1                            //1 允许使用静态方法创建任务
#define configSUPPORT_DYNAMIC_ALLOCATION        1                            //支持动态内存申请
#define configTOTAL_HEAP_SIZE			              ( ( size_t ) ( 35 * 1024 ) ) //系统所有总的堆大小
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1                            //1 时利用类似计算前导零的指令来选择下一个要执行的任务，要求CPU支持前导零指令，因为stm32有该指令所以该宏可以为1
#define configUSE_TIME_SLICING                  1                            //使能时间片轮转调度
#define configUSE_PREEMPTION		              	1                            //1 使用抢占式内核，0使用协程
#define configUSE_IDLE_HOOK			              	0                            //1，使用空闲钩子；0，不使用
#define configUSE_TICK_HOOK			        	      0                            //1，使用时间片钩子；0，不使用
#define configCPU_CLOCK_HZ			        	      ( SystemCoreClock )          //CPU频率
#define configTICK_RATE_HZ				              ( ( TickType_t ) 1000 )      //时钟节拍频率，这里设置为1000，周期就是1ms
#define configMAX_PRIORITIES			              ( 32 )                       //可使用的优先级数量，如果 configUSE_PORT_OPTIMISED_TASK_SELECTION 为 1 时，该宏不能大于32，因为stm32的是32位 mcu
#define configMINIMAL_STACK_SIZE	            	( ( unsigned short ) 130 )   //空闲任务使用的堆栈大小，FreeRTOS 的任务栈大小以字（即4字节）为单位，
#define configMAX_TASK_NAME_LEN		            	( 16 )                       //任务名字字符串长度
#define configUSE_TRACE_FACILITY		            1                            //为1启用可视化跟踪调试
#define configUSE_16_BIT_TICKS			            0                            //系统节拍计数器变量数据类型
#define configIDLE_SHOULD_YIELD		        	    1                            //为1时空闲任务放弃CPU使用权给其他同优先级的用户任务
#define configUSE_MUTEXES				                1                            //为1时使用互斥信号量
#define configQUEUE_REGISTRY_SIZE		            8                            //不为0时表示启用队列记录，具体的值是可以记录的队列和信号量最大数目
#define configCHECK_FOR_STACK_OVERFLOW        	0                            //大于0时启用堆栈溢出检测功能，如果使用此功能用户必须提供一个栈溢出钩子函数，如果使用的话
#define configUSE_RECURSIVE_MUTEXES		        	1                            //为1时使用递归互斥信号量
#define configUSE_MALLOC_FAILED_HOOK	        	0                            //1使用内存申请失败钩子函数
#define configUSE_APPLICATION_TASK_TAG        	0                            //此宏设置为1的话函数 configUSE_APPLICATION_TASK_TAGF() 和 xTaskCallApplicationTaskHook() 就会被编译
#define configUSE_COUNTING_SEMAPHORES		        1                            //为1时使用计数信号量

/* 运行时间统计配置 */
#define configGENERATE_RUN_TIME_STATS	        	 1                            //为1时启用运行时间统计功能
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() FreeRTOS_TS_Init()           //初始化运行时间统计功能，即初始化定时器6
#define portGET_RUN_TIME_COUNTER_VALUE()         FreeRTOSRunTimeTicks         //获取CPU时间截,该时间截利用定时器6实现单位为100us

/*协程有关的配置 */
#define configUSE_CO_ROUTINES 		       0     //为1时启用协程，启用协程以后必须添加文件croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES  ( 2 ) //协程的有效优先级数目

/* 软件定时器有关的配置  */
#define configUSE_TIMERS			      	1                            //为1时启用软件定时器
#define configTIMER_TASK_PRIORITY		  (configMAX_PRIORITIES-1)     //软件定时器任务优先级
#define configTIMER_QUEUE_LENGTH		  10                           //软件定时器队列长度
#define configTIMER_TASK_STACK_DEPTH	(configMINIMAL_STACK_SIZE*2) //软件定时器任务堆栈大小

/* FreeRTOS可选函数配置  */
#define INCLUDE_vTaskPrioritySet		  1
#define INCLUDE_uxTaskPriorityGet		  1
#define INCLUDE_vTaskDelete				    1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			    1
#define INCLUDE_vTaskDelayUntil			  1
#define INCLUDE_vTaskDelay				    1
#define INCLUDE_xTaskGetHandle        1

/* 中断有关的配置 */
#define configPRIO_BITS       		4                        //设置 MCU 使用几位优先级,STM32 使用的是 4 位，因此此宏为 4

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			  0xf //设置最低优先级
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5   //系统可管理的最高中断优先级,高于此优先级的中断函数中不能调用 FreeRTOS 的 API 函数

#define configKERNEL_INTERRUPT_PRIORITY 		  ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* 断言 */
#define configASSERT( x ) if( ( x ) == 0 ) { printf("Error:%s,%d\r\n",__FILE__,__LINE__); taskDISABLE_INTERRUPTS(); for( ;; ); }		
	
/* 中断函数 */
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

