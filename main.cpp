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
#include <thread>
#include <mutex>
#include <queue>

std::mutex eventMutex;

typedef std::string string;

bool debug = false;

bool quit = false;

int inputLoop(std::queue<SDL_Event*>* inputQueue, std::mutex* eventMutex){


	SDL_Event event;
	std::queue<SDL_Event*> wait;
	while(1){
		while(SDL_WaitEvent(&event)){
			SDL_Event* copy = new SDL_Event(event);
			if(eventMutex->try_lock()){ //SUCCESS
				while(wait.size() > 0){
					inputQueue->push(wait.front());
					wait.pop();
				}
				inputQueue->push(copy);
				eventMutex->unlock();
			}else{
				wait.push(copy);
			}
		}
	}
}

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

			std::queue<SDL_Event*> inputQueue;

			std::thread inputThread(inputLoop,&inputQueue, &eventMutex);

			while (!quit) {
				timeLastMs = timeCurrentMs;
		        
				desktop->render();
				quit = desktop->eventHandler(&eventMutex, &inputQueue);
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
		
		std::queue<SDL_Event*> inputQueue;

		std::thread inputThread(inputLoop,&inputQueue,&eventMutex);


		while (!quit) {
			timeLastMs = timeCurrentMs;
	    
			desktop->render();
			
			quit = desktop->eventHandler(&eventMutex, &inputQueue); 
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