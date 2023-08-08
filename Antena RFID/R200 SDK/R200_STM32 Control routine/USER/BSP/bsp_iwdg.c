#include "bsp_iwdg.h"



IWDG_HandleTypeDef hiwdg;



/*
功能  ：
      初始化看门狗
参数  ：
      无
返回值：
      无
*/
void iwdg_init(void)
{

  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}



/*
功能  ：
      刷新看门狗
参数  ：
      无
返回值：
      无
*/
HAL_StatusTypeDef refresh_iwdg(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_IWDG_Refresh(&hiwdg);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
}

