#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
	if(argc < 3){
		printf("error not enought arguments\n");
		return 0;
	}

	char sendArray[200];

	struct hostent*server_addr = gethostbyname(argv[1]); //get host addr
	struct sockaddr_in si_server; //create socketa addr
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0); //open socket

	bzero((char*)&si_server,sizeof(si_server));
        si_server.sin_family = AF_INET;
        bcopy((char*) server_addr -> h_addr, (char*)&si_server.sin_addr, server_addr -> h_length);
        si_server.sin_port = htons(50000);

	socklen_t len = sizeof(si_server);

	while(fgets(sendArray, 200, stdin)){
		//check for exit string
		int in = sendto(sockfd, sendArray, 200, 0, (struct sockaddr*)&si_server, sizeof(si_server)); //send to server
		if(strncmp(sendArray,"quit",4)==0)
			break;
		//recive
		recvfrom(sockfd, sendArray, 200, 0, (struct sockaddr*)&si_server, &len);
		if(strncmp(sendArray,"quit",4)==0)
			break;
		printf("%s\n", sendArray);
	}
	close(sockfd);

	return 0;	
}
