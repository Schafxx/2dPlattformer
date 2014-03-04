#include "Figure.h"
#include "util.h"
#include <sstream>

Figure::Figure(std::string name, Point offset, bool collision){
	this->offset.x = offset.x;
	this->offset.y = offset.y;
	std::string path = "Figures/"+name+".obj";
	path = "example";
	std::ifstream file(path.c_str());
	std::string line;
	std::vector<Point> points;
	
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
		}

		///////////////////////////////////


	}else{
		std::cout << "could not load "<<path << std::endl;
	}

}

Figure::~Figure(){

}

void Figure::draw(){
	//std::cout << "triangles size: "<< triangles.size() << std::endl;
	glColor3f(100,0,0);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < triangles.size();i++){
		glVertex3f((triangles[i].points[0].x),(triangles[i].points[0].y),0);
		glVertex3f((triangles[i].points[1].x),(triangles[i].points[1].y),0);
		glVertex3f((triangles[i].points[2].x),(triangles[i].points[2].y),0);
	}
	glEnd();
}

std::vector<Edge> Figure::getCollision(){
	return collision;
}

