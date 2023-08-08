
#include "bsp_SysTick.h" 

static uint32_t Value=0;



/*
功能  ：
      初始化systick，开中断
参数  ：
      time ：为兼容它版本的程序而定义，没有具体意义
返回值：
      无
*/
void  delay_init(uint32_t time)
{
  uint32_t data;
	/*计算1毫秒的初值*/
	data=Sys_CLK/1000;

  SysTick->LOAD  =data-1;                                
  SysTick->VAL   = 0;               
  /*时钟源选择为 HCLK */	
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;    
	/*设置中断优先级*/
  HAL_NVIC_SetPriority(SysTick_IRQn, 10, 0);  
  /*开中断*/	
  SYSTICK_IT(ENABLE);	
	/*使能定时器 */
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     	
}



/*
功能  ：
      微秒级延时
参数  ：
      us ：延时时间，单位是微秒
返回值：
      无
*/
void delay_us(uint32_t us)
{
  uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;				//LOAD的值	
	
	ticks=Sys_CLK/1000000*us; 						//需要的节拍数 
	told=SysTick->VAL;        				    //刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;       //获取计数器当前值
		if(told>tnow)
			tcnt+=told-tnow;       //没有发生溢出
		else 
			if(told<tnow) 
				tcnt+=reload-tnow+told; //发生了溢出
		told=tnow;                  //保存当前时间
		if(tcnt>=ticks) break;      //判断计时时间是否达到
	}
}



/*
功能  ：
      毫秒级延时
参数  ：
      ms ：延时时间，单位是毫秒
返回值：
      无
*/
void delay_ms(uint64_t ms)
{
	for(;ms>0;ms--)
		delay_us(1000);
}



/*
功能  ：
      获取时间截
参数  ：
      count ：获取系统时间截的缓冲
返回值：
      返回系统时间截
*/
uint32_t SYSTICK_getVal(uint32_t *count)
{
	*count=Value;
	return Value;
}



/*
功能  ：
      中断使能或禁止
参数  ：
      NewState ：使能或禁止选项，可以是 ENABLE  DISABLE
返回值：
      无
*/
void SYSTICK_IT(FunctionalState NewState)
{
	
	if(NewState==ENABLE)
		SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;     //开中断
	else
		SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;    //关中断
}



/*
功能  ：
      时间截加1
参数  ：
      无
返回值：
      无
*/
void inc_Value(void)
{
	Value++;
}

/**
功能  ：
      SysTick中断函数
参数  ：
      无
返回值：
      无
 */
void SysTick_Handler(void)
{
	Value++;
	HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}
