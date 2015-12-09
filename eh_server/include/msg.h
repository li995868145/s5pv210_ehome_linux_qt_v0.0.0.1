#ifndef __EHSERVER_MSG__
#define __EJSERVER_MSG__
#include <stdint.h>
#include <string.h>




/* 消息号*/
/* MCM<->Main 1 ~ 100*/
#define O_MCMMAIN_MACHINE_INFO_QUERY_REQ            1   /* 查看系统信息*/
struct machine_info {
	int32_t frequency;
	int32_t freemem;
	int32_t freedisk;
};


#define O_MCMMAIN_SET_REGISTER_DATA_REQ             2   /* 设置寄存器*/
#define O_MCMMAIN_GET_REGISTER_DATA_REQ             3   /* 获取寄存器*/
#define O_MCMMAIN_SET_EEPROM_DATA_REQ               4   /* 设置作EEPROM*/
#define O_MCMMAIN_GET_EEPROM_DATA_REQ               5   /* 获取EEPROM*/
#define O_MCMMAIN_SOFTWARE_UPDATE_REQ               6   /* 软件在线升级*/
#define O_MCMMAIN_MODEM_REQ                         7   /* 操作3G Modem*/
#define O_MCMMAIN_ZIGBEE_REQ                        8   /* 操作ZIGBEE*/
#define O_MCMMAIN_ZIGBEE_REQ_ON                        1
#define O_MCMMAIN_ZIGBEE_REQ_OFF                        0
#define O_MCMMAIN_ALARM_REQ                          9   /* 操作蜂鸣器*/
#define CMD_MCMMAIN_ALARM_REQ_ON					1
#define CMD_MCMMAIN_ALARM_REQ_OFF					0

#define O_MCMMAIN_LED_REQ                           10  /* 操作LED*/


#define O_MCMMAIN_HARDWARE_SELFTEST_REQ             11  /* 硬件自检*/
#define O_MCMMAIN_TOD_ADJUST_REQ                    12  /* 时间校准*/
#define O_MCMMAIN_VERSION_QUERY_REQ                 13  /* 查看版本信息*/
#define O_MCMMAIN_TEMPERATURE_QUERY_REQ                 14  /*获取温度 */

#define O_MCMMAIN_LOGIN_REQ 		                15  /* 登陆消息 */
#define O_MCMMAIN_CHANGEPWD_REQ 		                16  /* 修改密码 */
struct passwd_info{
	char user[64];
	char oldpwd[64];
	char pwd[64];
};

#define O_MCMMAIN_UARTPARAMETER_REQ 		                17  /* 设置串口参数 */
struct uart_config{
	int baudrate;
	char port[16];
	char datawidth;
	char parity;
	char stopbits;
};

#define O_MCMMAIN_NETCONFIG_REQ                         18  /* 设置网络参数 */
struct net_config{
	char ipv4[16];
};

#define O_MCMMAIN_ADC_REQ                         19  /* 监控烟感（ADC） */

#define O_MCMMAIN_ZIGBEE_MAC_REQ                    20  /* 获取ZIGBEE MAC*/
#define MAX_ZIGBEE_DEVICE	64
#define O_MCMMAIN_SETZIGBEE_MAC_REQ                    21  /* 设置ZIGBEE MAC*/
struct zigbee_config{
	char zigbee[8];
};
#endif
