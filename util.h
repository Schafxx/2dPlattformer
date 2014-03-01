#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <iostream>
#include "Figure.h"
#include "livingFigure.h"
#include <cmath>
#include <limits>
class util{
public:
	static void strSplit(std::string src, std::string dst[], char cmp);

	static int strCount(std::string src, char cmp);

	static Point checkCollision(std::vector<Edge> livingEdges, std::vector<Edge> constructEdges, Point livingOffset);
};
#endif