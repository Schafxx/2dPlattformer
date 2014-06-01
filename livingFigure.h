#ifndef LIVING_H_
#define LIVING_H_
#include "Figure.h"

class LivingFigure : public Figure {
public:
	LivingFigure(std::string name, Point offset);
	virtual ~LivingFigure();
	void draw();
	Point simulateMove(Point direction);
	void setPosition(Point p);
private:
	
};

#endif 