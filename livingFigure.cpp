#include "livingFigure.h"

LivingFigure::LivingFigure(std::string name, Point offset, std::vector<Edge> *collisionEdges)  : Figure( name, offset, true, collisionEdges){
	for(int i = 0; i < triangles.size(); i++){
		triangles[i].points[0].x-=this->offset.x;triangles[i].points[0].y-=this->offset.y;
		triangles[i].points[1].x-=this->offset.x;triangles[i].points[1].y-=this->offset.y;
		triangles[i].points[2].x-=this->offset.x;triangles[i].points[2].y-=this->offset.y;
	}

	for(int i = 0; i < triangles.size(); i++){
		triangles[i].points[0].x*=1.5f;
		triangles[i].points[1].x*=1.5f;
		triangles[i].points[2].x*=1.5f;
	}

	for(int i = 0; i < collisionEdges->size(); i++){
		(*collisionEdges)[i].p1.x-=this->offset.x;
		(*collisionEdges)[i].p2.x-=this->offset.x;
		(*collisionEdges)[i].p1.y-=this->offset.y;
		(*collisionEdges)[i].p2.y-=this->offset.y;
	}

	for(int i = 0; i < collisionEdges->size(); i++){
		(*collisionEdges)[i].p1.x*=1.5f;
		(*collisionEdges)[i].p2.x*=1.5f;
	}
}

LivingFigure::~LivingFigure(){

}

void LivingFigure::move(Point direction){
	this->offset.x += direction.x;
	this->offset.y += direction.y;
}

Point LivingFigure::simulateMove(Point direction){
	Point p;
	p.x = this->offset.x + direction.x;
	p.y = this->offset.y + direction.y;
	return p;
}

void LivingFigure::draw(){
	//std::cout << "triangles size: "<< triangles.size() << std::endl;
	glColor3f(100,0,0);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < triangles.size();i++){
		glVertex3f((triangles[i].points[0].x+this->offset.x),(triangles[i].points[0].y+this->offset.y),0);
		glVertex3f((triangles[i].points[1].x+this->offset.x),(triangles[i].points[1].y+this->offset.y),0);
		glVertex3f((triangles[i].points[2].x+this->offset.x),(triangles[i].points[2].y+this->offset.y),0);
	}
	glEnd();
}
