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
