#ifndef __EHSERVER_LOG__
#define __EHSERVER_LOG__


#define INFO(X...) fprintf(stdout,"%s %s %s:",__DATE__,__TIME__,__func__);fprintf(stdout,X)
#define LOG(X...) fprintf(stdout,"%s %s %s:",__DATE__,__TIME__,__func__);fprintf(stdout,X)
#define ERR(X...) fprintf(stderr,"%s %s %s:",__DATE__,__TIME__,__func__);fprintf(stderr,X)



#endif
