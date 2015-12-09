#include <plugin.h>
#include <stdio.h>
#include <msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#define DEFAULT_UARTCONFIG_FILE "/home/etc/uartconfig"

int uart_config(struct emi_msg *msg){
	
	struct uart_config *config=(struct uart_config *)msg->data;

	char buf[512];
	sprintf(buf,"%d %s %d %c %d",config->baudrate,config->port,config->datawidth,config->parity,config->stopbits);

	INFO("%s\n",buf);
	
	int fd=open(DEFAULT_UARTCONFIG_FILE,O_WRONLY|O_TRUNC);
	if(fd<0){
		ERR("open error\n");
		return -1;
	}
	
	if(write(fd,buf,strlen(buf))<0){
		ERR("write error\n");
		close(fd);
		return -1;
	}

	close(fd);

	return 0;
}


RECIEVER_PLUGIN_REGISTER(uart_config,O_MCMMAIN_UARTPARAMETER_REQ);
