#include "livingFigure.h"

LivingFigure::LivingFigure(std::string name, Point offset)  : Figure( name, offset, true){
	/*
	for(int i = 0; i < triangles.size(); i++){
		triangles[i].points[0].x-=this->offset.x;triangles[i].points[0].y-=this->offset.y;
		triangles[i].points[1].x-=this->offset.x;triangles[i].points[1].y-=this->offset.y;
		triangles[i].points[2].x-=this->offset.x;triangles[i].points[2].y-=this->offset.y;
	}
	*/
	for(int i = 0; i < collision.size(); i++){
		this->collision[i].p1.x-=this->offset.x;
		this->collision[i].p2.x-=this->offset.x;
		this->collision[i].p1.y-=this->offset.y;
		this->collision[i].p2.y-=this->offset.y;
	}
	
}

LivingFigure::~LivingFigure(){

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

void LivingFigure::setPosition(Point p){
	this->offset.x = p.x;
	this->offset.y = p.y;
}