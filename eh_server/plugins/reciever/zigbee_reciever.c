#include <plugin.h>
#include <stdio.h>
#include <msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdlib.h>

#define Z_EXTADDR_LEN  8

int speed_arr[] = {B115200,B38400,B19200,B9600,B4800,B2400,B1200,B300};
int bps_arr[]  = {115200,38400,19200,9600,4800,2400,1200,300};

void set_bps(int fd,int bps)
{       
    int i; 
    int status;
    struct termios opt;
    tcgetattr(fd,&opt);
    for(i=0;i<sizeof(speed_arr)/sizeof(int);i++)
    {   
        if(bps==bps_arr[i])
        {   
            tcflush(fd,TCIOFLUSH);
            cfsetispeed(&opt,speed_arr[i]);
            cfsetospeed(&opt,speed_arr[i]);
            status = tcsetattr(fd,TCSANOW,&opt);
            if(status != 0)
            {
                perror("Set Serial Bps Error");
            }   
            return;
        }
        tcflush(fd,TCIOFLUSH);
    }   
}

/**     
 * *@brief   设置串口数据位，停止位和效验位
 * *@param  fd     类型  int  打开的串口文件句柄*
 * *@param  databits 类型  int 数据位   取值 为 7 或者8*
 * *@param  stopbits 类型  int 停止位   取值为 1 或者2*
 * *@param  parity  类型  int  效验类型 取值为N,E,O,,S
 * */
int set_option(int fd,int databits,int stopbits,int parity)
{
    struct termios opt;
    if(tcgetattr(fd,&opt) != 0)
    {
        perror("Get Serial Options Error");
        return(-1);
    }
    opt.c_cflag &= ~CSIZE;
    //set data bit length
    switch (databits) /*设置数据位数*/
    {
        case 7:
            opt.c_cflag |= CS7;
            break;
        case 8:
            opt.c_cflag |= CS8;
            break;
        default:
            ERR("Unsupported data size!\n");
            return -1;
    }
    //set parity bit mode
    switch (parity)
    {
        case 'n':
        case 'N':
            opt.c_cflag &= ~PARENB;             /* Clear parity enable */
            opt.c_iflag &= ~INPCK;                      /* Disable parity checking */
            break;
        case 'o':
        case 'O':
            opt.c_cflag |= (PARODD|PARENB);     /* 设置为奇效验*/
            opt.c_iflag |= INPCK;               /* Enable parity checking */
            break;
        case 'e':
        case 'E':
            opt.c_cflag |= PARENB;              /* Enable parity */
            opt.c_cflag &= ~PARODD;             /* 转换为偶效验*/
            opt.c_iflag |= INPCK;               /* Enable parity checking */
            break;
        case 's':
        case 'S':                               /*as no parity*/
            opt.c_cflag &= ~PARENB;
            opt.c_cflag &= ~CSTOPB;
            break;
        default:
            ERR("Unsupported parity\n");
            return -1;
    }
    //set stop bit length
    switch (stopbits)
    {
        case 1:
            opt.c_cflag &= ~CSTOPB;
            break;
        case 2:
            opt.c_cflag |= CSTOPB;
            break;
        default:
            ERR("Unsupported stop bits\n");
            return -1;
    }
    //set input parity option
    //if (parity != 'n')
    //{
    //opt.c_iflag |= INPCK;
    //}
    opt.c_lflag &= ~(ICANON|ECHO|ECHOE|ISIG);
    opt.c_oflag &= ~OPOST;


    //opt.c_cc[VTIME] = 150; // 15 seconds
    opt.c_cc[VMIN] = 0;

    tcflush(fd,TCIFLUSH);                       //Update the options and do it NOW
    if (tcsetattr(fd,TCSANOW,&opt) != 0)
    {
        perror("Set Serial Options Error");
        return (-1);
    }
    return (0);
}

#define ZIGBEE_DEV "/dev/s3c2410_serial1"

int zigbee_init(int width,int stopbit,int parity){
	int zigbeefd = open(ZIGBEE_DEV, O_RDWR|O_SYNC);
	if (zigbeefd < 0)
		return -1;

	set_bps(zigbeefd,115200);

	if(set_option(zigbeefd,width,stopbit,parity)==-1){
		ERR("set option error\n");
		close(zigbeefd);
		return -1;
	}
		
	return zigbeefd;
}

int zigbee_exit(int fd){
	return close(fd);
}

int ctl_zigbee_light (int zigbeefd, char mac_addr[], unsigned char optLightState)
{
	int i;
    unsigned char cmd[100] = {0};
    cmd[0] = 0xFC;
    cmd[1] = 0x0d;
    cmd[2] = 0xa1;
    cmd[3] = 0x03;
    cmd[4] = optLightState; // 将灯的状态设置为0或者1
    // MAC地址  5
    memcpy (&cmd[5], mac_addr, Z_EXTADDR_LEN);

    // 累加和校验   13
    for (i=1; i<13; i++)
        cmd[13] += cmd[i];

    //先申请串口读取写入锁ziglock
    // 长度14
	
    if (write (zigbeefd, cmd, 14) != 14)
    {
        return -1;
    }

    unsigned char buf[6] = {0};
    while (1){
        if (buf[1] != 0)
            break;
        read (zigbeefd, buf, 6);
    }

	INFO("ctl light result : start(%x) len(%d) ret(%d)\n", buf[0], buf[1], buf[4]);

    if (buf[3] != 0x3)
        return -1;

    return buf[4];
}



#define DEFAULT_UARTCONFIG_FILE "/home/etc/uartconfig"
#define DEFAULT_ZIGCONFIG_FILE "/home/etc/zigbeeconfig"



int get_mac_from_file(char *fn,char mac[]){
    int fd;
    fd=open(fn,O_RDONLY);
    if(fd<0){
        return -1;
    }

    int empty=0,i=0;
    char tmp,*p;
    char buf[16]={0};
    p=buf;

    while(1){
        if(read(fd,&tmp,sizeof(char))<=0){
            break;
        }
        if(tmp!=' '){
            if(empty==1){
                mac[i++]=strtol(buf,NULL,16)&0xff;
                if(i==8)
                    break;
                p=buf;
                memset(buf,0,sizeof(buf));
                empty=0;
            }
            *p++=tmp;
        }else{
            empty=1;
        }
    }
    mac[7]=strtol(buf,NULL,16);

    close(fd);

    return 0;

}


int set_zigbee(struct emi_msg *msg){
    int baudrate;
    int width;
    int stopbit;
    char parity;
    char dev[64];

    FILE *f=fopen(DEFAULT_UARTCONFIG_FILE,"r");
    fscanf(f,"%d %s %d %c %d",&baudrate,dev,&width,&parity,&stopbit);
    fclose(f);

    INFO("%d %s %d %c %d",baudrate,dev,width,parity,stopbit);

	int fd=zigbee_init(width,stopbit,parity);
	if(fd<0){
		ERR("zigbee init error\n");
		return -1;
	}

	char mac[8];
	get_mac_from_file(DEFAULT_ZIGCONFIG_FILE,mac);
	

	unsigned char state=*(int *)msg->data;

	ctl_zigbee_light(fd,mac,state);

	close(fd);

	return 0;

}




RECIEVER_PLUGIN_REGISTER(set_zigbee,O_MCMMAIN_ZIGBEE_REQ);
