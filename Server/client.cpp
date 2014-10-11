#include <iostream>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

#include <cstdlib>
#include <stdio.h>

struct container
{
	char senderName[10];
	char tag[10];
	char body[100];
};


void getName(char* name)
{
	std::cout << "Hi, type in your name: ";
	std::cin >> name;
	fflush(stdin);
	printf("RAW: ");
	for(int i = 0; i <sizeof(name);i++)
	{
		printf("%x|",name[i]);
	}
	printf("\n");
}

void getMessage(char* message)
{
	std::cout << "Message: ";
	std::cin >> message;
	fflush(stdin);
	printf("RAW: ");
	for(int i = 0; i <sizeof(message);i++)
	{
		printf("%x|",message[i]);
	}
	printf("\n");
}

/*void serializeContainer(container * input, char * output)
{
	for(unsigned int i = 0; i < 120; i++)
	{
		if(i < 10)
			output[i] = input->senderName[i];
		else if(i < 20)
			output[i] = input->tag[i-10];
		else
			output[i] = input->body[i-20];
	}
}*/
void serializeContainer(struct container * input, char * output)
{
	for(unsigned int i = 0; i < 120; i++)
	{
		if(i < 10)
			output[i] = input->senderName[i];
		else if(i < 20)
			output[i] = input->tag[i-10];
		else
			output[i] = input->body[i-20];
	}
}
void deserializeContainer(char * input, container* output)
{
	for(unsigned int i = 0; i < 120;i++)
	{
		if(i < 10)
			output->senderName[i] = input[i];
		else if( i < 20)
			output->tag[i-10] = input[i];
		else
			output->body[i-20] = input[i];
	}
}

int main()
{
	// basic variables
	int clientSock, servSock;
	struct sockaddr_in servAddr;

	struct hostent *server;

	// create socket
	if((clientSock=socket(PF_INET,SOCK_STREAM,0))<0)
		std::cout << "Error: " << strerror(errno) << std::endl;
	else
		std::cout << "Socket created" << std::endl;

	// establish connection
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(11000);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(clientSock, (struct sockaddr*) &servAddr,sizeof(servAddr))<0)
		std::cout << "Error: " << strerror(errno) << std::endl;
	else
		std::cout << "connected." << std::endl;

	char server_reply[2000];
	char name[10];
	char body[100];
	container message;

	//Receive a reply from the server
	if( recv(clientSock , server_reply , 120 , 0) < 0)
	{
		puts("recv failed");
	}
	else
	{
		printf("Server reply(%d bytes) :\n",strlen(server_reply));
		//char contin[strlen(server_reply)];
		printf("RAW: ");
		for(int i = 0; i <strlen(server_reply);i++)
		{
			printf("%x|",server_reply[i]);
		}
		printf("\n");
	
		container reply;
		deserializeContainer(server_reply,&reply);
		printf("From: %s, Message: %s\n",reply.senderName, reply.body);
	}

	getName(name);

	fflush(stdin);
	// looop for input
	while(1)
	{
		

		getMessage(body);
		fflush(stdin);
		if(strcmp(body, "q")==0)
			break;

		strncpy(message.senderName, name ,10);
		strncpy(message.tag,"0000000000",10);
		strncpy(message.body, body ,100);

		char data[120];
		serializeContainer(&message,data);

		// the send routine
		if(send(clientSock,data,120,0) != sizeof(data))
			std::cout << "Error: " << strerror(errno) << std::endl;
		else
			std::cout << "Name: " << message.senderName << "Body: " << message.body << std::endl;
		if( recv(clientSock , server_reply , 120 , 0) < 0)
		{
			puts("recv failed");
		}
		else
		{
			printf("Server reply(%d bytes) :\n",strlen(server_reply));
			//char contin[strlen(server_reply)];
			printf("RAW: ");
			for(int i = 0; i <strlen(server_reply);i++)
			{
				printf("%x|",server_reply[i]);
			}
			printf("\n");
		
			container reply;
			deserializeContainer(server_reply,&reply);
			printf("From: %s, Message: %s\n",reply.senderName, reply.body);
		}
	}

	// close socket
	if(close(servSock) < 0)
		std::cout << "Failure on closing Socket\n" << std::endl;
	else
		std::cout << "Socket closed\n" << std::endl;

	return 1;
}