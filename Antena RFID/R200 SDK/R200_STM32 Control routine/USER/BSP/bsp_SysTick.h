#ifndef __SysTick_H    //��ֹ�ظ�������ͷ�ļ������û�к궨��__LED_H�����#ifndef ��#else֮��Ĵ���Σ����û��#else�����#endif֮��Ĵ���Ρ�
#define	__SysTick_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"

#define  Sys_CLK   72000000 //ָ��HCLKƵ�ʣ�systick��ʱ����HCLK8��Ƶ�ĵ�


void     delay_init(uint32_t time);
void     delay_us(uint32_t us);
void     delay_ms(uint64_t ms);
uint32_t SYSTICK_getVal(uint32_t *count);
void     SYSTICK_IT(FunctionalState NewState);
void     inc_Value(void);
#ifdef __cplusplus
}
#endif
#endif
