#include "movement.h"
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"

#define PI 3.14159265

Movement::Movement(){
	jumpX = 5;
	gravityStrength = 1;
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
	if(onladder)
		direction.y -= 1;
}

void Movement::down(){
	if(onladder)
		direction.y += 1;
}

void Movement::gravity(){
	direction.y += gravityStrength;
}

void Movement::jump(){
	std::cout << "JUMP" << jumpX << std::endl;;
	if(jumpX == 5 || jumpX == 4.5){
		jumpX = 0;
	}
}

float Movement::jumpCalc(){
	jumpX += PI/20;
	direction.y -= sin(jumpX)*10;
	
}

void Movement::move(){
	onladder = onLadder();
	if(jumpX >= PI/2 && jumpX != 4.5)
		this->gravity();
	else{
		if(jumpX != 4.5)
			this->jumpCalc();
	}
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
	if(falling && jumpX >= PI/2 && !onladder)
		jumpX = 4;
	
	player->move(direction);
	direction.x = 0;
	direction.y = 0;
}

bool Movement::addLadder(Figure* ladder){
	ladders.push_back(ladder);
	return true;
}

bool Movement::onLadder(){
	for(int i = 0; i < ladders.size(); i++){
		Point p = util::checkCollision(player->getCollision(), ladders[i]->getCollision(), player->simulateMove(direction));
		if(p.x != 0 || p.y != 0){
			if(jumpX >= PI/2)
				jumpX = 4.5;
			return true;
		}
	}
	return false;
}