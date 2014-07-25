#ifndef CHAT_H
#define CHAT_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <iostream>
#include <string>
#include <GL/glut.h>
#include <vector>
#include <unordered_map>
#include "client.h"

class Chat{
public:
	Chat(float x, float y, std::string name);
	~Chat();
	void addText(SDL_Event *event);
	void render();
	bool isActive();
	void activate();


private:
	void connect(char* ip);
	std::string name;
	float x,y;
	std::string *stringToAdd;
	std::vector<std::string*> text;
	bool active = false;
	Client* client;
	bool isConnected = false;


};


#endif
