/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CUSTOM_HID_IF_H__
#define __USBD_CUSTOM_HID_IF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_customhid.h"
extern uint8_t DefineReportDescriptor[Define_ReportDescriptor_Size];
extern uint8_t KeyboardReportDescriptor[Keyboard_ReportDescriptor_Size];
void USB_DEVICE_Init(void);
uint8_t USB_Receive_Data(uint32_t ms,uint8_t *p);
void USB_Transmit_Data(uint8_t epnum,uint8_t *data,int32_t len);
#ifdef __cplusplus
}
#endif

#endif /* __USBD_CUSTOM_HID_IF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
