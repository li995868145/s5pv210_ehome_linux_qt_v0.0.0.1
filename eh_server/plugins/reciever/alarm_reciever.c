#include <plugin.h>
#include <stdio.h>
#include <msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define BEEP_ON			(0x10007)
#define BEEP_OFF		(0x10008)
#define BEEP_DISABLE	(0x10009)
#define BEEP_ENABLE		(0x1000a)



int set_alarm(struct emi_msg *tmp){
	int ret=0;
    int fd = open("/dev/beeps", O_RDWR);
    if (fd < 0) {
        ERR("open beep error\n");
        return -1;
    }

	if(tmp->cmd==CMD_MCMMAIN_ALARM_REQ_ON){
		INFO("alarm on\n");
        ioctl(fd, BEEP_ENABLE);
        ioctl(fd, BEEP_ON);
		sleep(1);
		ioctl(fd, BEEP_OFF);
		sleep(1);
	}else if(tmp->cmd==CMD_MCMMAIN_ALARM_REQ_OFF){
		INFO("alarm off\n");
        ioctl(fd, BEEP_ON);
		sleep(1);
		ioctl(fd, BEEP_OFF);
        ioctl(fd, BEEP_DISABLE);
	}else{
		ERR("alarm cmd unknown\n");
		ret=-1;
	}
    close(fd);
	return ret;
}


RECIEVER_PLUGIN_REGISTER(set_alarm,O_MCMMAIN_ALARM_REQ);
