#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <vector>
#include "Figure.h"
#include "livingFigure.h"
#include "util.h"
#include "map.h"

class Movement{
public:
	Movement();
	virtual ~Movement();
	bool addPlayer(LivingFigure *player);
	void left();
	void right();
	void move();
	void up();
	void down();
	void jump();
	void changeMap(Map*);
	void renderPlayer();
	void getPlayer(LivingFigure *p);
private:
	bool onLadder();
	bool onladder;
	void gravity();
	float jumpCalc();
	float jumpX;
	float lastJumpEnded;
	bool falling;
	float gravityStrength;
	LivingFigure *player;
	Map *map;
	Point direction;

};

#endif