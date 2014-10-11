#include "Chat.h"

#define KEY(x) matchKeyCodesToInt[x]

Chat::Chat(float x, float y, std::string name){
	this->name = name;
	this->x = x;
	this->y = y;
	stringToAdd = new std::string();
	commands = new std::vector<std::string>();
}

Chat::~Chat(){
	for(unsigned int i = 0; i < text.size(); i++){
		delete text[i];
	}
	delete stringToAdd;
	if(isConnected)
		delete client;
	delete commands;
}

std::string Chat::getCommand(){
	std::string ret = "";
	if(commands->size() > 0){
		ret = commands->back();
		commands->pop_back();
	}
	return ret;
}

void Chat::render(){
	int startY = y;
	glColor3f(1.0f,1.0f,1.0f);
	for(int i = text.size()-1; i >= 0; i--){
		glRasterPos2f(x,startY);
		for(unsigned int iStr = 0; iStr < text[i]->length(); iStr++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]->c_str()[iStr]);
			
		}
		startY -= 15;
		if(startY < 0)
			break;

	}
	glRasterPos2f(10.0f, 120.0f);
	for(unsigned int i = 0; i < stringToAdd->length(); i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, (*stringToAdd)[i]);	
	}

}

void Chat::addText(SDL_Event* event){
	switch(event->type){
	case SDL_TEXTINPUT:
		stringToAdd->append(event->text.text);
		break;
	default:
		break;
	}	
}

void Chat::addText(std::string *text){
	this->text.push_back(text);
}

bool Chat::isActive(){
	return active;
}

void Chat::activate(){
	if(stringToAdd->size() > 1){
		if(this->active){
			if(stringToAdd->substr(0,1).compare("/") != 0){
				text.push_back(stringToAdd);
				if(isConnected)
					client->sendText(*stringToAdd);
			}else{
				if(stringToAdd->find("connect ") != std::string::npos){
					stringToAdd->erase(0,9); //9 == length of "/connect "
					std::cout << *stringToAdd << std::endl;
					connect(stringToAdd->c_str());
					std::cout << "connected"<<std::endl;
				}
				if(stringToAdd->find("load ") != std::string::npos){
					commands->push_back(stringToAdd->substr(0));
					std::cout << *stringToAdd << std::endl;
				}
				if(stringToAdd->find("save ") != std::string::npos){
					commands->push_back(stringToAdd->substr(0));
					std::cout << *stringToAdd << std::endl;
				}
			}
		}


		stringToAdd = new std::string();
	}
	this->active = !this->active;
}

void Chat::connect(const char* ip){
	client = new Client(ip, this->name);
}