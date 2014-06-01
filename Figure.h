#ifndef FIGURE_H_
#define FIGURE_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

struct Point{
	float x;
	float y;
};

struct Triangle{
	Point points[3];
};

struct Edge{
	Point p1;
	Point p2;
};

class Figure{
public:
	Figure(std::string name, Point offset, bool collision);
	virtual ~Figure();
	void draw();
	void move(Point direction);
	std::vector<Edge> getCollision();
protected:
	Point offset;
	std::vector<Triangle> triangles;
	std::vector<Edge> collision;
};

#endif 