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
