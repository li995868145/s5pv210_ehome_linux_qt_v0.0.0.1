#include <emi/emiif.h>
#include <msg.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"



static inline int machine_zigbee_config(char *ipaddr,char *info){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_SETZIGBEE_MAC_REQ,sizeof(struct zigbee_config),info,0,NULL,0);
}

static inline int machine_net_config(char *ipaddr,char *info){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_NETCONFIG_REQ,sizeof(struct net_config),info,0,NULL,0);
}


static inline int machine_uart_config(char *ipaddr,char *info){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_UARTPARAMETER_REQ,sizeof(struct uart_config),info,0,NULL,0);
}


static inline int machine_login(char *ipaddr,char *info){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_LOGIN_REQ,sizeof(struct passwd_info),info,0,NULL,0);
}


static inline int change_pwd(char *ipaddr,char *info){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_CHANGEPWD_REQ,sizeof(struct passwd_info),info,0,NULL,0);
}

static inline int message_get_machine_info(char *ipaddr,char *ret_data){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_MACHINE_INFO_QUERY_REQ,0,NULL,sizeof(struct machine_info),ret_data,0);
}

static inline int message_set_alarm(char *ipaddr,int on){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_ALARM_REQ,0,NULL,0,NULL,on);
}

static inline int message_set_zigbee(char *ipaddr,int *on){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_ZIGBEE_REQ,sizeof(int),on,0,NULL,0);
}


static inline int message_get_zigbee_mac(char *ipaddr,char *temp){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_ZIGBEE_MAC_REQ,0,NULL,MAX_ZIGBEE_DEVICE*8,temp,0);
}

static inline int message_get_temperature(char *ipaddr,int *temp){
    return emi_msg_send_highlevel_blockreturn(ipaddr,O_MCMMAIN_TEMPERATURE_QUERY_REQ,0,NULL,sizeof(int),temp,0);
}
