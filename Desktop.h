
#ifndef DESKTOP_H_
#define DESKTOP_H_

#include "livingFigure.h"
#include "movement.h"
#include <string>
#include "map.h"

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

private:
	void init(int x, int y, char* mode);
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
	bool pressedButtons[263] = {false};
		
};

#endif /* DESKTOP_H_ */
