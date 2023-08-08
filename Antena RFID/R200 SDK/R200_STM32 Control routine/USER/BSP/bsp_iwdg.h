#ifndef __iwdg_H
#define __iwdg_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


void iwdg_init(void);
HAL_StatusTypeDef refresh_iwdg(void);

#ifdef __cplusplus
}
#endif
#endif /*__ iwdg_H */

