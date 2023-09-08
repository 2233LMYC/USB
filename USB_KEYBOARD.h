#ifndef USB_KEYBOARD_H_
#define USB_KEYBOARD_H_

#include "main.h"

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


#define        KB_ERROR            0x01
#define        KB_A                0x04
#define        KB_B                0x05
#define        KB_C                0x06
#define        KB_D                0x07
#define        KB_E                0x08
#define        KB_F                0x09
#define        KB_G                0x0A
#define        KB_H                0x0B
#define        KB_I                0x0C
#define        KB_J                0x0D
#define        KB_K                0x0E
#define        KB_L                0x0F
#define        KB_M                0x10
#define        KB_N                0x11
#define        KB_O                0x12
#define        KB_P                0x13
#define        KB_Q                0x14
#define        KB_R                0x15
#define        KB_S                0x16
#define        KB_T                0x17
#define        KB_U                0x18
#define        KB_V                0x19
#define        KB_W                0x1A
#define        KB_X                0x1B
#define        KB_Y                0x1C
#define        KB_Z                0x1D
#define        KB_1                0x1E
#define        KB_2                0x1F
#define        KB_3                0x20
#define        KB_4                0x21
#define        KB_5                0x22
#define        KB_6                0x23
#define        KB_7                0x24
#define        KB_8                0x25
#define        KB_9                0x26
#define        KB_0                0x27
#define        KB_ENTER            0x28
#define        KB_ESC                0x29
#define        KB_BACKSPACE        0x2A
#define        KB_TAB                0x2B
#define        KB_SPACE            0x2C
#define        KB_MIUS                0x2D    //-_
#define        KB_EQUAL            0x2E    //=+
#define        KB_LSQUBRACKET        0x2F    //[{
#define        KB_RSQUBRACKET        0x30    //]}
#define        KB_BACKSLASH        0x31    //\|
#define        KB_SEMICOLON        0x33    //;:
#define        KB_APOSTROPHE        0x34    //'"
#define        KB_TILDE            0x35    //`~
#define        KB_COMMA            0x36    //,<
#define        KB_FULLSTOP            0x37    //.>
#define        KB_SLASH            0x38    ///?
#define        KB_CAPSLOCK            0x39   
#define        KB_F1                0x3A
#define        KB_F2                0x3B
#define        KB_F3                0x3C
#define        KB_F4                0x3D
#define        KB_F5                0x3E
#define        KB_F6                0x3F
#define        KB_F7                0x40
#define        KB_F8                0x41
#define        KB_F9                0x42
#define        KB_F10                0x43
#define        KB_F11                0x44
#define        KB_F12                0x45
#define        KB_PRTSCR            0x46
#define        KB_SCOLLLOCK        0x47
#define        KB_PAUSE            0x48
#define        KB_INSERT            0x49
#define        KB_HOME                0x4A
#define        KB_PAGEUP            0x4B
#define        KB_DELETE            0x4C
#define        KB_END                0x4D
#define        KB_PAGEDOWN            0x4E
#define        KB_RARROW            0x4F
#define        KB_LARROW            0x50
#define        KB_DARROW            0x51
#define        KB_UARROW            0x52
#define        KB_NUMLOCK            0x53
#define        KB_PAD_DIV            0x54    ///
#define        KB_PAD_MUL            0x55    //* 
#define        KB_PAD_MINUS        0x56    //-
#define        KB_PAD_PLUS           0x57    //+
#define        KB_PAD_ENTER        0x58
#define        KB_PAD_1            0x59
#define        KB_PAD_2            0x5A
#define        KB_PAD_3            0x5B
#define        KB_PAD_4            0x5C
#define        KB_PAD_5            0x5D
#define        KB_PAD_6            0x5E
#define        KB_PAD_7            0x5F
#define        KB_PAD_8            0x60
#define        KB_PAD_9            0x61
#define        KB_PAD_0            0x62
#define        KB_PAD_DEL           0x63
#define        KB_APPLICATION        0x65    //RWin右边键





#endif
