
#ifndef DESKTOP_H_
#define DESKTOP_H_

#include "livingFigure.h"
#include "movement.h"


class Desktop {
public:
	Desktop();
	virtual ~Desktop();
	bool eventHandler(Movement *movement);
	void drawSomething();
	void swap();
	void clearBuffer();
	void clearDirection();
private:
	SDL_Window* window;
	SDL_GLContext glcontext;
	SDL_Keycode keyPressed;
	bool direction[4] = {false,false,false,false};
};

#endif /* DESKTOP_H_ */
