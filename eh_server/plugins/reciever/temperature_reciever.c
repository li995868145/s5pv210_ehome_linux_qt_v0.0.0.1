#include <plugin.h>
#include <stdio.h>
#include <msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <log.h>

#define DS18B20_RESET 0x10001
#define DS18B20_REL   0x10002

int get_temperature(struct emi_msg *tmp){
	int fd;
	int data;
	unsigned char relbit;
	int *ret=(int *)(tmp->data);

	fd = open("/dev/ds18b20", O_RDWR);
	if (fd < 0) {
		ERR("open ds18b20 failed.\n");
		return -1;
	}

       
	relbit = 12;
	ioctl(fd, DS18B20_REL, &relbit);
	read(fd, &data, sizeof(data));

	close(fd);
	*ret=data;

	return emi_msg_prepare_return_data(tmp,ret,sizeof(int));

}


RECIEVER_PLUGIN_REGISTER(get_temperature,O_MCMMAIN_TEMPERATURE_QUERY_REQ);
