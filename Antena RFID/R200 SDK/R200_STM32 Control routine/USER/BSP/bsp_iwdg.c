#include "bsp_iwdg.h"



IWDG_HandleTypeDef hiwdg;



/*
����  ��
      ��ʼ�����Ź�
����  ��
      ��
����ֵ��
      ��
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
����  ��
      ˢ�¿��Ź�
����  ��
      ��
����ֵ��
      ��
*/
HAL_StatusTypeDef refresh_iwdg(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_IWDG_Refresh(&hiwdg);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
}

