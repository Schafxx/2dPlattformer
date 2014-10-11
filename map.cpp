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
	setPlayerSpawn(300.0f,0.0f); //REMOVE
	
}


Map::~Map(){
	delete renderFigures;
	delete deadlyFigures;
	delete ladders;
	delete collisionFigures;
	//delete player;
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
	std::ofstream file(filename.c_str());
	if(!file.is_open())
		return false;
	file << "#render name x y type scale\n";
	//std::cout << std::endl << "size: " <<renderFigures->size() << std::endl;
	for(unsigned int i = 0; i < renderFigures->size(); i++){
	//	std::cout << (int)(*renderFigures)[i]->getType() <<std::endl;
		file << (*renderFigures)[i]->getName() <<" "<<(*renderFigures)[i]->getOffset().x<<" "<<(*renderFigures)[i]->getOffset().y << " " << (int)(*renderFigures)[i]->getType()<<" " ;
		file << (*renderFigures)[i]->getScale() << "\n";
	}
	file << "X " << playerSpawnX << "\n";
	file << "Y " << playerSpawnY << "\n";
	file.flush();
	file.close();
	return true;
}

Map::Map(std::string filename){
	load(filename);
}

void Map::addFigure(unsigned char type, float x, float y, std::string name){
	unsigned char copyType = type;
	bool visible, collision;
	if(type%2) 
		visible = false;
	else 
		visible = true;
	type /= 2;
	if(type%2) 
		collision = false;
	else 
		collision = true;
	type /= 2;
	Point p;
	p.x = x;
	p.y = y;
	Figure* f = new Figure(name, p, collision, visible, copyType);
	renderFigures->push_back(f);
	if(type%2){
		ladders->push_back(f);
		collision = false;
	}
	type /= 2;
	if(type%2) 
		deadlyFigures->push_back(f);
	if(collision) collisionFigures->push_back(f);
	

}

void Map::setPlayer(LivingFigure* player){
	this->player = player;
}

void Map::setPlayerSpawn(float x, float y){
	playerSpawnX = x;
	playerSpawnY = y;
}

void Map::renderPlayer(){
	if(playerSpawned)
		this->player->draw();
}

void Map::spawnPlayer(bool b){
	playerSpawned = b;
	Point p;
	p.x = playerSpawnX;
	p.y = playerSpawnY;
	if(player != NULL)
		player->setPosition(p);
}

void Map::load(std::string filename){
	if(renderFigures != NULL)
		delete renderFigures;
	renderFigures = new std::vector<Figure*>();
	if(deadlyFigures != NULL)
		delete deadlyFigures;
	deadlyFigures = new std::vector<Figure*>();
	if(ladders != NULL)
		delete ladders;
	ladders = new std::vector<Figure*>();
	if(collisionFigures != NULL)
		delete collisionFigures;
	collisionFigures = new std::vector<Figure*>();
	
	std::ifstream file;
	std::string line;
	file.open(filename.c_str());
	float x, y;
	if(file.is_open()){
		while(getline(file,line)){
			if(line.size() > 0 && line.substr(0,1).compare("#") != 0){
				std::string lineParts[5];
			
				util::strSplit(line, lineParts, ' ');

				if(lineParts[0] == "X"){
					x = atof(lineParts[1].c_str());
				}else if(lineParts[0] == "Y"){
					y = atof(lineParts[1].c_str());
				}else{
					addFigure((unsigned char)atoi(lineParts[3].c_str()),atof(lineParts[1].c_str()),atof(lineParts[2].c_str()),lineParts[0].c_str());
					scaleRenderFigureAtPosition(getRenderFiguresSize()-1,1.0f-atof(lineParts[4].c_str()));
				}
			}
		}
		setPlayerSpawn(x,y);	
	}else{
		std::cout << "was not able to open file \"" <<filename <<"\""<<std::endl;
	}
}