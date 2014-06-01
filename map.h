
#ifndef MAP_H_
#define MAP_H_

#include "Figure.h"
#include <string>
#include <vector>
#include "livingFigure.h"
typedef std::string string;

class Map {
public:
	Map();
	virtual ~Map();
	void addCollisionFigure(Figure *figure);
	void addLadder(Figure *ladder);
	void addDeadlyFigure(Figure*);
	void addRenderFigure(Figure*);
	unsigned int getCollisionFiguresSize();
	void moveCollisionFigureAtPosition(unsigned int pos, Point direction);
	unsigned int getLaddersSize();
	void moveLadderAtPosition(unsigned int pos, Point direction);
	unsigned int getDeadlyFiguresSize();
	void moveDeadlyFigureAtPosition(unsigned int pos, Point direction);
	unsigned int getRenderFiguresSize();
	void moveRenderFigureAtPosition(unsigned int pos, Point direction);
	void render();
	void collisionWithCollisionFigures(LivingFigure &player,Point direction, std::vector<Point> &mtd);
	void collisionWithLadders(LivingFigure &player,Point direction, std::vector<Point> &mtd);
	void collisionWithDeadlyFigures(LivingFigure &player,Point direction, std::vector<Point> &mtd);
	void collisionWithRenderFigures(LivingFigure &player,Point direction, std::vector<Point> &mtd);
private:
	std::vector<Figure*>* renderFigures;
	std::vector<Figure*>* collisionFigures;
	std::vector<Figure*>* ladders;
	std::vector<Figure*>* deadlyFigures;
	float playerSpawnX;
	float playerSpawnY;
};

#endif /* MAP_H_ */
