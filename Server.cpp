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
