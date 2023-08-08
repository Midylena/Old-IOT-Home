
/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_customhid.h"
#include "common.h"

uint8_t            *Receive_buf;
uint8_t            Transmit_buf[64]={0};
USBD_HandleTypeDef hUsbDeviceFS;

/** Usb HID report descriptor. */

////////////////////////配置描述符集合完毕//////////////////////////
//USB键盘报告描述符的定义
__ALIGN_BEGIN static uint8_t DefineReportDescriptor[Define_ReportDescriptor_Size] __ALIGN_END =
{
    0x06, 0x00, 0xff,              // USAGE_PAGE (全局项目)	(Vendor Defined Page 1)
	  0x09, 0x01,                    // USAGE (Keyboard)(区域项目)(Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (主项目)(Application)
	
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x75, 0x08,                    // REPORT_SIZE(全局项目)(8)
    0x95, 0x40,                    // REPORT_COUNT(全局项目)(0x40)
    0x26, 0xff, 0x00,              // LOGICAL_MAXIMUX(全局项目)(255)  
  	0x15, 0x00,                    // LOGICAL_MINIMUX(全局项目)(0)
	
    0x85, 0x01,                    // REPORT_ID(全局项目)(1)
    0x95, 0x01,                    // REPORT_COUNT(全局项目)(1)
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT (主项目)(Data(表示这些数据可以变动),Var(表示这些数据域是独立的变量即每个域表示一个意思),Abs(表示绝对值))(0变量或常量  1数组或单一变量 2 相对值或绝对值)
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
	
    0x85, 0x02,                    // REPORT_ID(全局项目)(2)  
  	0x95, 0x02,                    // REPORT_COUNT(全局项目)(2)
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT (主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x03,                    // REPORT_ID (全局项目)(3)
    0x95, 0x03,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x04,                    // REPORT_ID(全局项目)(4)
    0x95, 0x04,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT (主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)	
		0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x05,                    // REPORT_ID(全局项目)(5)
    0x95, 0x05,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT(主项目)	(Data,Var,Abs)			
		0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x06,                    // REPORT_ID(全局项目)(6)
  	0x95, 0x06,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT(主项目)  (Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x07,                    // REPORT_ID(全局项目)(7)
    0x95, 0x07,                    // REPORT_COUNT (全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1) 
  	0x81, 0x02,                    // INPUT(主项目)(Data,Var,Abs)			
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x08,                    // REPORT_ID(全局项目)(8)
    0x95, 0x08,                    // REPORT_COUNT (全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x09,                    // REPORT_ID(全局项目)(9)
    0x95, 0x09,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		
		0x85, 0x0a,                    // REPORT_ID(全局项目)(9)
    0x95, 0x0a,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x0b,                    // REPORT_ID(全局项目)(9)
    0x95, 0x0b,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x0c,                    // REPORT_ID(全局项目)(9)
    0x95, 0x0c,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x0d,                    // REPORT_ID(全局项目)(9)
    0x95, 0x0d,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x0e,                    // REPORT_ID(全局项目)(9)
    0x95, 0x0e,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x0f,                    // REPORT_ID(全局项目)(9)
    0x95, 0x0f,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x10,                    // REPORT_ID(全局项目)(9)
    0x95, 0x10,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x11,                    // REPORT_ID(全局项目)(9)
    0x95, 0x11,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)	
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x12,                    // REPORT_ID(全局项目)(9)
    0x95, 0x12,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x13,                    // REPORT_ID(全局项目)(9)
    0x95, 0x13,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x14,                    // REPORT_ID(全局项目)(9)
    0x95, 0x14,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x15,                    // REPORT_ID(全局项目)(9)
    0x95, 0x15,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x16,                    // REPORT_ID(全局项目)(9)
    0x95, 0x16,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x17,                    // REPORT_ID(全局项目)(9)
    0x95, 0x17,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		
		0x85, 0x18,                    // REPORT_ID(全局项目)(9)
    0x95, 0x18,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
				
		0x85, 0x19,                    // REPORT_ID(全局项目)(9)
    0x95, 0x19,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
   	0x85, 0x1a,                    // REPORT_ID(全局项目)(9)
    0x95, 0x1a,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x1b,                    // REPORT_ID(全局项目)(9)
    0x95, 0x1b,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x1c,                    // REPORT_ID(全局项目)(9)
    0x95, 0x1c,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x1d,                    // REPORT_ID(全局项目)(9)
    0x95, 0x1d,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		
		0x85, 0x1e,                    // REPORT_ID(全局项目)(9)
    0x95, 0x1e,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
				
		0x85, 0x1f,                    // REPORT_ID(全局项目)(9)
    0x95, 0x1f,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs) 
		
		
		0x85, 0x20,                    // REPORT_ID(全局项目)(1)
    0x95, 0x20,                    // REPORT_COUNT(全局项目)(1)
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT (主项目)(Data(表示这些数据可以变动),Var(表示这些数据域是独立的变量即每个域表示一个意思),Abs(表示绝对值))(0变量或常量  1数组或单一变量 2 相对值或绝对值)
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x21,                    // REPORT_ID(全局项目)(1)
    0x95, 0x21,                    // REPORT_COUNT(全局项目)(1)
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT (主项目)(Data(表示这些数据可以变动),Var(表示这些数据域是独立的变量即每个域表示一个意思),Abs(表示绝对值))(0变量或常量  1数组或单一变量 2 相对值或绝对值)
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
	
    0x85, 0x22,                    // REPORT_ID(全局项目)(2)  
  	0x95, 0x22,                    // REPORT_COUNT(全局项目)(2)
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT (主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE (区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x23,                    // REPORT_ID (全局项目)(3)
    0x95, 0x23,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x24,                    // REPORT_ID(全局项目)(4)
    0x95, 0x24,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT (主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)	
		0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x25,                    // REPORT_ID(全局项目)(5)
    0x95, 0x25,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT(主项目)	(Data,Var,Abs)			
		0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x26,                    // REPORT_ID(全局项目)(6)
  	0x95, 0x26,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPUT(主项目)  (Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x27,                    // REPORT_ID(全局项目)(7)
    0x95, 0x27,                    // REPORT_COUNT (全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1) 
  	0x81, 0x02,                    // INPUT(主项目)(Data,Var,Abs)			
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x28,                    // REPORT_ID(全局项目)(8)
    0x95, 0x28,                    // REPORT_COUNT (全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
    0x85, 0x29,                    // REPORT_ID(全局项目)(9)
    0x95, 0x29,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		
		0x85, 0x2a,                    // REPORT_ID(全局项目)(9)
    0x95, 0x2a,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x2b,                    // REPORT_ID(全局项目)(9)
    0x95, 0x2b,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x2c,                    // REPORT_ID(全局项目)(9)
    0x95, 0x2c,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x2d,                    // REPORT_ID(全局项目)(9)
    0x95, 0x2d,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x2e,                    // REPORT_ID(全局项目)(9)
    0x95, 0x2e,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x2f,                    // REPORT_ID(全局项目)(9)
    0x95, 0x2f,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x30,                    // REPORT_ID(全局项目)(9)
    0x95, 0x30,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x31,                    // REPORT_ID(全局项目)(9)
    0x95, 0x31,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)	
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x32,                    // REPORT_ID(全局项目)(9)
    0x95, 0x32,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x33,                    // REPORT_ID(全局项目)(9)
    0x95, 0x33,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x34,                    // REPORT_ID(全局项目)(9)
    0x95, 0x34,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x35,                    // REPORT_ID(全局项目)(9)
    0x95, 0x35,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x36,                    // REPORT_ID(全局项目)(9)
    0x95, 0x36,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x37,                    // REPORT_ID(全局项目)(9)
    0x95, 0x37,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		
		0x85, 0x38,                    // REPORT_ID(全局项目)(9)
    0x95, 0x38,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
				
		0x85, 0x39,                    // REPORT_ID(全局项目)(9)
    0x95, 0x39,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
   	0x85, 0x3a,                    // REPORT_ID(全局项目)(9)
    0x95, 0x3a,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x3b,                    // REPORT_ID(全局项目)(9)
    0x95, 0x3b,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x3c,                    // REPORT_ID(全局项目)(9)
    0x95, 0x3c,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		0x85, 0x3d,                    // REPORT_ID(全局项目)(9)
    0x95, 0x3d,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
		
		
		0x85, 0x3e,                    // REPORT_ID(全局项目)(9)
    0x95, 0x3e,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs)
				
		0x85, 0x3f,                    // REPORT_ID(全局项目)(9)
    0x95, 0x3f,                    // REPORT_COUNT(全局项目)
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x81, 0x02,                    // INPPUT(主项目)(Data,Var,Abs)		
    0x09, 0x01,                    // USAGE(区域项目)(Vendor Usage 1)
    0x91, 0x02,                    // OUTPUT(主项目)(Data,Var,Abs) 
		
		0x85,0x40,										 // REPORT_ID(全局项目)(9)
		0x95,0x03,										 // REPORT_COUNT(全局项目)
		0x09,0x01,										 // USAGE(区域项目)(Vendor Usage 1)
		0x81,0x02,										 // INPPUT(主项目)(Data,Var,Abs)		
		0x09,0x01,										 // USAGE(区域项目)(Vendor Usage 1)
		0x91,0x02,										 // OUTPUT(主项目)(Data,Var,Abs) 
		
		0x09,0x01,                     // USAGE (区域项目)(Vendor Usage 1)
		0xb1,0x02,                     //FEATURE(主项目)
		0xc0
  }; /* Joystick_ReportDescriptor */
///////////////////////////键盘报告描述符完毕////////////////////////////

//USB鼠标报告描述符的定义
__ALIGN_BEGIN static uint8_t KeyboardReportDescriptor[Keyboard_ReportDescriptor_Size] __ALIGN_END =
{
 0x05, 0x01, // USAGE_Page(全局项目) (Generic Desktop Controls)
 0x09, 0x06, // USAGE (Keyboard) (区域项目)
 0xa1, 0x01, // COLLECTION (Application)  (主项目)
 0x05, 0x07, //	USAGE_Page(全局项目)(Keyboard)
 0x19, 0xe0, // USAGE_minimum (区域项目)(Keyboard LeftControl)
 0x29, 0xe7, // USAGE_maximum (区域项目)(Keyboard Right GUI)
 0x15, 0x00, // Logical_minimux(全局项目)
 0x25, 0x01, // Logical_maximux(全局项目)
	
 0x75, 0x01, // Report_size(全局项目)
 0x95, 0x08, // Report_count(全局项目)
 0x81, 0x02, // Input(主项目)(Data,Var,Abs)
	
 0x95, 0x01, // Report_count (全局项目)
 0x75, 0x08, // REPORT_SIZE (全局项目)
 0x81, 0x03, // INPUT (主项目)(Cnst,Var,Abs)
	
 0x95, 0x05, // REPORT_COUNT (全局项目)
 0x75, 0x01, // REPORT_SIZE (全局项目)
	
 0x05, 0x08, // USAGE_PAGE(全局项目)(LEDs)
 0x19, 0x01, // USAGE_minimux(区域项目)(Num Lock)
 0x29, 0x05, // USAGE_maximux(区域项目)(Kana)
 0x91, 0x02, // OUTPUT(主项目)(Data,Var,Abs)
 0x95, 0x01, // REPORT_COUNT(全局项目)
 0x75, 0x03, // REPORT_SIZE(全局项目)
 0x91, 0x03, // OUTPUT(主项目)(Cnst(常量),Var,Abs)
 0x95, 0x06, // REPORT_COUNT(全局项目)
 0x75, 0x08, // REPORT_SIZE(全局项目)
 0x15, 0x00, // LOGICAL_MINIMUX(全局项目)
 0x25, 0xff, // LOGICAL_MAXIMUX(全局项目)
 0x05, 0x07, // USAGE_PAGE(全局项目)(Keyboard)
 0x19, 0x00, // USAGE_minimux(区域项目)(Reserved(no event indicated))
 0x29, 0x65, // USAGE_MAXIMUX(区域项目)(Keyboard Application)
 0x81, 0x00, // INPUT(主项目)(Data,Ary,Abs)
 0xc0,        // END_COLLECTION
// 0xc0        // END_COLLECTION
};







/** @defgroup USBD_CUSTOM_HID_IF_Exported_Variables
  * @{
  */ 
  extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE BEGIN EXPORTED_VARIABLES */
/* USER CODE END EXPORTED_VARIABLES */



static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t epnum, uint8_t * buff);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
	{
  DefineReportDescriptor,
	KeyboardReportDescriptor
	},
	
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};


