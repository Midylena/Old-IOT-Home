#include "main.h"
#include "include.h"

/*
1.使用前请先阅读README.md文档
2.确保数据连接的串口正确
3.确保供电正常
*/

int main(void)
{	

	sys_init();
	uart_init();
	GPIO_Init();
	RPRMUM_Init();
	
    while(TRUE)
    {	
		//检查数据回传
		RPRMUM_DataCheck();
		//发送单次读取命令
		RPRMUM_Comm_ReadCard();
		
		//串口输出数据示例
		/*
		RSSI:-192 dBM 											//标签信号强度
		PC:30 00												//PC码
		EPC: E2  80  68  90  00  00  50  0E  88  C1  6C  A7  	//EPC编码
		********************************
		*/

	}
}

