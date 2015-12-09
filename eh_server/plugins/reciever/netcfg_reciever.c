#include <plugin.h>
#include <stdio.h>
#include <msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>



#define DEFAULT_NETCONFIG_FILE "/home/etc/netconfig"

int net_config(struct emi_msg *msg){
	
	struct net_config *config=(struct net_config *)msg->data;

	int fp=open(DEFAULT_NETCONFIG_FILE, O_WRONLY|O_TRUNC|O_SYNC);
	if(fp<0){
		return -1;
	}

	char buf[64];
	sprintf(buf,"%s",config->ipv4);
	
	write(fp,buf,strlen(buf));

	close(fp);


	return 0;
}


RECIEVER_PLUGIN_REGISTER(net_config,O_MCMMAIN_NETCONFIG_REQ);
