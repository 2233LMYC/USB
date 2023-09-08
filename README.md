# usb

#### 介绍
usb初次尝试,STM32F1 USB通信，以独立按键代替键盘

#### 软件
MDK5 CubeMX 

#### 使用流程
/*

main.c里定义数组：
		uint8_t USB_buff[8];
	各位内容如下：
				buff[0] 
						bit0:left CTRL
						bit1:left shift
						bit2:left ALT
						bit3:left WIN
						bit4:right CTRL
						bit5:right SHIFT
						bit6:right ALT
						bit7:right WIN
						
				buff[1] 保留位
				buff[2] 自定义键1
				buff[3] 自定义键2
				buff[4] 自定义键3
				buff[5] 自定义键4
				buff[6] 自定义键5
				buff[7] 自定义键6


修改：
	usbd_hid.c：
	1、	__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE]  __ALIGN_END 函数里替换描述符为以下内容：
	
			0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
			0x09, 0x06,                    // USAGE (Keyboard)		     用途为键盘 
			0xA1, 0x01,                    // COLLECTION (Application)   表示应用结合，必须以END_COLLECTION来结束 
			0x05, 0x07,                    //   USAGE_PAGE (Keyboard)    用途页为按键 
			0x19, 0xE0,                    //   USAGE_MINIMUM (Keyboard LeftControl)    用途最小值 左Ctrl 
			0x29, 0xE7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)	    用途最大值 右GUI 
			0x15, 0x00,                    //   LOGICAL_MINIMUM (0)	     逻辑最小值 0 
			0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)	     逻辑最大值 1 
			0x75, 0x01,                    //   REPORT_SIZE (1)        报告位大小(这个字段的宽度为1bit) 
			0x95, 0x08,                    //   REPORT_COUNT (8) 	   输入报告第一个字节(报告位大小 8bit) 
			0x81, 0x02,                    //   INPUT (Data,Var,Abs)   报告为输入用 , 从左ctrl到右GUI 8bit刚好构成1个字节
			 
			0x95, 0x01,                    //   REPORT_COUNT (1)	   报告位数量  1个 
			0x75, 0x08,                    //   REPORT_SIZE (8)        输入报告的第二给字节(报告位大小 8bit) 
			0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)   输入用的保留位，设备必须返回0 
			 
			0x95, 0x05,                    //   REPORT_COUNT (5)       报告位数量 5个 
			0x75, 0x01,                    //   REPORT_SIZE (1)		   报告位大小，1bit 
			0x05, 0x08,                    //   USAGE_PAGE (LEDs)      用途为LED 
			0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)   用途最小值 NUM Lock LED灯 
			0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)    用途最大值 Kana 灯 
			0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)   输出用途，用于控制LED等 
			 
			0x95, 0x01,                    //   REPORT_COUNT (1)       报告位数量 1个 
			0x75, 0x03,                    //   REPORT_SIZE (3)        报告位大小 3bit 
			0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)  用于字节补齐，跟前面5个bit进行补齐 
			 
			0x95, 0x06,                    //   REPORT_COUNT (6)    报告位数量 6个
			0x75, 0x08,                  	//   REPORT_SIZE (8)		   报告位大小 8bit 
			0x15, 0x00,                    //   LOGICAL_MINIMUM (0)		   逻辑最小值0 
			0x25, 0x65,                    //   LOGICAL_MAXIMUM (255)      逻辑最大值255 
			0x05, 0x07,                    //   USAGE_PAGE (Keyboard)      用途页为按键 
			0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))   使用值最小为0 
			0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)		    使用值最大为65 
			0x81, 0x00,                    //   INPUT (Data,Ary,Abs)	   输入用，变量，数组，绝对值 
			0xc0 
			

	2、__ALIGN_BEGIN static uint8_t USBD_HID_OtherSpeedCfgDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END 函数内，修改以下内容为keyboard
	
			0x01,          nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse


	3、usbd_hid.h 修改以下内容为：
	
		#define HID_EPIN_SIZE                 0x08U
		
		#define HID_MOUSE_REPORT_DESC_SIZE    63U
		


声明：   mian.c里边

			uint8_t USBD_HID_SendReport(USBD_HandleTypeDef  *pdev,uint8_t *report,uint16_t len);

			extern USBD_HandleTypeDef hUsbDeviceFS;


发送

		USBD_HID_SendReport(&hUsbDeviceFS,USB_buff,8);


*/

