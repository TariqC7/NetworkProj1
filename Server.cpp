#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

void doProcessing(int sock) {
    int n;
    char buffer[255];
    bzero(buffer,256);
    n =read(sock,buffer,255);
    
    if(n < 0) {
        perror("Error from reading socket");
        exit(1);
    }
    
    if(n > 0) {
        printf("Here is the msg: %s\n",buffer);
        n=write(sock,"I got your msg",18);
    }
    
    if(n<0) {
        perror("Error writing to socket");
        exit(1);
    }
}
    
int main( int argc, char *argv[] )
{
    int sockfd,pid,newsockfd,portno,clientn;
    struct sockaddr_in serv_addr,cli_addr;
    char buffer[256];
    bool connected;
    int n;
    socklen_t len;
    /*call socket() function*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
    perror("Error opening socket");
    exit(1);
    }
    
    /*Initialize socket structure*/
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    /*bind the host address using bind() call*/
    if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
    perror("Error on binding!");
    exit(1);
    }
    int yes =1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes, sizeof(yes)) == -1) {
    perror("setsockopt");
    exit(1);
    }
    
    /*start listening for clients, will go into sleep mode and wait for incoming connection*/
    listen(sockfd,5);
    len = sizeof(cli_addr);
     while(connected == false) {
        newsockfd = accept(sockfd,(struct sockaddr*)&cli_addr,&len);
         if(newsockfd < 0) {
            perror("Error on accept!");
            exit(1);
            }
         /*Create chlid process*/
        pid =fork();
        if(pid < 0)
        {
            perror("Error on fork!");
            exit(1);
        }
        if(pid == 0)
        {
            /*Client process*/
            close(sockfd);
            doPrcoessing(newsockfd);
            return 0;
        }
        else
        {
            close(newsockfd);
        }
    }
    return 0;
