#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdbool.h>
#include <signal.h>
#include <iostream>
#include <sstream>

void msg(void);
void mainMenu();
int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;
bool loop = false;
char options[100];
char buffer[255];
int choice;
char c;

int main(int argc, char *argv[])
{
    while(loop==false) {
        if (argc < 3) {
            fprintf(stderr,"usage %s hostname port\n", argv[0]);
            exit(0);
        }
        portno = atoi(argv[2]);
        /* Create a socket point */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)  {
            perror("ERROR opening socket");
            exit(1);
      }
     server = gethostbyname(argv[1]);
     if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
     }
     bzero((char *)&serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,
                server->h_length);
        serv_addr.sin_port = htons(portno);
        
        /* connect to the server */
        if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
            perror("Error connecting");
            exit(1);
     }
