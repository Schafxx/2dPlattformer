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
	
	if(argc > 1){
		string s(argv[1]);
		string edit = "edit";
		if(s.compare("edit")==0){
			Desktop* desktop = new Desktop(800,600,"edit");
			SDL_Delay(1000);
			Map* map = new Map();
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
		        timeCurrentMs = SDL_GetTicks();
		        timeDeltaMs = timeCurrentMs - timeLastMs;
		        timeAccumulatedMs = timeDeltaMs;
				
				desktop->render();
				while (timeAccumulatedMs >= timeStepMs)
		        {
		        	quit = desktop->eventHandler();
				    timeAccumulatedMs -= timeStepMs;
		        }
		        desktop->swap();
		        desktop->clearBuffer();
			    
			}

			return 0;
		}
	}
	if (!debug) {
		Movement* movementHandler = new Movement();
		Map* map = new Map();
		movementHandler->changeMap(map);
		Desktop* desktop = new Desktop(800,600,"game", movementHandler);
		SDL_Delay(1000);
		////////////////////// Collision Data
		////////////////////// Player
		
		Point p;
		p.x = 300;
		p.y = 0;
		LivingFigure player("example",p);
		movementHandler->addPlayer(&player);
		p.x = 300;
		p.y = 200;
		Figure something("example",p,true);
		p.x = 100;
		p.y = 300;
		Figure ladder("example", p, true);
		
		p.x = 400;
		p.y = 200;
		Figure deadly("example",p, true);
		map->addDeadlyFigure(&deadly);
		map->addCollisionFigure(&something);
		map->addLadder(&ladder);
		map->addRenderFigure(&deadly);
		map->addRenderFigure(&something);
		map->addRenderFigure(&ladder);
		///////////////////////
		/////////////////////// Timing
		float timeStepMs = 1000.0f / 100.0f;
		float timeCurrentMs;
		float timeDeltaMs;
		float timeAccumulatedMs;
		float timeLastMs;
		////////////////////////
		std::string f = "fuu";
		desktop->addTextToPrint(&f);
		desktop->addTextToPrint(&f);
		desktop->changeMap(map);
		while (!quit) {
			timeLastMs = timeCurrentMs;
	        timeCurrentMs = SDL_GetTicks();
	        timeDeltaMs = timeCurrentMs - timeLastMs;
	        timeAccumulatedMs = timeDeltaMs;
			
			desktop->render();
			while (timeAccumulatedMs >= timeStepMs){
	        	quit = desktop->eventHandler();
			    timeAccumulatedMs -= timeStepMs;
	        }
	        desktop->swap();
	        desktop->clearBuffer();
		    
		}
	
	}else{
		Test* t = new Test();
	}
	return 0;
}
