#include "include.h"
#include "bsp_uart.h"
#include "RPRMUM.h"


//#define dbg_uart_RX 

//#define RX_time
#define USART_REC_LEN  			100  	//定义最大接收字节数 200


UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;


unsigned  int USART_RX_COUNT=0;			//接收数据计数 
uint8_t  uart_rx_buf[USART_REC_LEN];
uint8_t  uart3_rx_buf[USART_REC_LEN];


void uart_init(void)
{
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
}


/*
功能  ：
      重定向 c 库函数 printf 到串口,使用printf、putchar()时不能开发送中断
形参  ：
      无
返回值：
			无
*/
int fputc(int ch, FILE *f)
{
	while((huart1.Instance->SR & 0x40) == 0);
	huart1.Instance->DR=ch;  
	return ch;
}




/*
功能  ：
      重定向 c 库函数 scanf 到串口，使用scanf、getchar()时不能开接收中断
形参  ：
      无
返回值：
			无
*/
int fgetc(FILE *f)
{
//  uint8_t ch;
//	HAL_UART_Receive(&huart1,&ch,1,1000);  //阻塞式接收指定个字符
//	return (int)ch;       //读USART接收的数据
	while((huart1.Instance->SR & 0x20) == 0);
	return huart1.Instance->DR;
}






/*
功能  ：
      USART1 初始化函数 
形参  ：
      无
返回值：
			无
*/
/* USART1 init function */
void MX_USART1_UART_Init(void)
{
      huart1.Instance = USART1;
      huart1.Init.BaudRate = 115200;
      huart1.Init.WordLength = UART_WORDLENGTH_9B;
      huart1.Init.StopBits = UART_STOPBITS_1;
      huart1.Init.Parity = UART_PARITY_EVEN;
      huart1.Init.Mode = UART_MODE_TX;
      huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
      huart1.Init.OverSampling = UART_OVERSAMPLING_16;
//	HAL_UART_Init(&huart1);	
//	HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1); 	

      if (HAL_UART_Init(&huart1) != HAL_OK)
      {
            _Error_Handler(__FILE__, __LINE__);
      }
      USART1->SR &= (uint16_t)~0x0020;
      /* Enable the UART Data Register not empty Interrupt */
      __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
}

void MX_USART2_UART_Init(void)
{
		//UART 初始化设置
	huart2.Instance=USART2;					    //USART1
	huart2.Init.BaudRate=921600;				    //波特率
	huart2.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	huart2.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	huart2.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	huart2.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	huart2.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&huart2);					    //HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&huart2, (uint8_t *)uart_rx_buf, 1);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
}
void MX_USART3_UART_Init(void)
{
		//UART 初始化设置
	huart3.Instance=USART3;					    //USART3
	huart3.Init.BaudRate=115200;				    //波特率
	huart3.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	huart3.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	huart3.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	huart3.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	huart3.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&huart3);					    //HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&huart3, (uint8_t *)uart3_rx_buf, 1);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
}

//串口1中断处理函数

void USART1_IRQHandler(void)
{

	if( __HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)==SET)
	{
	}
}
//串口2中断处理函数

void USART2_IRQHandler(void)
{

	if( __HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)==SET)
	{
//		MODS_ReciveNew(huart2.Instance->DR);
	}
}
//串口2中断处理函数

void USART3_IRQHandler(void)
{

	if( __HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE)==SET)
	{
          RPRMUM_DataReceive(huart3.Instance->DR);
	}
}

/*
功能  ：
      初始化回调函数
形参  ：
      无
返回值：
			无
*/


void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART1)
  {
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();


	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);				
	HAL_NVIC_SetPriority(USART1_IRQn,1,0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(USART2_IRQn,1,0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */
	  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
//		
//    __HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);
  /* USER CODE END USART2_MspInit 1 */
  }
    else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  	__HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(USART3_IRQn,1,1);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */
	  __HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
//		
//    __HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);
  /* USER CODE END USART2_MspInit 1 */
  }
}


/*
功能  ：
      反初始化回调函数
形参  ：
      无
返回值：
			无
*/

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 


