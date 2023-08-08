#include "bsp_gpio.h"

#include "bsp_SysTick.h" 



uint16_t modbusAddRaed(void)
{
	uint8_t volatile  add1=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
	uint8_t volatile add2=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
	uint8_t volatile add3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);
	uint8_t volatile add4=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8);
	uint8_t volatile add5=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9);
	uint8_t volatile add6=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12);
	
	return add1+add2*2+add3*4+add4*8+add5*16+add6*32;
}
void GPIO_Init(void)
{
	
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOB_CLK_ENABLE(); 
	__HAL_RCC_GPIOA_CLK_ENABLE(); 
	
	//跳线设置端口，6个端口
	GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_12; 				
	GPIO_Initure.Mode=GPIO_MODE_INPUT;  	        	        	   	 
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		
	//LED驱动
	GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15; 				
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP; 
    GPIO_Initure.Pull=GPIO_NOPULL;    
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
	
	//外置看门狗驱动引脚
	GPIO_Initure.Pin=GPIO_PIN_8; 				
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull=GPIO_NOPULL;         
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}




