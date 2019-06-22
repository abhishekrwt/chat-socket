#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include<pthread.h>

char str[100];
char sendBuff[1024];
char s[100];
char out[4]="bye";
char name[100]="Mr_Robot : ";
int  connfd[10] = {0},i=0;

void *writeIn(void *arg){
    int fd=*(int*)arg;
    int j;
    while(1){
	    fgets(str,100,stdin);
        if(strncmp(str,out,3)==0){
            close(fd);
            break;
        }
        strcat(name,str);
        strcpy(str,name);
        strcpy(name,"Mr_Robot : ");
        for(j=0;j<i;j++)
            write(connfd[j], str, 100);
    }
    return(NULL);
}

void *readIn(void *arg){
    int fd=*(int*)arg;
    int j;
    while(1){
        read(fd,s, 100);
        for(j=0;j<i;j++)
            write(connfd[j], s, 100);
        if(strncmp(s,out,3)==0){
            close(fd);
            break;
        }
        printf("\t\t\t\t%s", s);
    }
    return(NULL);
}

int main(int argc, char *argv[]){
    int listenfd = 0;
    struct sockaddr_in serv_addr;
	pthread_t thrd[10];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);
	
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	
    listen(listenfd, 10);
	
    while(connfd[i] = accept(listenfd, (struct sockaddr*)NULL, NULL)){
        int pid;
        pthread_create(&thrd[i],NULL,writeIn,&connfd[i]);
        pthread_create(&thrd[i],NULL,readIn,&connfd[i]);
        i++;
    }
    close(connfd[i]);
    sleep(1);
}
