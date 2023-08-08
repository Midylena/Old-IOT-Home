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
/* ��Բ�ͬ�ı��������ò�ͬ��stdint.h�ļ� */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif
/*FreeRTOS������������*/
#define configUSE_STATS_FORMATTING_FUNCTIONS    1                            //���configUSE_TRACE_FACILITYͬʱΪ1ʱ���������3������ prvWriteNameToBuffer(),vTaskList(),vTaskGetRunTimeStats()
#define configSUPPORT_STATIC_ALLOCATION         1                            //1 ����ʹ�þ�̬������������
#define configSUPPORT_DYNAMIC_ALLOCATION        1                            //֧�ֶ�̬�ڴ�����
#define configTOTAL_HEAP_SIZE			              ( ( size_t ) ( 35 * 1024 ) ) //ϵͳ�����ܵĶѴ�С
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1                            //1 ʱ�������Ƽ���ǰ�����ָ����ѡ����һ��Ҫִ�е�����Ҫ��CPU֧��ǰ����ָ���Ϊstm32�и�ָ�����Ըú����Ϊ1
#define configUSE_TIME_SLICING                  1                            //ʹ��ʱ��Ƭ��ת����
#define configUSE_PREEMPTION		              	1                            //1 ʹ����ռʽ�ںˣ�0ʹ��Э��
#define configUSE_IDLE_HOOK			              	0                            //1��ʹ�ÿ��й��ӣ�0����ʹ��
#define configUSE_TICK_HOOK			        	      0                            //1��ʹ��ʱ��Ƭ���ӣ�0����ʹ��
#define configCPU_CLOCK_HZ			        	      ( SystemCoreClock )          //CPUƵ��
#define configTICK_RATE_HZ				              ( ( TickType_t ) 1000 )      //ʱ�ӽ���Ƶ�ʣ���������Ϊ1000�����ھ���1ms
#define configMAX_PRIORITIES			              ( 32 )                       //��ʹ�õ����ȼ���������� configUSE_PORT_OPTIMISED_TASK_SELECTION Ϊ 1 ʱ���ú겻�ܴ���32����Ϊstm32����32λ mcu
#define configMINIMAL_STACK_SIZE	            	( ( unsigned short ) 130 )   //��������ʹ�õĶ�ջ��С��FreeRTOS ������ջ��С���֣���4�ֽڣ�Ϊ��λ��
#define configMAX_TASK_NAME_LEN		            	( 16 )                       //���������ַ�������
#define configUSE_TRACE_FACILITY		            1                            //Ϊ1���ÿ��ӻ����ٵ���
#define configUSE_16_BIT_TICKS			            0                            //ϵͳ���ļ�����������������
#define configIDLE_SHOULD_YIELD		        	    1                            //Ϊ1ʱ�����������CPUʹ��Ȩ������ͬ���ȼ����û�����
#define configUSE_MUTEXES				                1                            //Ϊ1ʱʹ�û����ź���
#define configQUEUE_REGISTRY_SIZE		            8                            //��Ϊ0ʱ��ʾ���ö��м�¼�������ֵ�ǿ��Լ�¼�Ķ��к��ź��������Ŀ
#define configCHECK_FOR_STACK_OVERFLOW        	0                            //����0ʱ���ö�ջ�����⹦�ܣ����ʹ�ô˹����û������ṩһ��ջ������Ӻ��������ʹ�õĻ�
#define configUSE_RECURSIVE_MUTEXES		        	1                            //Ϊ1ʱʹ�õݹ黥���ź���
#define configUSE_MALLOC_FAILED_HOOK	        	0                            //1ʹ���ڴ�����ʧ�ܹ��Ӻ���
#define configUSE_APPLICATION_TASK_TAG        	0                            //�˺�����Ϊ1�Ļ����� configUSE_APPLICATION_TASK_TAGF() �� xTaskCallApplicationTaskHook() �ͻᱻ����
#define configUSE_COUNTING_SEMAPHORES		        1                            //Ϊ1ʱʹ�ü����ź���

/* ����ʱ��ͳ������ */
#define configGENERATE_RUN_TIME_STATS	        	 1                            //Ϊ1ʱ��������ʱ��ͳ�ƹ���
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() FreeRTOS_TS_Init()           //��ʼ������ʱ��ͳ�ƹ��ܣ�����ʼ����ʱ��6
#define portGET_RUN_TIME_COUNTER_VALUE()         FreeRTOSRunTimeTicks         //��ȡCPUʱ���,��ʱ������ö�ʱ��6ʵ�ֵ�λΪ100us

/*Э���йص����� */
#define configUSE_CO_ROUTINES 		       0     //Ϊ1ʱ����Э�̣�����Э���Ժ��������ļ�croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES  ( 2 ) //Э�̵���Ч���ȼ���Ŀ

/* �����ʱ���йص�����  */
#define configUSE_TIMERS			      	1                            //Ϊ1ʱ���������ʱ��
#define configTIMER_TASK_PRIORITY		  (configMAX_PRIORITIES-1)     //�����ʱ���������ȼ�
#define configTIMER_QUEUE_LENGTH		  10                           //�����ʱ�����г���
#define configTIMER_TASK_STACK_DEPTH	(configMINIMAL_STACK_SIZE*2) //�����ʱ�������ջ��С

/* FreeRTOS��ѡ��������  */
#define INCLUDE_vTaskPrioritySet		  1
#define INCLUDE_uxTaskPriorityGet		  1
#define INCLUDE_vTaskDelete				    1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			    1
#define INCLUDE_vTaskDelayUntil			  1
#define INCLUDE_vTaskDelay				    1
#define INCLUDE_xTaskGetHandle        1

/* �ж��йص����� */
#define configPRIO_BITS       		4                        //���� MCU ʹ�ü�λ���ȼ�,STM32 ʹ�õ��� 4 λ����˴˺�Ϊ 4

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			  0xf //����������ȼ�
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5   //ϵͳ�ɹ��������ж����ȼ�,���ڴ����ȼ����жϺ����в��ܵ��� FreeRTOS �� API ����

#define configKERNEL_INTERRUPT_PRIORITY 		  ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* ���� */
#define configASSERT( x ) if( ( x ) == 0 ) { printf("Error:%s,%d\r\n",__FILE__,__LINE__); taskDISABLE_INTERRUPTS(); for( ;; ); }		
	
/* �жϺ��� */
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

