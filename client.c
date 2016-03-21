/* Author: Aastha Agrawal
 * This is a simple client socket reader.  It opens a socket, connects to a server, reads the message, and closes.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include<netinet/in.h>


#define SERVER_ADDR     "127.0.0.1"     /* localhost */
#define MAXBUF          1024

int main()
{   int sockfd;
    struct sockaddr_in dest;
    char buffer[MAXBUF];

    /* Create the socket. The three arguments are: */
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("Socket");
        exit(errno);
    }

   /* Configure settings of the server address struct */
    
    /* Address family = Internet */
    dest.sin_family = AF_INET;

    /* Set port number, using htons function to use proper byte order */
    dest.sin_port = htons(9999);
    if ( inet_aton(SERVER_ADDR, &dest.sin_addr.s_addr) == 0 )
    {
        perror(SERVER_ADDR);
        exit(errno);
    }

    /* Connect to server */
    if ( connect(sockfd, (struct sockaddr*)&dest, sizeof(dest))!=0)
    {
        perror("Connect ");
        exit(errno);
    }
        
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Data received:%s\n", buffer);

    /*Close socket*/
    close(sockfd);
    return 0;
}


