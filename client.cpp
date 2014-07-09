#include "client.h"

client::client(char* ip, std::string name){
	this->name = name;

	clientSocket = socket(PF_INET, SOCK_STREAM,0);
	if(clientSocket < 0)
		std::cout << "Connection Error: " << std::strerror(errno) << std::endl;
	
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_port = htons(11000);
	this->serverAddr.sin_addr.s_addr = inet_addr(ip);

	if(connect(clientSocket, (struct sockaddr*) &serverAddr,0) < 0)
		std::cout << "Connection Error: " << std::strerror(errno) << std::endl;
	
}

void client::sendText(std::string text){
	char data[120];
	container tmp;
	strncpy(tmp.body, text.c_str(), 100);
	strncpy(tmp.senderName,this->name.c_str(),10);
	strncpy(tmp.tag,"0000000000",10);
	serializeText(&tmp, data);
	if(send(clientSocket,data,120,0) != 120)
		std::cout << "Connection Error: " << std::strerror(errno) << std::endl;
}

void client::serializeText(container* input, char* output){
	for(unsigned int i = 0; i < 120; i++){
		if(i < 10)
			output[i] = input->senderName[i];
		else if(i < 20)
			output[i] = input->tag[i-10];
		else 
			output[i] = input->body[i-20];
	}
}

client::~client(){

}