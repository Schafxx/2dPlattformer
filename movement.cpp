#include "movement.h"
#include <iostream>

Movement::Movement(){

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


void Movement::move(){
	for(int i = 0; i < collisionFigures.size();i++){
		Point mtd = util::checkCollision(player->getCollision(), collisionFigures[i]->getCollision(), player->simulateMove(direction));
		direction.x -= mtd.x;
		direction.y -= mtd.y;
	}
	player->move(direction);
	direction.x = 0;
	direction.y = 0;
}