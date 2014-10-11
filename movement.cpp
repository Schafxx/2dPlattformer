#include "movement.h"
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"

#define PI 3.14159265

Movement::Movement(){
	jumpX = 5;
	gravityStrength = 2;
}

Movement::~Movement(){

}

void Movement::changeMap(Map* map){
	this->map = map;
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
	//std::cout << "JUMP" << jumpX << std::endl;;
	if(jumpX == 500 || jumpX == 450){
		jumpX = 0;
	}
}

float Movement::jumpCalc(){
	jumpX += 5;
	direction.y -= gravityStrength;
	
}

void Movement::move(){
	unsigned int dfSize, cfSize, lSize;
	dfSize = map->getDeadlyFiguresSize();
	std::vector<Point> mtdD(dfSize);
	cfSize = map->getCollisionFiguresSize();
	std::vector<Point> mtdC(cfSize);
	lSize = map->getLaddersSize();
	std::vector<Point> mtdL(lSize);

	onladder = onLadder();
	if(jumpX >= 100 && jumpX != 450)
		this->gravity();
	else{
		if(jumpX != 450)
			this->jumpCalc();
	}		


	map->collisionWithCollisionFigures(*player, direction, mtdC);
	falling = true;
	for(unsigned int i = 0; i < cfSize; i++){
		if(mtdC[i].y > 0 && jumpX >= 100){
			jumpX = 500;
			falling = false;
		}
		direction.x -= mtdC[i].x;
		direction.y -= mtdC[i].y;
	}
	if(falling && jumpX >= 100 && !onladder)
		jumpX = 400;


	map->collisionWithDeadlyFigures(*player, direction, mtdD);
	for(unsigned int i = 0; i < dfSize;i++){
		if(mtdD[i].x != 0 && mtdD[i].y != 0){
			std::cout << "DEATH";
		}
	}

	player->move(direction);
	direction.x = 0;
	direction.y = 0;

}


bool Movement::onLadder(){
	unsigned int lSize;
	lSize = map->getLaddersSize();
	std::vector<Point> mtd(lSize);
	map->collisionWithLadders(*player, direction, mtd);
	for(int i = 0; i < lSize; i++){
		if(mtd[i].x != 0 || mtd[i].y != 0){
			if(jumpX >= PI/2)
				jumpX = 4.5;
			return true;
		}
	}
	return false;
}

bool Movement::addPlayer(LivingFigure *player){
	this->player = player;
	map->setPlayer(player);
}

void Movement::renderPlayer(){
	this->player->draw();
}

void Movement::getPlayer(LivingFigure *p){
	p = this->player;
}