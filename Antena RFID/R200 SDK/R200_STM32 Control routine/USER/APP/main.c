#include "main.h"
#include "include.h"

/*
1.ʹ��ǰ�����Ķ�README.md�ĵ�
2.ȷ���������ӵĴ�����ȷ
3.ȷ����������
*/

int main(void)
{	

	sys_init();
	uart_init();
	GPIO_Init();
	RPRMUM_Init();
	
    while(TRUE)
    {	
		//������ݻش�
		RPRMUM_DataCheck();
		//���͵��ζ�ȡ����
		RPRMUM_Comm_ReadCard();
		
		//�����������ʾ��
		/*
		RSSI:-192 dBM 											//��ǩ�ź�ǿ��
		PC:30 00												//PC��
		EPC: E2  80  68  90  00  00  50  0E  88  C1  6C  A7  	//EPC����
		********************************
		*/

	}
}

