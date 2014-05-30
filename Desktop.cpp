#include "Desktop.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <iostream>
#include "util.h"
#include "movement.h"
#include <string>

typedef std::string string;



Desktop::Desktop(int x, int y, char* mode, Movement *movement) {
	this->movement = movement;
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
	window = SDL_CreateWindow("", 0, 0, x, y,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!window)
		std::cout << "Failed to create window"<<std::endl;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	
	glcontext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 800, 600, 0, -1, 1);

}

void Desktop::setMovement(Movement* movement){
	this->movement = movement;
}

bool Desktop::eventHandler() {
	SDL_Event event;
//	SDL_PumpEvents();
	SDL_PollEvent(&event);
	int mouseX;
	int mouseY;
	Uint8 mouse = SDL_GetMouseState(&mouseX, &mouseY);
	if(mode == 0){

		switch (event.type) {

		case SDL_QUIT:
			return true;
			break;
		case SDL_KEYDOWN:
			keyPressed = event.key.keysym.sym;
			//printf("Taste %s gerückt\n", SDL_GetKeyName(keyPressed));
			switch (keyPressed) {
			case SDLK_q:
				printf("Fenster geschlossen mit <q>\n");
				return true;
			case SDLK_SPACE:
				movement->jump();
				break;
			case SDLK_l:
				break;
			case SDLK_w:
				direction[0] = true;
				break;
			case SDLK_a:
				direction[1] = true;
				break;
			case SDLK_s:
				direction[2] = true;			
				break;
			case SDLK_d:
				direction[3] = true;			
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym){
			case SDLK_w:
				direction[0] = false;
				break;
			case SDLK_a:
				direction[1] = false;
				break;
			case SDLK_s:
				direction[2] = false;				
				break;
			case SDLK_d:
				direction[3] = false;			
				break;
			default:
				break;	
			}

			break;
		default:
			break;
		}

		if(direction[0])
			movement->up();
		if(direction[2])
			movement->down();
			

		if(direction[1])
			movement->left();
		if(direction[3])
			movement->right();
		
		movement->move();

		return false;
	}
	if(mode == 1){
		Point p;
		p.x = (float)mouseX-100;
		p.y = (float)mouseY-100;
		bool y = false;
		switch (event.type) {

		case SDL_QUIT:
			return true;
			break;
		case SDL_KEYDOWN:
			keyPressed = event.key.keysym.sym;
			//printf("Taste %s gerückt\n", SDL_GetKeyName(keyPressed));
			switch (keyPressed) {
			case SDLK_q:
				printf("Fenster geschlossen mit <q>\n");
				return true;
			case SDLK_SPACE:
				break;
			case SDLK_l:
				break;
			case SDLK_w:
				y = true;
				break;
			case SDLK_a:
				break;
			case SDLK_s:
				break;
			case SDLK_d:
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym){
			case SDLK_w:
				break;
			case SDLK_a:
				break;
			case SDLK_s:
				break;
			case SDLK_d:
				break;
			default:
				break;	
			}

			break;
		default:
			break;
		}		
		if(y){
			Figure* f = new Figure("aa",p,true);
			map->addRenderFigure(f);			
		}
	}
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
	SDL_Quit();
	SDL_DestroyWindow(window);
}

void Desktop::changeMap(Map *map){
	this->map = map;
}

void Desktop::render(){
	this->map->render();
	if(mode == 0)
		this->movement->renderPlayer();
}

void Desktop::addMouse(LivingFigure *mouse){
	this->mouse = mouse;
}

