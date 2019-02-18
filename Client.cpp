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
        mainMenu();
    }
    close(sockfd);
        return 0;
}

void mainMenu() {
    std::cout << "\n" << std::endl;
    printf("Main Menu!\n");
    printf(" 1. Input Message \n");
    printf(" 2. Exit \n");
    printf("Enter your choice\n");
    scanf("%d",&choice);
    getchar();
        switch(choice) {
            case 1: msg();
                break;
            case 2: std::cout << "Exiting";
                loop = true;
                exit(0);
                break;
            default:
                printf("%s","Invalid choice!\n");
            break;
        }
}
void msg(void)  {
    std::cout << "Press Q to Quit" << std::endl;
    std::cout << " " << std::endl;
     /*ask for a message from the user, this message will be read by server */
    std::cout << "Please enter the message : \n" <<std::endl;
    bzero(buffer,256);
    while(fgets(buffer,255,stdin)) {
        printf("User Input: %s",buffer);
        /* Send message to the server */
            //n = write(sockfd,buffer,strlen(buffer));
            n = write(sockfd,buffer,strlen(buffer)+1);
        if (n < 0)  {
                perror("ERROR writing to socket");
                exit(1);
            }
        /* read server response */
            bzero(buffer,256);
            n = read(sockfd,buffer,256);
