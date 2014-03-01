#include "util.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

void util::strSplit(std::string src, std::string dst[], char cmp){
	int dstCount = 0;
	for(int i = 0; i < src.size(); i++){
		if(src[i] ==  cmp){
			dstCount++;
		}else{
			dst[dstCount] += src[i];
		}
	}
}

int util::strCount(std::string src, char cmp){
	int count = 0;
	for(int i = 0; i < src.size(); i++){
		if(src[i] == cmp){
			count++;
		}
	}
	return count;
}

Point util::checkCollision(std::vector<Edge> livingEdges, std::vector<Edge> constructEdges, Point livingOffset){
	std::vector<Point> mtd;
	std::vector<Edge> edges = livingEdges;
	for(int i = 0; i < constructEdges.size(); i++){
		edges.push_back(constructEdges[i]);
	}
	for(int livingI = 0; livingI < edges.size(); livingI++){
		
		
		float livingNormX = edges[livingI].p1.x - edges[livingI].p2.x;
		float livingNormY = edges[livingI].p1.y - edges[livingI].p2.y;
		float tmpX = 1.0f/(sqrt(livingNormX*livingNormX+livingNormY*livingNormY));
		//float tmpX;
		livingNormX = tmpX * livingNormX;
		livingNormY = tmpX * livingNormY;
		tmpX = livingNormX;
		livingNormX = livingNormY;
		livingNormY = -1.0f * tmpX;

		/////////NORMALEN
		glColor3f(0,100,0);
		glBegin(GL_LINES);
		glVertex3f(100,100,0);
		glVertex3f(100+livingNormX*100,100+livingNormY*100,0);
		glEnd();

		//std::cout << tmpX << " " << livingNormX<<std::endl;
		float livingMin = 10000000;
		float livingMax = -1000000;
		float constructMin = 10000000;
		float constructMax = -1000000;
		for(int i = 0; i < livingEdges.size(); i++){
			float tmp = (livingEdges[i].p1.x+livingOffset.x)*livingNormX+(livingEdges[i].p1.y+livingOffset.y)*livingNormY;
			//std::cout << tmp <<" livingTMP"<< std::endl;
			if(tmp < livingMin)
				livingMin = tmp;
			if(tmp > livingMax)
				livingMax = tmp;
			//std::cout << livingEdges[i].p1.x+livingOffset.x<<" "<<livingEdges[i].p1.y+livingOffset.y<<std::endl;
		}
		//std::cout << "BLAH"<<std::endl;
		for(int i = 0; i < constructEdges.size(); i++){
			float tmp = constructEdges[i].p1.x*livingNormX+constructEdges[i].p1.y*livingNormY;
			//std::cout << tmp <<" constructTMP"<< std::endl;
			if(tmp < constructMin)
				constructMin = tmp;
			if(tmp > constructMax)
				constructMax = tmp;
			//std::cout << constructEdges[i].p1.x<<" "<<constructEdges[i].p1.y<<std::endl;
		}
		/////PROJEKTION LIVING
		glColor3f(0,0,100);
		glBegin(GL_LINES);
		glVertex3f(livingMin,105+livingI*5,0);
		glVertex3f(livingMax,105+livingI*5,0);
		glEnd();

		/////PROJEKTION CONSTRUCT
		glColor3f(0,100,100);
		glBegin(GL_LINES);
		glVertex3f(constructMin+100,120+livingI*5,0);
		glVertex3f(constructMax+100,120+livingI*5,0);
		glEnd();
		/*
		float offset = (livingEdges[livingI].p1.x - livingEdges[livingI].p2.x)*livingNormX + (livingEdges[livingI].p1.y - livingEdges[livingI].p2.y)*livingNormY;
		livingMin += offset;
		livingMax += offset;
		float d1 = livingMin-constructMax;
		float d2 = constructMin-livingMax;
		if(d1 > 0 || d2 >0){
			Point mtdE;
			mtdE.x = 0;
			mtdE.y = 0;
			return mtdE;
		}else{
			livingNormX *= 
		}*/
		//std::cout << constructMin << " " << constructMax << " || " << livingMin<<" "<<livingMax<<std::endl;
		//std::cout << std::endl;
		
		if(!((livingMin < constructMax && livingMin >= constructMin) || (livingMax > constructMin && livingMax < constructMax)||
			 (constructMin < livingMax && constructMin >= livingMin) || (constructMax > livingMin && constructMax < livingMax))){
			Point mtdE;
			mtdE.x = 0;
			mtdE.y = 0;
			return mtdE;
		}else{
			
			float min = 1000000.0f;
			if(livingMin <= constructMax && livingMin >= constructMin){
				min = (livingMin-constructMax);
				if(std::abs(livingMin-constructMin) < std::abs(min))
					min = (livingMin-constructMin);
			}
			if(livingMax >= constructMin && livingMax <= constructMax){
				if(std::abs(livingMax-constructMin) < std::abs(min))
					min = (livingMax-constructMin);
				if(std::abs(livingMax-constructMax) < std::abs(min))
					min = (livingMax-constructMax);
			}
			if(constructMin <= livingMax && constructMin >= livingMin){
				if(std::abs(constructMin-livingMax) < std::abs(min))
					min = (constructMin-livingMax);
				if(std::abs(constructMin-livingMin) < std::abs(min))
					min = (constructMin-livingMin);
			}
			if(constructMax >= livingMin && constructMax <= livingMax){
				if(std::abs(constructMax-livingMin) < std::abs(min))
					min = (constructMax-livingMin);
				if(std::abs(constructMax-livingMax) < std::abs(min))
					min = (constructMax-livingMax);
			}

			livingNormX *= min;
			livingNormY *= min;	
			
			
			Point mtdE;
			mtdE.x = livingNormX;
			mtdE.y = livingNormY;
			mtd.push_back(mtdE);
		}
	}
	float min = 10000000000.0f;
	Point pMin;
	for(int i = 0; i < mtd.size(); i++){
		//std::cout << mtd[i].x << " |||||MMM||||| "<<mtd[i].y<<" ||| "<<mtd[i].x*mtd[i].x+mtd[i].y*mtd[i].y<<std::endl;
		if(mtd[i].x*mtd[i].x+mtd[i].y*mtd[i].y < min){
			min = mtd[i].x*mtd[i].x+mtd[i].y*mtd[i].y;
			pMin = mtd[i];
		}
	}
	glColor3f(100,0,0);
	//pMin.x *= 2;
	//pMin.y *= 2;
	//std::cout << pMin.x << " ||||||||||| "<<pMin.y<<std::endl;
	return pMin;
}
