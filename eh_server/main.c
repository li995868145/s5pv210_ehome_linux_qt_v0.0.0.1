#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <ctype.h>
#include <pthread.h>

#include <log.h>
#include <emi/emiif.h>

#define MAX_PLUGIN_NUMBER	64
#define RECIEVER_PLUGIN_DIR "/home/apps/reciever"
#define TRIGGER_PLUGIN_DIR "/home/apps/trigger"



static int max_plugin_num=MAX_PLUGIN_NUMBER;
static char *reciever_plugin_dir=RECIEVER_PLUGIN_DIR;
static char *trigger_plugin_dir=TRIGGER_PLUGIN_DIR;

int running_check(char *filename){
	return 0;
}

int daemon_operation(void){
	return 0;
}

struct plugin_item {
	char name_list[NAME_MAX];
	void *handle;
};

struct plugin_info {
	int count;
	char path[PATH_MAX];
	struct plugin_item item[];
};

struct plugin_info *get_plugin_name_list(char *plugin_dir){
    struct dirent* ent = NULL;
    DIR *pdir;
	int count=0;
	struct plugin_info *info=(struct plugin_info *)malloc(max_plugin_num*sizeof(struct plugin_item)+sizeof(struct plugin_info));

	if(info==NULL){
		ERR("malloc error\n");
		return NULL;
	}

    if((pdir=opendir(plugin_dir))==NULL ){
		ERR("opendir error\n");
        return NULL;
    }

	strcpy(info->path,plugin_dir);

    while((ent=readdir(pdir))!=NULL){
        if(ent->d_type & DT_DIR){
            if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
                continue;
        }else{
			if(strstr(ent->d_name,".so")){
				strcpy(info->item[count].name_list,ent->d_name);
//				INFO("%d,%s\n",count,ent->d_name);
				count++;
				if(count>max_plugin_num){
					LOG("warning: plugins number exceed the configurated maximum, remainings will be ignored\n");
					break;
				}
			}
        }
    }
    closedir(pdir);
	info->count=count;
    return info;
}


int open_plugin(struct plugin_info *info){
	int i,ret=-1;
	char tmp[PATH_MAX];
	memcpy(tmp,info->path,PATH_MAX);
	for(i=0;i<info->count;i++){
		void *handle;
//		strcat(tmp,info->item[i].name_list);
		strcpy(tmp+strlen(info->path),info->item[i].name_list);
		handle = dlopen(tmp, RTLD_LAZY);
		if (!handle) {
			LOG("open plugins failed: %s, %s\n",tmp, (char *)dlerror());
			dlerror();    /* Clear any existing error */
			continue;
		}
		info->item[i].handle=handle;
		ret=0;
	}
	return ret;
}



int reciever_plugin_register(struct plugin_info *info){
	int i,ret=-1;
	int (*handle)(void);
	char *error;

	for(i=0;i<info->count;i++){
		handle = dlsym(info->item[i].handle, "__reciever_plugin_register_init__");
		if ((error = dlerror()) != NULL){
			LOG("plugin dlsym error: %s,%s\n",info->item[i].name_list,error);
			continue;
		}
		if(handle()){
			LOG("function in plugin %s running error,probably due to the missed emi_core\n",info->item[i].name_list);
			continue;
		}
		ret=0;
	}
	return ret;
}

int close_plugin(struct plugin_info *info){
	int i;
	for(i=0;i<info->count;i++){
	    dlclose(info->item[i].handle);
	}
	return 0;
}

int load_msg_reciever_plugins(char *plugin_dir){
	struct plugin_info *reciever=get_plugin_name_list(plugin_dir);
	if(reciever==NULL){
		ERR("check out your environment variables\n");
		return -1;
	}
	INFO("reciever_plugin dir %s\n",plugin_dir);
	if(open_plugin(reciever)){
		ERR("no valid plugin was found\n");
		return -1;
	}

	if(reciever_plugin_register(reciever)){
		ERR("plugins were found, but none of them was reciever plugin\n");
		return -1;
	}

	return 0;
}

int trigger_plugin_init(struct plugin_info *info){
	int i,ret=-1,trig_error;
	int (*handle)(void);
	char *error;

	pthread_t pthread[info->count];

	for(i=0;i<info->count;i++){
		handle = dlsym(info->item[i].handle, "__trigger_plugin_register_init__");
		if ((error = dlerror()) != NULL){
			LOG("plugin dlsym error: %s,%s\n",info->item[i].name_list,error);
			continue;
		}

		pthread_create(&pthread[i],NULL,(void *(*)(void *))handle,NULL);
		ret=0;
	}

//	pthread_self();

	if(ret)
		return ret;	

	while(1){
		int trigger_ret;
		int trybreak=-1;
		for(i=0;i<info->count;i++){
			if(pthread[i]==(pthread_t)0){
				continue;
			}
			trig_error=pthread_tryjoin_np(pthread[i],(void *)&trigger_ret);
			if(!trig_error){
				LOG("the %s trigger plugin function exit abnormally,code %d\n",info->item[i].name_list,trigger_ret);
				pthread[i]=(pthread_t)0;
			}
			trybreak=0;
		}
		if(trybreak==-1){
			ret=-1;
			break;
		}
		sleep(1);
	}

	return ret;
}

int load_msg_trigger_plugins(char *plugin_dir){
	struct plugin_info *trigger=get_plugin_name_list(plugin_dir);
	if(trigger==NULL){
		ERR("check out your environment variables\n");
		return -1;
	}
	INFO("trigger dir %s\n",plugin_dir);
	if(open_plugin(trigger)){
		ERR("no valid plugin was found\n");
		return -1;
	}

	if(trigger_plugin_init(trigger)){
		ERR("all trigger plugin functions were exited or invalid\n");
		return -1;
	}

	return 0;
}

void load_env(void){
	char *tmp=NULL;
	int num;
	tmp=getenv("RECIEVER_PLUGIN_DIR");
	if(tmp)
		reciever_plugin_dir=tmp;

	tmp=getenv("TRIGGER_PLUGIN_DIR");
	if(tmp)
		trigger_plugin_dir=tmp;
	
	tmp=getenv("MAX_PLUGIN_NUM");
	if(tmp){
		num=strtol(tmp,NULL,10);
		if(isdigit(num)){
			max_plugin_num=num;
		}
	}
	
	INFO("RECIEVER_PLUGIN_DIR=%s,TRIGGER_PLUGIN_DIR=%s,MAX_PLUGIN_NUM=%d\n",reciever_plugin_dir,trigger_plugin_dir,max_plugin_num);

}

int main(int argc,char **argv){

	load_env();

	if(running_check("")){
		LOG("server has been initiated,exiting\n");
		exit(0);
	}

	if(daemon_operation()){
		LOG("cannot run as a daemon,probably because of the lack of root priority\n");
		exit(0);
	}
	
	emi_init();	

	if(load_msg_reciever_plugins(reciever_plugin_dir)){
		ERR("reciever plugins register error\n");
		exit(-1);
	}

	if(load_msg_trigger_plugins(trigger_plugin_dir)){
		ERR("trigger plugins register error\n");
		exit(-1);
	}

	while(1){
		pause();
	}

	return 0;
}
