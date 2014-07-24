#include "Chat.h"

#define KEY(x) matchKeyCodesToInt[x]

Chat::Chat(float x, float y){
	stringToAdd = new std::string();
}

Chat::~Chat(){
	for(unsigned int i = 0; i < text.size(); i++){
		delete text[i];
	}
	delete stringToAdd;
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
	if(this->active)
		text.push_back(stringToAdd);
	stringToAdd = new std::string();
		
	this->active = !this->active;
}