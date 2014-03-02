#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <vector>
#include "livingFigure.h"
#include "util.h"

class Movement{
public:
	Movement();
	virtual ~Movement();
	bool addPlayer(LivingFigure *player);
	bool addCollisionFigure(Figure *figure);
	void left();
	void right();
	void move();
	void up();
	void down();
private:
	LivingFigure *player;
	std::vector<Figure*> collisionFigures;
	Point direction;

};

#endif