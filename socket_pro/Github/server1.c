/*
 *  server.h
 *  
 *
 *  Created by Ankush Mittal on 01/03/15.
 *  Copyright 2015 IIT. All rights reserved.
 *
 */

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

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 
	char s[100];
    char sendBuff[1025];
	int temp;
    time_t ticks; 
	
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 
	
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	
    listen(listenfd, 10); 
	
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
		
       // ticks = time(NULL);
        //snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, "Hello\n", 6);
		scanf("%d", &temp);
		write(connfd, "Sleep?\n", 7);
		scanf("%d", &temp);
		read(connfd,s, 20); 
		printf("The client said: %s\n", s);
//		write(connfd, sendBuff, strlen(sendBuff)); 
		scanf("%d", &temp);
        close(connfd);
        sleep(1);
	}
}