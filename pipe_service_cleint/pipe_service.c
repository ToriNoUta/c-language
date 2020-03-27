#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

int main()
{
	umask(0);
	if(mkfifo("myfifo",0644)<0)ERR_EXIT("MKFIFO");
	int rfd;
	if(rfd=open("myfifo",O_RDONLY)<0)ERR_EXIT("OPEN FIFO");
	char buf[1024];
	while(1){
	buf[0]=0;
	printf("please wait...\n");
	ssize_t s=read(rfd,buf,sizeof(buf)-1);
	if(s>0){
	buf[s-1]=0;
	printf("client say# %s\n",buf);
	
	}
	else if(s==0){
	printf("client exit\n");
	exit(EXIT_SUCCESS);
	}
	else ERR_EXIT("READ");
	}
	close(rfd);
	return 0;
}
