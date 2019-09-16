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
	int wfd;
	if(wfd=open("myfifo",O_WRONLY)<0)ERR_EXIT("OPEN FIFO");
	char buf[1024];
	while(1){
	buf[0]=0;
	printf("please enter#...\n");
	fflush(stdout);
	ssize_t s=read(0,buf,sizeof(buf)-1);
	if(s>0){
	buf[s-1]=0;
	write(wfd,buf,strlen(buf));
	
	}
	else if(s<=0){
	ERR_EXIT("READ");
	}
	}	
	close(wfd);
	return 0;
}
