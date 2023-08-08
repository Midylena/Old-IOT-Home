#ifndef _UART_
#define _UART_
#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32f1xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;


extern void _Error_Handler(char *, int);
void uart_init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
unsigned short uart_Rx_Data(unsigned char *data,unsigned int *length );


#ifdef __cplusplus
}
#endif
#endif


