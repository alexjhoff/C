#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char* argv[])
{

	char recvArray[200];
	const serverPort = 50000;

	struct sockaddr_in si_server; //init sock addr
	
	bzero((char*)&si_server, sizeof(si_server)); //bind
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0); //init socket

	si_server.sin_family = AF_INET;
	si_server.sin_addr.s_addr=INADDR_ANY;
	si_server.sin_port = htons(serverPort);
	
	bind(sockfd, (struct sockaddr*)&si_server, sizeof(si_server));

	socklen_t len = sizeof(si_server);

	while(1){
		int n = recvfrom(sockfd, recvArray, 200, 0, (struct sockaddr *)&si_server, &len); //recv from client
		if(strncmp(recvArray, "quit", 4)==0)
			break;
		printf("%s\n", recvArray);
		fgets(recvArray, 200, stdin);
		if(strncmp(recvArray, "quit", 4)==0)
			break;
		sendto(sockfd, recvArray, 200, 0, (struct sockaddr *)&si_server, sizeof(si_server));
	}

	close(sockfd);

	return 0;
}

