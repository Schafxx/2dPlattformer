#include "Chat.h"

#define KEY(x) matchKeyCodesToInt[x]

Chat::Chat(float x, float y, std::string name){
	this->name = name;
	this->x = x;
	this->y = y;
	stringToAdd = new std::string();
}

Chat::~Chat(){
	for(unsigned int i = 0; i < text.size(); i++){
		delete text[i];
	}
	delete stringToAdd;
	if(isConnected)
		delete client;
}

void Chat::render(){
	int startY = 100;
	glColor3f(1.0f,1.0f,1.0f);
	for(int i = text.size()-1; i >= 0; i--){
		glRasterPos2f(10.0f,startY);
		for(unsigned int iStr = 0; iStr < text[i]->length(); iStr++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]->c_str()[iStr]);
			
		}
		startY -= 15;

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

bool Chat::isActive(){
	return active;
}

void Chat::activate(){
	if(stringToAdd->size() > 1){
		if(this->active){
			char c[1] = {stringToAdd->front()};
			if(stringToAdd->substr(1) == "/"){
				text.push_back(stringToAdd);
				if(isConnected)
					client->sendText(*stringToAdd);
			}else{
				if(stringToAdd->find("connect ") != std::string::npos){
					stringToAdd->erase(0,9); //9 == length of "/connect "
					std::cout << *stringToAdd << std::endl;
					connect(stringToAdd->c_str());
				}
			}
		}


		stringToAdd = new std::string();
	}
	this->active = !this->active;
}

void Chat::connect(const char* ip){
	if(isConnected)
		delete client;
	client = new Client(ip, this->name);
}