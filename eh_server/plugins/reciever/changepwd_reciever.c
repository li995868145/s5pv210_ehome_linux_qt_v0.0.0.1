#include <plugin.h>
#include <stdio.h>
#include <msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define _XOPEN_SOURCE

#include<stdio.h>
#include<unistd.h>
#include <crypt.h>


#define PASSWD_FILE		"/home/etc/passwd"

int change_passwd(struct emi_msg *msg){
	char nm[64];
	char salt[17];
	char dcrypt[128];
	int size,i=0;
	char tmp;

	struct passwd_info *info=(struct passwd_info *)msg->data;

	int fd=open(PASSWD_FILE,O_RDONLY);
	if(fd<0){
		ERR("read passwd file error\n");
		return -1;
	}
	
	while((size=read(fd,&tmp,1))>0){
		if(tmp==' '){
			nm[i]=0;
			break;
		}else{
			nm[i++]=tmp;
		}
	}

	if(strcmp(nm,info->user)){
		close(fd);
		ERR("wrong username local %s,remote %s \n",nm,info->user);
		return -1;
	}

	i=0;
	while((size=read(fd,&tmp,1))>0){
		if(tmp==' '){
			salt[i]=0;
			break;
		}else{
			salt[i++]=tmp;
		}
	}
	
	i=0;
	while((size=read(fd,&tmp,1))>0){
		if(tmp==' '){
			dcrypt[i]=0;
			break;
		}else{
			dcrypt[i++]=tmp;
		}
	}

	close(fd);
	
	char *c=crypt(info->oldpwd,salt);

	INFO("recieved is %s,len is %d,local is %s,len is %d\n",c,strlen(c),dcrypt,strlen(dcrypt));
	if(strncmp(c,dcrypt,98)){
		ERR("passwd verified failed\n");
		return -1;
	}

	FILE *fp=fopen(PASSWD_FILE, "w");
	if(fp==NULL){
		return -1;
	}

	c=crypt(info->pwd,salt);
	fprintf(fp,"%s %s %s",nm,salt,c);
	fflush(fp);

	fclose(fp);
	
	return 0;
}


RECIEVER_PLUGIN_REGISTER(change_passwd,O_MCMMAIN_CHANGEPWD_REQ);
