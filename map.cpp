#include "map.h"
#include "util.h"
#include <iostream>

Map::Map(bool ignoreInvisibility){
	renderFigures = new std::vector<Figure*>();
	deadlyFigures = new std::vector<Figure*>();
	ladders = new std::vector<Figure*>();
	collisionFigures = new std::vector<Figure*>();
	this->ignoreInvisibility = ignoreInvisibility;
	//std::cout << renderFigures->size() <<std::endl;
	
}


Map::~Map(){
	delete renderFigures;
	delete deadlyFigures;
	delete ladders;
	delete collisionFigures;
}


void Map::addCollisionFigure(Figure* figure){
	this->collisionFigures->push_back(figure);
}

void Map::addDeadlyFigure(Figure* figure){
	this->deadlyFigures->push_back(figure);
}

void Map::addRenderFigure(Figure* figure){
	this->renderFigures->push_back(figure);
}

void Map::addLadder(Figure* figure){
	this->ladders->push_back(figure);
}

unsigned int Map::getCollisionFiguresSize(){
	return collisionFigures->size();
}

unsigned int Map::getLaddersSize(){
	return ladders->size();	
}

unsigned int Map::getDeadlyFiguresSize(){
	return deadlyFigures->size();
}

unsigned int Map::getRenderFiguresSize(){
	return renderFigures->size();
}

void Map::render(){
	for(int i = 0; i < renderFigures->size(); i++){
		(*this->renderFigures)[i]->draw(ignoreInvisibility);
	}
}

void Map::collisionWithCollisionFigures(LivingFigure &player,Point direction, std::vector<Point> &mtd){
	for(int i = 0; i < collisionFigures->size();i++){
		Point v = util::checkCollision(player.getCollision(), (*collisionFigures)[i]->getCollision(), player.simulateMove(direction),(*collisionFigures)[i]->getOffset());
		mtd[i].x = v.x;
		mtd[i].y = v.y;
		direction.x -= v.x;
		direction.y -= v.y;
		
	}
}

void Map::collisionWithLadders(LivingFigure &player,Point direction, std::vector<Point> &mtd){
	for(int i = 0; i < ladders->size();i++){
		Point v = util::checkCollision(player.getCollision(), (*ladders)[i]->getCollision(), player.simulateMove(direction),(*ladders)[i]->getOffset());
		mtd[i].x = v.x;
		mtd[i].y = v.y;
		direction.x -= v.x;
		direction.y -= v.y;
	}
}

void Map::collisionWithDeadlyFigures(LivingFigure &player,Point direction, std::vector<Point> &mtd){
	for(int i = 0; i < deadlyFigures->size();i++){
		Point v = util::checkCollision(player.getCollision(), (*deadlyFigures)[i]->getCollision(), player.simulateMove(direction),(*renderFigures)[i]->getOffset());
		mtd[i].x = v.x;
		mtd[i].y = v.y;
		direction.x -= v.x;
		direction.y -= v.y;
	}
}

void Map::collisionWithRenderFigures(LivingFigure &player,Point direction, std::vector<Point> &mtd){
	for(int i = 0; i < renderFigures->size();i++){
		Point v = util::checkCollision(player.getCollision(), (*renderFigures)[i]->getCollision(), player.simulateMove(direction),(*renderFigures)[i]->getOffset());
		mtd[i].x = v.x;
		mtd[i].y = v.y;
		direction.x -= v.x;
		direction.y -= v.y;
	}
}

void Map::moveCollisionFigureAtPosition(unsigned int pos, Point direction){
	(*collisionFigures)[pos]->move(direction);
}

void Map::scaleCollisionFigureAtPosition(unsigned int pos, float d){
	(*collisionFigures)[pos]->scale(d);
}

void Map::moveLadderAtPosition(unsigned int pos, Point direction){
	(*ladders)[pos]->move(direction);
}

void Map::scaleLadderAtPosition(unsigned int pos, float d){
	(*ladders)[pos]->scale(d);
}

void Map::moveDeadlyFigureAtPosition(unsigned int pos, Point direction){
	(*deadlyFigures)[pos]->move(direction);
}

void Map::scaleDeadlyFigureAtPosition(unsigned int pos, float d){
	(*deadlyFigures)[pos]->scale(d);
}

void Map::moveRenderFigureAtPosition(unsigned int pos, Point direction){
	(*renderFigures)[pos]->move(direction);
}

void Map::scaleRenderFigureAtPosition(unsigned int pos, float d){
	(*renderFigures)[pos]->scale(d);
}

bool Map::saveToFile(std::string filename){
	std::ofstream file;
	file.open(filename.c_str());
	if(!file.is_open())
		return false;
	file << "#render name x y type scale\n";
	//std::cout << std::endl << "size: " <<renderFigures->size() << std::endl;
	for(unsigned int i = 0; i < renderFigures->size(); i++){
	//	std::cout << (int)(*renderFigures)[i]->getType() <<std::endl;
		file << (*renderFigures)[i]->getName() <<" "<<(*renderFigures)[i]->getOffset().x<<" "<<(*renderFigures)[i]->getOffset().y << " " << (int)(*renderFigures)[i]->getType()<<" " ;
		file << (*renderFigures)[i]->getScale() << "\n";
	}
	file.close();
	return true;
}

Map::Map(std::string filename){
	renderFigures = new std::vector<Figure*>();
	deadlyFigures = new std::vector<Figure*>();
	ladders = new std::vector<Figure*>();
	collisionFigures = new std::vector<Figure*>();
	std::ifstream file;
	file.open(filename.c_str());
	if(file.is_open()){

	}else{
		std::cout << "was not able to open file \"" <<filename <<"\""<<std::endl;
	}
}

void Map::addFigure(unsigned char type, float x, float y, std::string name){
	unsigned char copyType = type;
	bool visible, collision;
	if(type%2) visible = false;
	else visible = true;
	type /= 2;
	if(type%2) collision = false;
	else collision = true;
	type /= 2;
	Point p;
	p.x = x;
	p.y = y;
	Figure* f = new Figure(name, p, collision, visible, copyType);
	renderFigures->push_back(f);
	if(collision) collisionFigures->push_back(f);
	if(type%2) ladders->push_back(f);
	type /= 2;
	if(type%2) deadlyFigures->push_back(f);


}
	
