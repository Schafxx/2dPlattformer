
#ifndef DESKTOP_H_
#define DESKTOP_H_

#include "livingFigure.h"
#include "movement.h"
#include <string>
#include "map.h"
#include <unordered_map>
#include "Chat.h"

typedef std::string string;

class Desktop {
public:
	Desktop(int x, int y, char* mode, Movement *movement);
	Desktop(int x, int y, char* mode);
	virtual ~Desktop();
	bool eventHandler();
	void drawSomething();
	void swap();
	void clearBuffer();
	void clearDirection();
	void setMovement(Movement *movement);
	void render();
	void changeMap(Map *map);
	void addMouse(LivingFigure *Mouse);
	

	//void addTextToPrint(std::string *text);

private:
	void executeChatCommands();
	void init(int x, int y, char* mode);
	//void printText();
	Map* map;
	int mode;
	SDL_Window* window;
	Movement* movement;
	SDL_GLContext glcontext;
	SDL_Keycode keyPressed;
	bool direction[4] = {false,false,false,false};
	LivingFigure* mouse; 
	std::vector<Point>* renderFiguremtd;
	bool mouseButtonPushed[2] = {false,false};
	bool pressedButtons[133] = {false};
	bool lastPressedButtons[133] = {false};
	bool everPressedButtons[133] = {false};
	Chat* chatWindow;

	//std::vector<std::string*> text;
	//bool chatInputActive = false;

	std::vector<int> keyCodes; 
	std::unordered_map<int,int> matchKeyCodesToInt;
};

#endif /* DESKTOP_H_ */
