#include <plugin.h>
#include <stdio.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/vfs.h>

#include <msg.h>

/* 字符串解析*/
char *parse_string(char *file, char *string)
{
	
        int size=16384;
        char pbuf[size];

        char *ptmp;
        char *ptmp1;
        int fd;
        int nread;

        if (!file || !string) return NULL; 
        /* 打开文件*/
        fd = open(file, O_RDONLY);
        if (fd < 0) {
                ERR("open %s file error!\n", file);
                return NULL;
        }
       

        nread = read(fd, pbuf, size);
        if (nread < 0) {
                ERR("read %s file error!", file);
                return NULL;
        }

        /* 解析字符串*/
        ptmp = strstr(pbuf, string);
		if(ptmp==NULL)
			return NULL;
        ptmp += strlen(string);

        while (1) {
                if ((*ptmp == ' ') || (*ptmp == ':') || (*ptmp == '\t')) { 
                        /* nothing */
                } else {
                        ptmp1 = strchr(ptmp, '\n');
                        *ptmp1 = '\0';
                        break;
                }
                ptmp++;
        }
       
        return ptmp;
}

/* 获取cpu频率*/
void get_cpu_freq(int *cpufreq)
{
        char *file = "/proc/cpuinfo";
//        char *pstr  = "bogomips";
        char *pstr  = "BogoMIPS";
        char *ptmp;

        ptmp = parse_string(file, pstr);
		if(ptmp==NULL){
			*cpufreq=0;
			return;
		}
        *cpufreq = strtol(ptmp, NULL,10);
}

/* 获取当前剩余内存*/
void get_freemem_space(int *freemem)
{
        char *file = "/proc/meminfo";
        char *pstr = "MemFree:";
        char *ptmp;

        ptmp = parse_string(file, pstr);
        
        *freemem = strtol(ptmp, NULL, 10);;
}

/* 获取当前剩余磁盘空间*/
void get_freedisk_space(int *freedisk)
{
        long long free;
        long long blocks;
        struct statfs stat;
        char *dev = "/home/";

        statfs(dev, &stat);
        
        blocks    = stat.f_blocks;        
        free      = stat.f_bfree;
        *freedisk  = free * stat.f_bsize / (1024.00 * 1024.00);
}



int machine_info_reciever(struct emi_msg *msg){
	int tmp;
	struct machine_info info;
	get_freemem_space(&tmp);
	info.freemem=tmp;
	get_freedisk_space(&tmp);
	info.freedisk=tmp;
	get_cpu_freq(&tmp);
	info.frequency=tmp;

	return emi_msg_prepare_return_data(msg,&info,sizeof(info));
}


RECIEVER_PLUGIN_REGISTER(machine_info_reciever,O_MCMMAIN_MACHINE_INFO_QUERY_REQ);
