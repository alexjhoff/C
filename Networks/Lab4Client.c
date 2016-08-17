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

	char *str[] = {"packet one", "packet two", "packet three", "packet four", "packet five", NULL};

	struct hostent*server_addr = gethostbyname(argv[1]); //get host addr
	struct sockaddr_in si_server;

	//initialize packet structure
	typedef struct packet{
		unsigned int sequence;
		char buffer[200];
		unsigned int checksum;
	}PACKET;
	
	PACKET packet;
	packet.sequence = 0;
	packet.checksum = 15;

	int sockfd = socket(PF_INET, SOCK_DGRAM, 0); 		//get socket return address
	bzero((char*)&si_server,sizeof(si_server));		//write zeros to socket address structure fields
        si_server.sin_family = AF_INET;				//specify IPv4
        bcopy((char*) server_addr -> h_addr, (char*)&si_server.sin_addr, server_addr -> h_length); //copy server address to socket address address field
        si_server.sin_port = htons(50000);			//assign the port number
	socklen_t len = sizeof(si_server);

	while(1){
		strcpy(packet.buffer,str[packet.sequence]);		
	
		int in = sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr*)&si_server, sizeof(si_server)); //send to server

		if(strncmp(packet.buffer,"quit",4)==0)
			break;

		recvfrom(sockfd, &packet, sizeof(packet), 0, (struct sockaddr*)&si_server, &len); //recieve from server
		if(packet.checksum!=15){		//check if checksum is correct
			printf("Data corrupted");
			packet.sequence--;
		}

		if(strncmp(packet.buffer,"quit",4)==0)
			break;
		//print out message
		printf("Uppercase %s\n", packet.buffer);
		printf("Checksum = %d, is correct. Lenght of string %d, Message:%s\n", packet.checksum, strlen(packet.buffer), packet.buffer);
		if(packet.sequence > 4){
			printf("All packets have been sent\n");
			break;
		}
	}
	close(sockfd);

	return 0;	
}
