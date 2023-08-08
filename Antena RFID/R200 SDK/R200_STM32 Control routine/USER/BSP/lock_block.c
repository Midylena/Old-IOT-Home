#include "lock_block.h"
#include "include.h"



unsigned char lock_block_addr;
unsigned char lock_block_num;


//�����ݿ�
void lock_block(void)
{
    unsigned char crc_first=0,crc_second=0;
    uint16_t status_2=0;

    memcpy(pMask,USART_BUF+11,8);
    memcpy(&lock_block_addr,USART_BUF+22,1);
    memcpy(&lock_block_num,USART_BUF+24,1);
    if(STATUS_APPLY_15693==0x01)
    {
        for(int g=0; g<3; g++)
        {
            //���
            status = phpalSli15693_ActivateCard(&palSli,
                                                PHPAL_SLI15693_ACTIVATE_ADDRESSED,
                                                PHPAL_SLI15693_FLAG_DATA_RATE,
                                                0xFF,
                                                pMask,
                                                0,
                                                &bDsfid,
                                                pUid,
                                                &bMoreCardsAvaliable);
//								printf("  phpalSli15693_ActivateCard status=%02x					\r\n",status);
            if(status == PH_ERR_SUCCESS)
                break;
        }
        if(status==PH_ERR_SUCCESS)
        {
            for(int i=0; i<lock_block_num; i++)
            {
                lock_block_addr=lock_block_addr+i;
                status_2 =	phalI15693_LockBlock(
                                &al15693,  /**< [In] Pointer to this layers parameter structure. */
                                PHAL_I15693_OPTION_ON,     /**< [In] Option flag; \c #PHAL_I15693_OPTION_OFF: disable; \c #PHAL_I15693_OPTION_ON: enable. */
                                lock_block_addr
                            );
                if( status_2 != PH_ERR_SUCCESS)//д��ʧ��
                    break;
            }
        }

        if( status != 0x00 )      //д��ʧ��
        {
            memcpy(SEND_DATA_BUF,lock_block_err,13);

            //����λ�뷢�������Ӧ
            if(USART_BUF[3]==0x40)
                SEND_DATA_BUF[3]=0x40;
            else if(USART_BUF[3]==0x00)
                SEND_DATA_BUF[3]=0x00;

            ComputeCrc(2,(SEND_DATA_BUF+1),12,&crc_first,&crc_second);
            SEND_DATA_BUF[13]=crc_first;
            SEND_DATA_BUF[14]=crc_second;
            SEND_LENGTH=15;
//						HAL_UART_Transmit(&huart1,SEND_DATA_BUF,15,500);
//					send_date(SEND_DATA_BUF,15);
#ifdef dbg
            printf("\r\n<<15693�����ݿ�  ���ʧ��\r\n");
#endif
        }
        else if(PH_ERR_SUCCESS == status_2)//д��ɹ�
        {
            memcpy(SEND_DATA_BUF,lock_block_suc,11);
            //����λ�뷢�������Ӧ
            if(USART_BUF[3]==0x40)
                SEND_DATA_BUF[3]=0x40;
            else if(USART_BUF[3]==0x00)
                SEND_DATA_BUF[3]=0x00;

            ComputeCrc(2,(SEND_DATA_BUF+1),10,&crc_first,&crc_second);
            SEND_DATA_BUF[11]=crc_first;
            SEND_DATA_BUF[12]=crc_second;
            SEND_LENGTH=13;
//						HAL_UART_Transmit(&huart1,SEND_DATA_BUF,13,500);
//						send_date(SEND_DATA_BUF,13);
#ifdef dbg
            printf("\r\n<<15693�����ݿ�ɹ�\r\n");
#endif
        }
        else if(PH_ERR_SUCCESS != status_2)//д��ʧ��
        {
            memcpy(SEND_DATA_BUF,lock_block_err,13);

            //����λ�뷢�������Ӧ
            if(USART_BUF[3]==0x40)
                SEND_DATA_BUF[3]=0x40;
            else if(USART_BUF[3]==0x00)
                SEND_DATA_BUF[3]=0x00;

            ComputeCrc(2,(SEND_DATA_BUF+1),12,&crc_first,&crc_second);
            SEND_DATA_BUF[13]=crc_first;
            SEND_DATA_BUF[14]=crc_second;
            SEND_LENGTH=15;
//						HAL_UART_Transmit(&huart1,SEND_DATA_BUF,15,500);
//						send_date(SEND_DATA_BUF,15);
#ifdef dbg
            printf("\r\n<<15693�����ݿ�ʧ��\r\n");
#endif
        }
    }
    else
    {
#ifdef dbg
        printf("\r\n<<15693�����ݿ�ʧ��,����15693Э��ʧ��\r\n");
#endif
        memcpy(SEND_DATA_BUF,lock_block_err,13);
        //����λ�뷢�������Ӧ
        if(USART_BUF[3]==0x40)
            SEND_DATA_BUF[3]=0x40;
        else if(USART_BUF[3]==0x00)
            SEND_DATA_BUF[3]=0x00;

        ComputeCrc(2,(SEND_DATA_BUF+1),12,&crc_first,&crc_second);
        SEND_DATA_BUF[13]=crc_first;
        SEND_DATA_BUF[14]=crc_second;
        SEND_LENGTH=15;
//			HAL_UART_Transmit(&huart1,SEND_DATA_BUF,15,500);
//			send_date(SEND_DATA_BUF,15);
    }
}	//if(STATE2&0x10)