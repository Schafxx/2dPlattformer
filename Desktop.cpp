#include "Desktop.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <iostream>
#include "util.h"
#include "movement.h"
#include <string>
#include <GL/glut.h>
#include <stdlib.h>

typedef std::string string;

#define KEY(x) matchKeyCodesToInt[x]


Desktop::Desktop(int x, int y, char* mode, Movement *movementt) {
	this->movement = movementt;
	init(x,y,mode);
}

Desktop::Desktop(int x, int y, char* mode){
	init(x,y,mode);
}

void Desktop::init(int x, int y, char* mode){

	string s(mode);
	if(s.compare("game")==0)
		this->mode = 0;
	if(s.compare("edit")==0)
		this->mode = 1;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Fehler: %s \n", SDL_GetError());
	}
	window = SDL_CreateWindow("A", 0, 0, x, y,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!window){
		std::cout << SDL_GetError() << std::endl;
		std::cout << "Failed to create window"<<std::endl;
		exit(EXIT_SUCCESS);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	
	
	glcontext = SDL_GL_CreateContext(window);
	if(glcontext == NULL){
	    printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	if(SDL_GL_SetSwapInterval(1) < 0 ){
        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 800, 600, 0, -1, 1);
	int argc = 1;
  	char *argv[1] = {(char*)"Something"};
	glutInit(&argc, argv);
	
	int k[] = {SDLK_BACKSPACE, SDLK_TAB, SDLK_CLEAR, SDLK_RETURN, SDLK_PAUSE, SDLK_ESCAPE, SDLK_SPACE, SDLK_EXCLAIM, SDLK_QUOTEDBL, SDLK_HASH, SDLK_DOLLAR, SDLK_AMPERSAND, SDLK_QUOTE, SDLK_LEFTPAREN, SDLK_RIGHTPAREN, SDLK_ASTERISK, SDLK_PLUS, SDLK_COMMA, SDLK_MINUS, SDLK_PERIOD, SDLK_SLASH, SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_COLON, SDLK_SEMICOLON, SDLK_LESS, SDLK_EQUALS, SDLK_GREATER, SDLK_QUESTION, SDLK_AT, SDLK_LEFTBRACKET, SDLK_BACKSLASH, SDLK_RIGHTBRACKET, SDLK_CARET, SDLK_UNDERSCORE, SDLK_BACKQUOTE, SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h, SDLK_i, SDLK_j, SDLK_k, SDLK_l, SDLK_m, SDLK_n, SDLK_o, SDLK_p, SDLK_q, SDLK_r, SDLK_s, SDLK_t, SDLK_v, SDLK_w, SDLK_x, SDLK_y, SDLK_z, SDLK_DELETE, SDLK_KP_PERIOD, SDLK_KP_DIVIDE, SDLK_KP_MULTIPLY, SDLK_KP_MINUS, SDLK_KP_PLUS, SDLK_KP_ENTER, SDLK_KP_EQUALS, SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT, SDLK_INSERT, SDLK_HOME, SDLK_END, SDLK_PAGEUP, SDLK_PAGEDOWN, SDLK_F1, SDLK_F2, SDLK_F3, SDLK_F4, SDLK_F5, SDLK_F6, SDLK_F7, SDLK_F8, SDLK_F9, SDLK_F10, SDLK_F11, SDLK_F12, SDLK_F13, SDLK_F14, SDLK_F15, SDLK_CAPSLOCK, SDLK_RSHIFT, SDLK_LSHIFT, SDLK_RCTRL, SDLK_LCTRL, SDLK_RALT, SDLK_LALT, SDLK_MODE, SDLK_HELP, SDLK_SYSREQ, SDLK_MENU, SDLK_POWER};
	for(unsigned int i = 0; i < sizeof(k)/sizeof(int); i++){
		matchKeyCodesToInt.insert({k[i], i});
	}

	chatWindow = new Chat(0,100, "fuu");
	help = new Chat(700,80,"help");

	if(this->mode == 1){
		std::string* s = new std::string("CTRL: invisible");
		std::string* s1 = new std::string("ALT: no collision");
		std::string* s2 = new std::string("SHIFT: ladder");
		std::string* s3 = new std::string("TAB: deadly");
		help->addText(s);
		help->addText(s1);
		help->addText(s2);
		help->addText(s3);
	}
}

void Desktop::setMovement(Movement* movement){
	this->movement = movement;
}

//void Desktop::addTextToPrint(std::string *text){
//	this->text.push_back(text);
//}
/*
void Desktop::printText(){
	int startY = 100;
	glColor3f(1.0f,1.0f,1.0f);
	for(int i = text.size()-1; i >= 0; i--){
		glRasterPos2f(10.0f,startY);
		//char* tmpText = text[i]->c_str();
		unsigned int l = text[i]->length();
		for(unsigned int iStr = 0; iStr < l; iStr++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]->c_str()[iStr]);
			
		}
		startY -= 15;

	}
}
*/

bool Desktop::eventHandler() {
	this->executeChatCommands();
	SDL_Event event;
//	SDL_PumpEvents();
	int mouseX;
	int mouseY;
	int mouseMovementX;
	int mouseMovementY; 
	Uint8 mouse = SDL_GetMouseState(&mouseX, &mouseY);
	SDL_GetRelativeMouseState(&mouseMovementX, &mouseMovementY);
	Uint8 button;
	Point tp;
	tp.x = mouseX;
	tp.y = mouseY;
	Point p;
	p.x = (float)mouseX-100;
	p.y = (float)mouseY-100;
	Point d;
	d.x = 0;
	d.y = 0;

	/////////////////////////
	//::SDL_WaitEvent(&event);
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button){
				case SDL_BUTTON_LEFT:
					map->collisionWithRenderFigures(*(this->mouse), d, *renderFiguremtd);
					mouseButtonPushed[0] = true;
					break;
				case SDL_BUTTON_RIGHT:
					mouseButtonPushed[1] = true;
					break;
				default:
					break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButtonPushed[0] = mouseButtonPushed[1] = false;
			break;
		case SDL_QUIT:
			break;
		case SDL_KEYDOWN:
			pressedButtons[KEY(event.key.keysym.sym)] = true;
			everPressedButtons[KEY(event.key.keysym.sym)] = true;
			break;
		case SDL_KEYUP:
			pressedButtons[KEY(event.key.keysym.sym)] = false;
			lastPressedButtons[KEY(event.key.keysym.sym)] = true;
			break;
		default:
			break;
		}
		if(chatWindow->isActive()){
			chatWindow->addText(&event);
		}
	}
	if(mode == 1)
		this->mouse->setPosition(tp);
	if(!pressedButtons[KEY(SDLK_RETURN)] && lastPressedButtons[KEY(SDLK_RETURN)]){
		chatWindow->activate();
	}
	if(mode == 0){
		
		if(!chatWindow->isActive()){
			if(pressedButtons[KEY(SDLK_q)]){
				return true;
			}
			if(pressedButtons[KEY(SDLK_w)]){
				movement->up();
			}
			if(pressedButtons[KEY(SDLK_s)]){

				movement->down();
			}
			if(pressedButtons[KEY(SDLK_a)]){
				movement->left();
			}
			if(pressedButtons[KEY(SDLK_d)]){
				movement->right();
			}
			if(pressedButtons[KEY(SDLK_SPACE)]){
				movement->jump();
			}
		}
		movement->move();

		
	}
	if(mode == 1){
		if(pressedButtons[KEY(SDLK_q)]){
			return true;
		}
		if(mouseButtonPushed[0]){
			int c = 0;
			for(unsigned int i = 0; i < map->getRenderFiguresSize(); i++ ){
				if((*renderFiguremtd)[i].x != 0 || (*renderFiguremtd)[i].y != 0){
					//std::cout << c++ << std::endl;
					Point p;
					p.x = mouseMovementX;
					p.y = mouseMovementY;
					map->moveRenderFigureAtPosition(i,p);
					//std::cout << p.x <<" || "<<p.y << std::endl;
				}
			}	
		}

		/////////////////////////////////
		unsigned char type = 0;
		if(pressedButtons[KEY(SDLK_LCTRL)]) type += 1; //invisible
		if(pressedButtons[KEY(SDLK_LALT)]) type += 2; //no collision
		if(pressedButtons[KEY(SDLK_LSHIFT)]) type += 4; //ladder
		if(pressedButtons[KEY(SDLK_TAB)]) type += 8; //deadly
		/////////////////////////////////

		if(pressedButtons[KEY(SDLK_w)]){
			this->map->addFigure(type, p.x, p.y, "example");
			renderFiguremtd->resize(this->map->getRenderFiguresSize());
			pressedButtons[KEY(SDLK_w)] = false;		
		}

		if(pressedButtons[KEY(SDLK_s)]){ //set Spawn
			this->map->setPlayerSpawn(p.x,p.y);
			//TODO: add Visual indicator for spawn point
		}

		/////////////////////////////////
		
		if(pressedButtons[KEY(SDLK_PAGEDOWN)]){
			for(unsigned i = 0; i < map->getRenderFiguresSize(); i++){
				if((*renderFiguremtd)[i].x != 0 || (*renderFiguremtd)[i].y != 0){
					this->map->scaleRenderFigureAtPosition(i, -0.005f);
				}
			}
		}
		if(pressedButtons[KEY(SDLK_PAGEUP)]){
			for(unsigned i = 0; i < map->getRenderFiguresSize(); i++){
				if((*renderFiguremtd)[i].x != 0 || (*renderFiguremtd)[i].y != 0){
					this->map->scaleRenderFigureAtPosition(i, 0.005f);
				}
			}
		}


	}
	for(unsigned int i = 0; i < 133; i++){
		lastPressedButtons[i] = everPressedButtons[i] = pressedButtons[i];
	}
	//std::cout << 1<<std::endl;
	return false;
}



