
/* Author: Aastha Agrawal
 * Simple Server
 */

#include <stdio.h>
#include <errno.h>
#include<netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#define MY_PORT		9999
#define MAXBUF		1024

int main(int Count, char *Strings[])
{    
     int sockfd;
	struct sockaddr_in addr;
	char buffer[MAXBUF];

     /* Create the socket. The three arguments are:*/
      /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
     if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

     /* Configure settings of the server address struct */
	
     /* Address family = Internet */
	addr.sin_family = AF_INET;
     /* Set port number, using htons function to use proper byte order */
	addr.sin_port = htons(MY_PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

     /* Bind the address struct to the socket*/
     if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr))!=0)
     {
		perror("socket--bind");
		exit(errno);
     }

	/* Listen on the socket, with 20 max connection requests queued*/
	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}
	else
	{
		printf("Listening\n");
	}
	
	 
	int clientfd;
	struct sockaddr_in client_addr;
	int addrlen=sizeof(client_addr);

	/*accept a connection (creating a data pipe)*/
	clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
	printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	bzero(&buffer, sizeof(buffer));
	strcpy(buffer,"Hello world\n"); 
	send(clientfd, buffer, 13, 0); //Here 13 is the size of message sent to client


	/*close socket*/
	close(sockfd);
	return 0;
}

