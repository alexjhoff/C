#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char* argv[])
{

	const serverPort = 50000;

	struct sockaddr_in si_server; //init sock addr
	
	//initialize packet structure
	typedef struct packet{
		unsigned int sequence;
		char buffer[200];
		unsigned int checksum;
	}PACKET;
	
	PACKET packet;
	packet.sequence = 0;
	packet.checksum = 15;
	
	bzero((char*)&si_server, sizeof(si_server)); 	//write zeros to socket address structure fields
	si_server.sin_family = AF_INET;			//specify IPv4
	si_server.sin_addr.s_addr=INADDR_ANY;		//allow use of any interface
	si_server.sin_port = htons(serverPort);		//assign the server port number

	int sockfd = socket(PF_INET, SOCK_DGRAM, 0); 	//get the socket address
	
	bind(sockfd, (struct sockaddr*)&si_server, sizeof(si_server)); //assign the socket address to the server address

	socklen_t len = sizeof(si_server);

	while(1){
		int n = recvfrom(sockfd, &packet, sizeof(packet), 0, (struct sockaddr *)&si_server, &len); //recv from client
		
		if(packet.checksum!=15){		//check if checksum isnt correct
			printf("Checksum corrupted\n");
			break;
		}
		else{					//if it is
			packet.sequence++;
			
			int i;
			for(i=0; i<strlen(packet.buffer); i++){			//change characters to uppercase
				packet.buffer[i] = toupper(packet.buffer[i]);
			}
			printf("Checksum = %d. Lenght of message %d, Message:%s\n", packet.checksum, strlen(packet.buffer), packet.buffer); //print message
		}

		if(strncmp(packet.buffer,"quit",4)==0)
			break;

		if(packet.checksum!=15){
			printf("Checksum does not match");
			packet.sequence--;
		}
		
		sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr *)&si_server, sizeof(si_server)); //send packet back to client

		if(packet.sequence > 4){
			printf("All packets have been sent\n");
			break;
		}
	}

	close(sockfd); 	//close connection

	return 0;
}