void Desktop::drawSomething() {

	glBegin(GL_TRIANGLES);

	glColor3f(50, 0, 0);
	glVertex3f(400, 100, 0);

	glColor3f(50, 1, 0);
	glVertex3f(750, 500, 0);

	glColor3f(50, 0, 1);
	glVertex3f(50, 500, 0);

	glEnd();

}
void Desktop::swap() {
	SDL_GL_SwapWindow(window);
}

void Desktop::clearDirection(){
	for(int i = 0; i < 4; i++)
		direction[i] = false;
	
}

void Desktop::clearBuffer(){
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

Desktop::~Desktop() {
	delete chatWindow;
	SDL_Quit();
	SDL_DestroyWindow(window);
}

void Desktop::changeMap(Map *map){
	this->map = map;
	renderFiguremtd = new std::vector<Point>;
	
}
void Desktop::render(){
	this->map->render();
	this->chatWindow->render();
	//printText();
	this->help->render();
	if(mode == 0)
		this->map->renderPlayer();
}

void Desktop::addMouse(LivingFigure *mouse){
	this->mouse = mouse;
}

void Desktop::executeChatCommands(){
	std::string commandAndParam;
	commandAndParam = chatWindow->getCommand();
	while(commandAndParam.compare("") != 0){
		std::string command = commandAndParam.substr(1,commandAndParam.find(" "));
		std::string params = commandAndParam.substr(commandAndParam.find(" ")+1);
		if(command.compare("load ")==0){
			this->map->load(params);
			this->map->spawnPlayer(true);
		}else if(command.compare("save ")==0){
			this->map->saveToFile(params);
		}

		commandAndParam = chatWindow->getCommand();
	}
}
