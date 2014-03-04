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
	bool addLadder(Figure *ladder);
	void left();
	void right();
	void move();
	void up();
	void down();
	void jump();
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
	std::vector<Figure*> collisionFigures;
	std::vector<Figure*> ladders;
	Point direction;

};

#endif