#ifndef __EHSERVER_PLUGIN__
#define __EHSERVER_PLUGIN__

#include <log.h>
#include <err.h>
#include <emi/emiif.h>

#define RECIEVER_PLUGIN_REGISTER(func,msgnum)						\
			int __reciever_plugin_register_init__(void){			\
				return emi_msg_register_blockreturn(msgnum,func);	\
			}

static inline int __trigger_plugin_register_call__(emi_func func,int msgnum,int size,int sleep_time){
	unsigned int flags=0;	
	int ret=0;			
	struct emi_msg *msg=emi_msg_alloc(size);									
	if(msg==NULL)															
		return TRIGGER_PLUGIN_REGISTER_MSGALLOC_ERROR;					
	if(size!=0)																		
		flags=EMI_MSG_TYPE_CMD|EMI_MSG_FLAG_BLOCK_RETURN|EMI_MSG_TYPE_DATA;			
	else																		
		flags=EMI_MSG_TYPE_CMD|EMI_MSG_FLAG_BLOCK_RETURN;							
																						
	while(1){															
		sleep(sleep_time);											
		int functmp=func(msg);										
		if(functmp==TRIGGER_RETURN_ERROR){							
			ret=TRIGGER_PLUGIN_REGISTER_FUNCTION_ERROR;				
			goto error;												
		}else if(functmp==TRIGGER_RETURN_EXIT){						
			ret=TRIGGER_PLUGIN_REGISTER_NORMAL_EXIT;				
			goto error;												
		}else if(functmp==TRIGGER_RETURN_IGNORE){
			continue;
		}

		emi_fill_msg(msg,"127.0.0.1",NULL,0,msgnum,flags);			
		if(emi_msg_send(msg)){										
			ret=TRIGGER_PLUGIN_REGISTER_SEND_ERROR;					
			goto error;												
		}
	}																
	emi_msg_free(msg);												
	return TRIGGER_PLUGIN_REGISTER_NORMAL_EXIT;						
	error:															
		emi_msg_free(msg);											
	return ret;													
}	

#define TRIGGER_PLUGIN_REGISTER(func,msgnum,size,sleep_time)									\
			int __trigger_plugin_register_init__(void){											\
				return __trigger_plugin_register_call__(func,msgnum,size,sleep_time);			\
			}



#endif
