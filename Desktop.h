
#ifndef DESKTOP_H_
#define DESKTOP_H_

#include "livingFigure.h"


class Desktop {
public:
	Desktop();
	virtual ~Desktop();
	bool eventHandler(LivingFigure *player,std::vector<Edge> *playerEdges, std::vector<Edge> *constructEdges);
	void drawSomething();
	void swap();
	void clearBuffer();
	void clearDirection();
private:
	bool direction[4] = {false,false,false,false};
};

#endif /* DESKTOP_H_ */
