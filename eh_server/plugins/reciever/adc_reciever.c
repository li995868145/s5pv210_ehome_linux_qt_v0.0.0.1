#include <plugin.h>
#include <stdio.h>
#include <msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <log.h>

#define BEEP_ON			(0x10007)
#define BEEP_OFF		(0x10008)
#define BEEP_DISABLE	(0x10009)
#define BEEP_ENABLE		(0x1000a)



int adc_recieved_set_alarm(struct emi_msg *msg){
    int fd = open("/dev/beeps", O_RDWR);
    if (fd < 0) {
        ERR("open beep error\n");
        return -1;
    }
	
	if(msg->cmd==1){
		INFO("cmd=1,beep on\n");
		ioctl(fd, BEEP_ON);
	}else{
		INFO("cmd=0,beep off\n");
		ioctl(fd, BEEP_OFF);
	}

    close(fd);
	return 0;
}


RECIEVER_PLUGIN_REGISTER(adc_recieved_set_alarm,O_MCMMAIN_ADC_REQ);
