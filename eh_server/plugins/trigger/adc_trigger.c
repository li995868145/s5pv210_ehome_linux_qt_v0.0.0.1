#include <plugin.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <msg.h>
#include <emi/emi.h>


#define ADC_RESOL       0x10012
#define ADC_INPUT_PIN   0x10013

int alarmed=0;


int adc_trigger(struct emi_msg *msg){
	int fd;
	int voltage;
	double adcinfo;
	

    fd = open("/dev/s5pv210_adc", O_RDWR);
	if(fd<0){
		return TRIGGER_RETURN_IGNORE; 
	}
	int nbit=12;
	int port=1;

    ioctl(fd, ADC_RESOL, &nbit);
    ioctl(fd, ADC_INPUT_PIN, &port);


	read(fd, &voltage, sizeof(voltage));
	adcinfo =  (float)voltage / (1 << nbit) * 3.3;

	close(fd);

	if(alarmed==0){
		if(adcinfo>3.0){
			msg->cmd=1;
			alarmed=1;
			return TRIGGER_RETURN_SUCCESS; 
		}
	}else{
		if(adcinfo<3.0){
			msg->cmd=0;
			alarmed=0;
			return TRIGGER_RETURN_SUCCESS; 
		}
	}

		return TRIGGER_RETURN_IGNORE; 

}


TRIGGER_PLUGIN_REGISTER(adc_trigger,O_MCMMAIN_ADC_REQ,0,5);
