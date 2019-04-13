#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include<pthread.h>

char str[100];
char recvBuff[1024];
char out[4]="bye";
char name[100],temp[100];
int sockfd = 0;
void *writeIn(void *arg){
	char *name=(char*)arg;
    strcpy(temp,name);
    while(1){
	    fgets(str,100,stdin);
        if(strncmp(str,out,3)==0){
            strcat(str,temp);
            write(sockfd, &str, 100);
            close(sockfd);
            exit(0);
        }     
        strcat(temp,str);
        strcpy(str,temp);
        strcpy(temp,name);
        write(sockfd, &str, 100);
        
    }
    return(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t thrd1;
    int n = 0;
    int temp;
    struct sockaddr_in serv_addr; 
	char s[100];
    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server> <UserName>\n",argv[0]);
        return 1;
    } 
	strcpy(name,argv[2]);
    strcat(name," : ");

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
	
    memset(&serv_addr, '0', sizeof(serv_addr)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
	printf("Server address used is: %s\n", argv[1]);
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
	
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		printf("\n Error : Connect Failed \n");
		return 1;
    } 

    pthread_create(&thrd1,NULL,writeIn,name);
    while(1){
        read(sockfd, s, 100);
        printf("\t\t\t%s",s);
    }
    close(sockfd);
    return 0;
}
