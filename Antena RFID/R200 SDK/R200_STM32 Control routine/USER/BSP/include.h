#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include "bsp_uart.h"
#include "bsp_sys.h"
#include "bsp_SysTick.h" 
#include "bsp_iwdg.h"
#include "bsp_gpio.h"
#include "RPRMUM.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_iwdg.h"
#include <stdio.h>
#include <string.h>


//写入
#define WRIET_WAIT		0x01	//写入等待完成
#define WRITE_OK		0x02	//写入成功
#define WRITE_PASSERR	0x03	//密码错误
#define WRITE_NONE		0x04	//卡片不在
#define WRITE_ERR		0x05	//写入失败
#define WRITE_NBACK		0x10	//模块无回复



#endif
