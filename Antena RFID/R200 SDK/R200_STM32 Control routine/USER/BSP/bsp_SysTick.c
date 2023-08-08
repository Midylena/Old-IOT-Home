
#include "bsp_SysTick.h" 

static uint32_t Value=0;



/*
����  ��
      ��ʼ��systick�����ж�
����  ��
      time ��Ϊ�������汾�ĳ�������壬û�о�������
����ֵ��
      ��
*/
void  delay_init(uint32_t time)
{
  uint32_t data;
	/*����1����ĳ�ֵ*/
	data=Sys_CLK/1000;

  SysTick->LOAD  =data-1;                                
  SysTick->VAL   = 0;               
  /*ʱ��Դѡ��Ϊ HCLK */	
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;    
	/*�����ж����ȼ�*/
  HAL_NVIC_SetPriority(SysTick_IRQn, 10, 0);  
  /*���ж�*/	
  SYSTICK_IT(ENABLE);	
	/*ʹ�ܶ�ʱ�� */
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     	
}



/*
����  ��
      ΢�뼶��ʱ
����  ��
      us ����ʱʱ�䣬��λ��΢��
����ֵ��
      ��
*/
void delay_us(uint32_t us)
{
  uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;				//LOAD��ֵ	
	
	ticks=Sys_CLK/1000000*us; 						//��Ҫ�Ľ����� 
	told=SysTick->VAL;        				    //�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;       //��ȡ��������ǰֵ
		if(told>tnow)
			tcnt+=told-tnow;       //û�з������
		else 
			if(told<tnow) 
				tcnt+=reload-tnow+told; //���������
		told=tnow;                  //���浱ǰʱ��
		if(tcnt>=ticks) break;      //�жϼ�ʱʱ���Ƿ�ﵽ
	}
}



/*
����  ��
      ���뼶��ʱ
����  ��
      ms ����ʱʱ�䣬��λ�Ǻ���
����ֵ��
      ��
*/
void delay_ms(uint64_t ms)
{
	for(;ms>0;ms--)
		delay_us(1000);
}



/*
����  ��
      ��ȡʱ���
����  ��
      count ����ȡϵͳʱ��صĻ���
����ֵ��
      ����ϵͳʱ���
*/
uint32_t SYSTICK_getVal(uint32_t *count)
{
	*count=Value;
	return Value;
}



/*
����  ��
      �ж�ʹ�ܻ��ֹ
����  ��
      NewState ��ʹ�ܻ��ֹѡ������� ENABLE  DISABLE
����ֵ��
      ��
*/
void SYSTICK_IT(FunctionalState NewState)
{
	
	if(NewState==ENABLE)
		SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;     //���ж�
	else
		SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;    //���ж�
}



/*
����  ��
      ʱ��ؼ�1
����  ��
      ��
����ֵ��
      ��
*/
void inc_Value(void)
{
	Value++;
}

/**
����  ��
      SysTick�жϺ���
����  ��
      ��
����ֵ��
      ��
 */
void SysTick_Handler(void)
{
	Value++;
	HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}
