#include "Figure.h"
#include "util.h"
#include <sstream>

Figure::Figure(std::string name, Point offset, bool collision, bool visible, unsigned char type){
	this->type = type;
	this->visible = visible;
	this->name = name;
	this->offset.x = offset.x;
	this->offset.y = offset.y;
	//std::string path = "Figures/"+name+".obj";
	std::string path = name + ".obj";
	std::ifstream file(path.c_str());
	std::string line;
	std::vector<Point> points;
	scaleFactor = 1.0;
	std::vector<std::vector<int> > planes;


	if(file.is_open()){
		while(getline(file,line)){
			if(line.size() > 0){
				if(line.at(0) == '#' || line.at(0) == 'o'){ 
					continue;	
				}
				if(line.at(0) == 'v'){ //v 1.0 -1.0 -1.0
					const int length = util::strCount(line, ' ') + 1;
					std::string* lineArray = new std::string[length];
					util::strSplit(line, lineArray, ' ');
					float f[2];
					for(int i = 1; i < 3; i++){
						std::stringstream s;
						f;
						s << lineArray[i];
						s >> f[i-1];
					}
					Point p;
					p.x = f[0]+offset.x;
					p.y = f[1]+offset.y;
					points.push_back(p);
					continue;
				}
				if(line.at(0) == 'f'){//f 1 2 3 4
					const int length = util::strCount(line, ' ') + 1;
					std::string* lineArray = new std::string[length];
					util::strSplit(line, lineArray, ' ');
					std::vector<int> tmpPlanes;
					for(int i = 1; i < length; i++){
						int tmp;
						std::stringstream s;
						tmp;
						s << lineArray[i];
						s >> tmp;
						tmpPlanes.push_back(tmp);
					}
					planes.push_back(tmpPlanes);
					continue;
				}
			}
		}
		file.close();
		for(int i1 = 0; i1 < planes.size(); i1++){
			for(int i2 = 0; i2 < planes[i1].size()-2; i2++){
				Triangle t;
				if(i2 != planes[i1].size() -3){
					t.points[0] = points[planes[i1][i2]  -1];
					t.points[1] = points[planes[i1][i2+1]-1];
					t.points[2] = points[planes[i1][i2+2]-1];
				}else{
					t.points[0] = points[planes[i1][0]   -1];
					t.points[1] = points[planes[i1][i2+1]-1];
					t.points[2] = points[planes[i1][i2+2]-1];
				}
				triangles.push_back(t);
			}
		}
		for(int i = 0; i < triangles.size(); i++){
			triangles[i].points[0].x-=this->offset.x;triangles[i].points[0].y-=this->offset.y;
			triangles[i].points[1].x-=this->offset.x;triangles[i].points[1].y-=this->offset.y;
			triangles[i].points[2].x-=this->offset.x;triangles[i].points[2].y-=this->offset.y;
		}

		/////////////////////////////////// collision data

		if(collision){
			for(int i1 = 0; i1 < planes.size(); i1++){
				for(int i2 = 0; i2 < planes[i1].size(); i2++){
					Edge e;
					if(i2 != planes[i1].size()-1){
						e.p1 = points[planes[i1][i2]  -1];
						e.p2 = points[planes[i1][i2+1]-1];
					}else{
						e.p2 = points[planes[i1][0]   -1];
						e.p1 = points[planes[i1][i2]  -1];
					}
					this->collision.push_back(e);

				}
			}
			for(int i = 0; i < this->collision.size(); i++){
				this->collision[i].p1.x-=this->offset.x;
				this->collision[i].p2.x-=this->offset.x;
				this->collision[i].p1.y-=this->offset.y;
				this->collision[i].p2.y-=this->offset.y;
			}
		}

		///////////////////////////////////


	}else{
		std::cout << "could not load "<<path << std::endl;
	}

}

Figure::~Figure(){

}

void Figure::draw(bool ignoreInvisibility){
	//std::cout << "triangles size: "<< triangles.size() << std::endl;
	if(ignoreInvisibility || visible){
		glColor3f(100,0,0);
		glBegin(GL_TRIANGLES);
		for(int i = 0; i < triangles.size();i++){
			glVertex3f((triangles[i].points[0].x+this->offset.x),(triangles[i].points[0].y+this->offset.y),0);
			glVertex3f((triangles[i].points[1].x+this->offset.x),(triangles[i].points[1].y+this->offset.y),0);
			glVertex3f((triangles[i].points[2].x+this->offset.x),(triangles[i].points[2].y+this->offset.y),0);}
		glEnd();
	}
}

std::vector<Edge> Figure::getCollision(){
	return collision;
}

void Figure::move(Point direction){
	this->offset.x += direction.x;
	this->offset.y += direction.y;
}

Point Figure::getOffset(){
	return this->offset;
}

std::string Figure::getName(){
	return this->name;
}

void Figure::scale(float d){
	for(unsigned int i = 0; i < triangles.size(); i++){
		triangles[i].points[0].x *= (d+scaleFactor)/scaleFactor;
		triangles[i].points[1].x *= (d+scaleFactor)/scaleFactor;
		triangles[i].points[2].x *= (d+scaleFactor)/scaleFactor;
		triangles[i].points[0].y *= (d+scaleFactor)/scaleFactor;
		triangles[i].points[1].y *= (d+scaleFactor)/scaleFactor;
		triangles[i].points[2].y *= (d+scaleFactor)/scaleFactor;
	}
	for(unsigned int i = 0; i < collision.size();i++){
		collision[i].p1.x *= (d+scaleFactor)/scaleFactor;
		collision[i].p2.x *= (d+scaleFactor)/scaleFactor;
		collision[i].p1.y *= (d+scaleFactor)/scaleFactor;
		collision[i].p2.y *= (d+scaleFactor)/scaleFactor;
	}
	scaleFactor = scaleFactor+d;
}

float Figure::getScale(){
	return scaleFactor;
}

unsigned char Figure::getType(){
	return type;
}