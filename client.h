#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <errno.h>
#include <cstdlib>
#include <cstring>

struct container{
	char senderName[10];
	char tag[10];
	char body[100];
};

class Client{
public:
	Client(const char* ip, std::string name);
	~Client();
	void sendText(std::string text);
	void recvText(container* message);
private:
	void serializeText(container* input, char* output);
	void deserializeText(char* input, container* output);
	std::string name;
	int clientSocket, serverSocket;
	struct sockaddr_in serverAddr;
	struct hostent *server;
};


#endif