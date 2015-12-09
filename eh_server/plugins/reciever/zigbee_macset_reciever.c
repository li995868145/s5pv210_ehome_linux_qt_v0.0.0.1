#include <plugin.h>
#include <stdio.h>
#include <msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#define DEFAULT_ZIGCONFIG_FILE "/home/etc/zigbeeconfig"

int zigbee_config(struct emi_msg *msg){
	
	struct zigbee_config *c=(struct zigbee_config *)msg->data;

	FILE *fp=fopen(DEFAULT_ZIGCONFIG_FILE, "w");
	if(fp==NULL){
		return -1;
	}
/*
	fprintf(fp,"%c%c %c%c %c%c %c%c %c%c %c%c %c%c %c%c\n",c->zigbee[0][0],c->zigbee[0][1],c->zigbee[1][0],c->zigbee[1][1],
										c->zigbee[2][0],c->zigbee[2][1],c->zigbee[3][0],c->zigbee[3][1],
										c->zigbee[4][0],c->zigbee[4][1],c->zigbee[5][0],c->zigbee[5][1],
										c->zigbee[6][0],c->zigbee[6][1],c->zigbee[7][0],c->zigbee[7][1]			);
*/
	
	fprintf(fp,"%x %x %x %x %x %x %x %x\n",c->zigbee[0]&0xff,c->zigbee[1]&0xff,
										c->zigbee[2]&0xff,c->zigbee[3]&0xff,
										c->zigbee[4]&0xff,c->zigbee[5]&0xff,
										c->zigbee[6]&0xff,c->zigbee[7]&0xff			);

	fflush(fp);

	fclose(fp);


	return 0;
}


RECIEVER_PLUGIN_REGISTER(zigbee_config,O_MCMMAIN_SETZIGBEE_MAC_REQ);
