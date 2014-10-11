#include "Desktop.h"
#include "Tests/Test.cpp"
#include "Figure.h"
#include "livingFigure.h"
#include <unistd.h>
#include "movement.h"
#include <vector>
#include <string>
#include "util.h"
#include "map.h"

typedef std::string string;

bool debug = false;

bool quit = false;

int main(int argc, char **argv) {
	/*
	for(unsigned int i = 0; i < 100000000; i++){
		printf("Taste %s gerückt\n", SDL_GetKeyName(i));
	}
	*/
	
	if(argc > 1){
		string s(argv[1]);
		string edit = "edit";
		if(s.compare("edit")==0){
			SDL_Delay(1000);
			Desktop* desktop = new Desktop(800,600,"edit");
			Map* map = new Map(true);
			Point p;
			p.x = 0;
			p.y = 0;
			LivingFigure mouse("mouse",p);
			desktop->addMouse(&mouse);
			desktop->changeMap(map);

			/////////////////////// Timing
			float timeStepMs = 1000.0f / 100.0f;
			float timeCurrentMs;
			float timeDeltaMs;
			float timeAccumulatedMs;
			float timeLastMs;
			////////////////////////
			while (!quit) {
				timeLastMs = timeCurrentMs;
		        
				desktop->render();
				quit = desktop->eventHandler();
				timeCurrentMs = SDL_GetTicks();
	        	
				if((timeCurrentMs - timeLastMs) < timeStepMs){ 
					SDL_Delay(timeStepMs - (timeCurrentMs - timeLastMs));	//add sleep 10ms?
				}
		        desktop->swap();
		        desktop->clearBuffer();
			    
			}

			return 0;
		}
	}
	if (!debug) {
		Movement* movementHandler = new Movement();
		Map* map = new Map(false);
		movementHandler->changeMap(map);
		Desktop* desktop = new Desktop(800,600,"game", movementHandler);
		//SDL_Delay(1000);
		////////////////////// Collision Data
		////////////////////// Player
		Point p;
		p.x = 300;
		p.y = 0;
		LivingFigure player("example",p);
		movementHandler->addPlayer(&player);
		p.x = 300;
		p.y = 200;
		//Figure something("example",p,true, true,0);
		p.x = 100;
		p.y = 300;
		//Figure ladder("example", p, true, true,0);
		
		p.x = 400;
		p.y = 200;
		//Figure deadly("example",p, true, true,0);
		//map->addDeadlyFigure(&deadly);
		//map->addCollisionFigure(&something);
		//map->addLadder(&ladder);
		//map->addRenderFigure(&deadly);
		//map->addRenderFigure(&something);
		//map->addRenderFigure(&ladder);
		///////////////////////
		/////////////////////// Timing
		float timeStepMs = 20;
		float timeCurrentMs;
		float timeLastMs;
		////////////////////////
		desktop->changeMap(map);
		//map->spawnPlayer(true);
		while (!quit) {
			timeLastMs = timeCurrentMs;
	    
			desktop->render();
			
			quit = desktop->eventHandler(); 
	        timeCurrentMs = SDL_GetTicks();
	        if((timeCurrentMs - timeLastMs) < timeStepMs){ 
				SDL_Delay(timeStepMs - (timeCurrentMs - timeLastMs));	//add sleep 10ms?
			}
			desktop->swap();
	        desktop->clearBuffer();
		}
	
	}else{
		Test* t = new Test();
	}
	return 0;
}