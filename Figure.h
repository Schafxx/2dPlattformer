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
	Figure(std::string name, Point offset, bool collision, bool visible, unsigned char type);
	virtual ~Figure();
	void draw(bool );
	void move(Point direction);
	std::vector<Edge> getCollision();
	Point getOffset();
	std::string getName();
	void scale(float d);
	float getScale();
	unsigned char getType();
protected:
	unsigned char type;
	bool visible;
	Point offset;
	std::string name;
	std::vector<Triangle> triangles;
	std::vector<Edge> collision;
	float scaleFactor;
};

#endif 