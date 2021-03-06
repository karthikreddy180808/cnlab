#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define CLI_PORT 4000
#define BUFF_SIZE 80
#define IP "127.0.0.1"
int main(int argc, char **argv)
{
    int clisoc, re;
    char recbuff[BUFF_SIZE];
    struct sockaddr_in cliaddr;
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(CLI_PORT);
    cliaddr.sin_addr.s_addr = inet_addr(IP);
    if ((clisoc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket Errror");
        exit(0);
    }
    if ((connect(clisoc, (struct sockaddr *)&cliaddr, sizeof(cliaddr))) < 0)
    {
        perror("Connect Error");
        exit(0);
    }
    if ((re = (fread(clisoc, recbuff, sizeof(recbuff), 0))) < 0)
    {
        printf("Read Error");
        exit(0);
    }
    printf("The Current Date and Time : %s\n", recbuff);
    close(clisoc);
    return 0;
}
