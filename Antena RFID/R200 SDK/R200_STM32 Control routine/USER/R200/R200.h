#include "main.h"

#ifndef __RPRMUM_H
#define __RPRMUM_H

#define FALSE 0
#define TRUE 1

typedef unsigned       char u8;
typedef unsigned short int u16;
typedef unsigned       int u32;

#define RPRMUM_pr 				printf
#define RPRMUM_malloc 			malloc
#define RPRMUM_free 	    		free
#define COMM_HEAD_1				0xAA
#define COMM_END				0XDD
#define USC_BUFF_MAX 			400
#define RPRMUM_PASSWORD_NUM		4	//操作密码区
#define RPRMUM_EPC_NUM			12	//EPC数量
#define RPRMUM_TID_NUM			12	//TID数量
#define RPRMUM_USER_NUM			16	//USER数量
#define RPRMUM_MIXER_NUM			4	//USER数量
#define RPRMUM_MaxCarNum			200	//保存的最多卡片数量


	
void RPRMUM_Comm_ReadCard(void);
uint8_t RPRMUM_DataCheck(void);
void RPRMUM_Init(void);
void RPRMUM_DataReceive(u8 data);

#endif