/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t epnum, uint8_t *buff)
{
//	USBD_CUSTOM_HID_HandleTypeDef     *hhid;
//  hhid = (USBD_CUSTOM_HID_HandleTypeDef*) hUsbDeviceFS.pClassData;
//	printf("%s",buff);
	//获取数据缓冲区地址
//	Receive_buf=hhid->Report_buf;
	Receive_buf=buff;
  return (USBD_OK);
}


/*
功能  ：
      初始化 USB 外设和 USB 库
参数  ：
      无
返回值：
      无
*/
void USB_DEVICE_Init(void)
{
  /* Init Device Library, add supported class and start the library. */
  USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);  //device descriptor

  USBD_RegisterClass(&hUsbDeviceFS, &USBD_CUSTOM_HID); //configer descriptor
  
  USBD_CUSTOM_HID_RegisterInterface(&hUsbDeviceFS, &USBD_CustomHID_fops_FS); //report descriptor
  
  USBD_Start(&hUsbDeviceFS);
}



/*
功能  ：
      获取来USB接收到的数据
参数  ：
      ms 超时时间
      p  存放接收缓冲区地址的指针,如果没有正确的接收到数据则*p=NULL
返回值：
      无
*/
uint8_t  USB_Receive_Data(uint32_t ms,uint8_t *p)
{
	uint32_t timout=0;
	while(1)
	{
		if(Receive_buf!=NULL)
		{
//			printf("Receive_buf data:  ");
//			for(int i=0;i<(Receive_buf[0]+1);i++)
//				printf("%02x  ",Receive_buf[i]);
//			printf("\r\n");
			
		  memcpy(p,Receive_buf,(Receive_buf[0]+1));
			Receive_buf=NULL;
			return 0;
		}
		HAL_Delay(1);
		timout++;
		if(timout>ms)
		{
			*p=NULL;
			return 1;
		}
	}
}


/*
功能  ：
       通过USB发送数据
说明  ：
      data 数据地址
      len  数据长度
返回值：
      无
*/
void USB_Transmit_Data(uint8_t epnum,uint8_t *data,int32_t len)
{
	while(1)
	{
		//每包数据大小固定为64B，不足64B需要补齐到64B
		if(len>=64)
		{
			USART_BUF[0]=64;
			memcpy(USART_BUF+1,data,63);
//			memcpy(SEND_DATA_BUF+1,USART_BUF,SEND_LENGTH);
			
			
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,epnum, USART_BUF,64);
			data+=63;
			len-=63;
			HAL_Delay(3);
			if(len<=0) break;
		}
		else
		{
			USART_BUF[0]=len;
			memcpy(USART_BUF+1,data,len);
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,epnum, Transmit_buf,len+1);
			HAL_Delay(3);
			break;
		}
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

