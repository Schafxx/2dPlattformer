#include "movement.h"
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"

#define PI 3.14159265

Movement::Movement(){
	jumpX = PI;
	lastJumpEnded = 0;
}

Movement::~Movement(){

}

bool Movement::addPlayer(LivingFigure* player){
	this->player = player;
}

bool Movement::addCollisionFigure(Figure* figure){
	this->collisionFigures.push_back(figure);
}

void Movement::left(){
	direction.x -= 1;
}

void Movement::right(){
	direction.x += 1;
}

void Movement::up(){
	direction.y -= 1;
}

void Movement::down(){
	direction.y += 1;
}

void Movement::jump(){
	if(jumpX >= PI/2 && SDL_GetTicks() -lastJumpEnded > 1000){
		jumpX = 0;
	}
}

float Movement::jumpCalc(){
	jumpX += PI/20;
	direction.y -= sin(jumpX)*10;
	if(jumpX >= PI/2)
		lastJumpEnded = SDL_GetTicks();
}

void Movement::move(){
	if(jumpX>=PI/2)
		this->down();
	else
		this->jumpCalc();
	for(int i = 0; i < collisionFigures.size();i++){
		Point mtd = util::checkCollision(player->getCollision(), collisionFigures[i]->getCollision(), player->simulateMove(direction));
		direction.x -= mtd.x;
		direction.y -= mtd.y;
	}
	player->move(direction);
	direction.x = 0;
	direction.y = 0;
}