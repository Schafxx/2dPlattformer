#include "Desktop.h"
#include "Tests/Test.cpp"
#include "Figure.h"
#include "livingFigure.h"
#include <unistd.h>

bool debug = false;

bool quit = false;

int main(int argc, char **argv) {
	if (!debug) {
		
		Desktop* desktop = new Desktop();
		usleep(1000*1000);
		////////////////////// Collision Data
		std::vector<Edge> playerColl;
		std::vector<Edge> structureColl;

		////////////////////// Player
		Point p;
		p.x = 100;
		p.y = 100;
		LivingFigure player("aa",p,&playerColl);
		p.x = 300;
		p.y = 200;
		Figure something("aa",p,true,&structureColl);
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
			player.draw();
			
			while (timeAccumulatedMs >= timeStepMs)
	        {
	        	quit = desktop->eventHandler(&player,&playerColl,&structureColl);
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
