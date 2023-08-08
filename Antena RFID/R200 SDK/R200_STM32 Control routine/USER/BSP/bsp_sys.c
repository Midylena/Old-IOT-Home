

#include "bsp_sys.h"
#include "bsp_SysTick.h" 
#include "bsp_uart.h"


/*
功能  ：
      发生错误时可调用该函数输出调试信息
形参  ：
      无
返回值：
			无
*/
void _Error_Handler(char * file, int line)
{
  /* User can add his own implementation to report the HAL error return state */
	printf ("错误在%s文件的%d行",file,line);
  while(1) 
  {
  }
}


/*
功能  ：
      时钟初始化
形参  ：
      PLLM ：PLL倍频系数；参数范围 RCC_PLL_MUL2 到 RCC_PLL_MUL16
返回值：
			无
*/
void RCC_Config(uint32_t PLLM)
{
  
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	
  __HAL_RCC_GPIOD_CLK_ENABLE();
    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = PLLM;//RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}



/*
功能  ：
      配置系统时钟为72M
形参  ：
      无
返回值：
			无
*/
void SystemClock_Config(void)
{
  RCC_Config(RCC_PLL_MUL9);
}



/*
功能  ：
      系统初始化函数
形参  ：
      无
返回值：
			无
*/
void sys_init(void)
{
	HAL_Init();
  SystemClock_Config();
	delay_init(72);
}

