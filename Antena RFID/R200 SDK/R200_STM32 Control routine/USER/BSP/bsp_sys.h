#ifndef _SYS_
#define _SYS_
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"




void _Error_Handler(char * file, int line);
void RCC_Config(uint32_t PLLM);
void SystemClock_Config(void);
void sys_init(void);






#ifdef __cplusplus
}
#endif
#endif

