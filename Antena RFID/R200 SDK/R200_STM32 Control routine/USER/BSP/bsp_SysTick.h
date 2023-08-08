#ifndef __SysTick_H    //防止重复包含该头文件，如果没有宏定义__LED_H则编译#ifndef 到#else之间的代码段，如果没有#else则编译#endif之间的代码段。
#define	__SysTick_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"

#define  Sys_CLK   72000000 //指定HCLK频率，systick的时钟由HCLK8分频的到


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
