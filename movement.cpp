#include "movement.h"
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"

#define PI 3.14159265

Movement::Movement(){
	jumpX = 5;
	falling = true;
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
	if(jumpX == 5){
		jumpX = 0;
	}
}

float Movement::jumpCalc(){
	jumpX += PI/20;
	direction.y -= sin(jumpX)*10;
	
}

void Movement::move(){
	if(jumpX >= PI/2)
		this->down();
	else
		this->jumpCalc();
	falling = true;
	for(int i = 0; i < collisionFigures.size();i++){
		Point mtd = util::checkCollision(player->getCollision(), collisionFigures[i]->getCollision(), player->simulateMove(direction));
		if(mtd.y > 0 && jumpX >= PI/2){
			jumpX = 5;
			falling = false;
		}
		direction.x -= mtd.x;
		direction.y -= mtd.y;
	}
	if(falling && jumpX >= PI/2)
		jumpX = 4;
	
	player->move(direction);
	direction.x = 0;
	direction.y = 0;
}