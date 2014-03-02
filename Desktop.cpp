
#include "Desktop.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <iostream>
#include "util.h"



Desktop::Desktop() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Fehler: %s \n", SDL_GetError());
	}

	window = SDL_CreateWindow("", 0, 0, 800, 600,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!window)
		std::cout << "Failed to create window"<<std::endl;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	
	glcontext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 800, 600, 0, -1, 1);

}

bool Desktop::eventHandler(LivingFigure *player, std::vector<Edge> *playerEdges, std::vector<Edge> *constructEdges) {
	SDL_Event event;
//	SDL_PumpEvents();
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		SDL_Quit();
		return true;
		break;
	case SDL_KEYDOWN:
		keyPressed = event.key.keysym.sym;
		//printf("Taste %s gerückt\n", SDL_GetKeyName(keyPressed));
		switch (keyPressed) {
		case SDLK_q:
			printf("Fenster geschlossen mit <q>\n");
			SDL_Quit();
			return true;
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


	Point p;
	p.x = 0;
	p.y = 0;
	if(direction[0])
		p.y -= 1;
	if(direction[1])
		p.x -= 1;
	if(direction[2])
		p.y += 1;
	if(direction[3])
		p.x += 1;
	Point mtd = util::checkCollision(*playerEdges, *constructEdges, player->simulateMove(p)); 
	p.x -= mtd.x;
	p.y -= mtd.y;
	player->move(p);

	


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
	SDL_DestroyWindow(window);
}

