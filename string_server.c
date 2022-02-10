#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
int main(int argc, char **argv)
{
    int i, j, l, sockfd, clilen, newsockfd, n;
    char buf[4096], buf1[4096] = "i got your message\0";
    struct sockaddr_in servaddr, cliaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9888);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct aockaddr *)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);
    clilen = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
    n = read(newsockfd, buf, 4000);
    printf("\n\nreceived from client:%s\n", buf);
    l = strlen(buf);
    for (i = l - 1, j = 0; j < strlen(buf1); i++, j++)
        buf[i] = buf1[j];
    buf[i] = '\0';
    write(newsockfd, buf, strlen(buf));
    close(newsockfd);
}
