#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFOFILE "fifo"

int main(int argc, char** argv){
    int n, fd;
    char buf[BUFSIZ];
    int num; 
    //int numArr[4];
    unlink(FIFOFILE);

    if(mkfifo(FIFOFILE, 0666)<0){
        perror("mkfifo()");
        return -1;
    }

    if((fd=open(FIFOFILE,O_RDONLY))<0){
        perror("open()");
        return -1;
    }

    while((n=read(fd,buf,sizeof(buf)))>0){
        num = atoi(buf);
        printf("result : %d\n",num);   
        //printf("%s",buf);
    }


    printf("file end: %s",buf);

    for(int i = 0; i<4; i++){
		numDest += numArr[i]*pow(10,numArrCnt-1-i);
	}

    close(fd);
    return 0;


}