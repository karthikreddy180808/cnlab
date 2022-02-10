#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
int main(int argc, char **argv)
{
    int sockfd, n;
    char buf[4096];
    struct sockaddr_in cliaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9888);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    connect(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    printf("enter a string\n");
    fgets(buf, 256, stdin);
    write(sockfd, buf, strlen(buf));
    n = read(sockfd, buf, 4000);
    printf("\n\nreceived message from server:%s\n", buf);
    close(sockfd);
}
