#ifndef LIVING_H_
#define LIVING_H_
#include "Figure.h"

class LivingFigure : public Figure{
public:
	LivingFigure(std::string name, Point offset);
	virtual ~LivingFigure();
	void move(Point direction);
	void draw();
	Point simulateMove(Point direction);
private:
	
};

#endif 