#include "Desktop.h"
#include "Tests/Test.cpp"
#include "Figure.h"
#include "livingFigure.h"
#include <unistd.h>
#include "movement.h"

bool debug = false;

bool quit = false;

int main(int argc, char **argv) {
	if (!debug) {
		
		Desktop* desktop = new Desktop();
		SDL_Delay(1000);
		Movement* movementHandler = new Movement();
		////////////////////// Collision Data

		////////////////////// Player
		Point p;
		p.x = 300;
		p.y = 0;
		LivingFigure player("aa",p);
		p.x = 300;
		p.y = 200;
		Figure something("aa",p,true);
		p.x = 100;
		p.y = 300;
		Figure ladder("aa", p, true);
		movementHandler->addPlayer(&player);
		movementHandler->addCollisionFigure(&something);
		movementHandler->addLadder(&ladder);
		///////////////////////
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
			something.draw();
			ladder.draw();
			player.draw();
			
			while (timeAccumulatedMs >= timeStepMs)
	        {
	        	quit = desktop->eventHandler(movementHandler);
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
