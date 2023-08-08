

#include "bsp_sys.h"
#include "bsp_SysTick.h" 
#include "bsp_uart.h"


/*
����  ��
      ��������ʱ�ɵ��øú������������Ϣ
�β�  ��
      ��
����ֵ��
			��
*/
void _Error_Handler(char * file, int line)
{
  /* User can add his own implementation to report the HAL error return state */
	printf ("������%s�ļ���%d��",file,line);
  while(1) 
  {
  }
}


/*
����  ��
      ʱ�ӳ�ʼ��
�β�  ��
      PLLM ��PLL��Ƶϵ����������Χ RCC_PLL_MUL2 �� RCC_PLL_MUL16
����ֵ��
			��
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
����  ��
      ����ϵͳʱ��Ϊ72M
�β�  ��
      ��
����ֵ��
			��
*/
void SystemClock_Config(void)
{
  RCC_Config(RCC_PLL_MUL9);
}



/*
����  ��
      ϵͳ��ʼ������
�β�  ��
      ��
����ֵ��
			��
*/
void sys_init(void)
{
	HAL_Init();
  SystemClock_Config();
	delay_init(72);
}

