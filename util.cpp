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
	Point mtd;
	float minMul = 100000000;
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
		
		if(!((livingMin < constructMax && livingMin > constructMin) || (livingMax > constructMin && livingMax < constructMax)||
			 (constructMin < livingMax && constructMin > livingMin) || (constructMax > livingMin && constructMax < livingMax) 
			 || (livingMin == constructMin && livingMax == constructMax))){
			Point mtdE;
			mtdE.x = 0;
			mtdE.y = 0;
			return mtdE;
		}else{
			
			float min = 1000000.0f;
			if(livingMin < constructMax && livingMin > constructMin){
				if(std::abs(livingMin-constructMax) < std::abs(min) && std::abs(livingMin-constructMax) != 0)
					min = (livingMin-constructMax);
				/*if(std::abs(livingMin-constructMin) < std::abs(min)&& std::abs(livingMin-constructMin) != 0)
					min = (livingMin-constructMin);*/
			}
			if(livingMax > constructMin && livingMax < constructMax){
				if(std::abs(livingMax-constructMin) < std::abs(min)&& std::abs(livingMax-constructMin) != 0)
					min = (livingMax-constructMin);
				/*if(std::abs(livingMax-constructMax) < std::abs(min)&& std::abs(livingMax-constructMax) != 0)
					min = (livingMax-constructMax);*/
			}
			if(constructMin < livingMax && constructMin > livingMin){
				if(std::abs(constructMin-livingMax) < std::abs(min)&& std::abs(livingMax-constructMin) != 0)
					min = (constructMin-livingMax);
				/*if(std::abs(constructMin-livingMin) < std::abs(min)&& std::abs(livingMin-constructMin) != 0)
					min = (constructMin-livingMin);*/
			}
			if(constructMax > livingMin && constructMax < livingMax){
				if(std::abs(constructMax-livingMin) < std::abs(min)&& std::abs(livingMin-constructMax) != 0)
					min = (constructMax-livingMin);
				/*
				if(std::abs(constructMax-livingMax) < std::abs(min)&& std::abs(livingMax-constructMax) != 0)
					min = (constructMax-livingMax);*/
			}
			//std::cout << min << std::endl;
			if(std::abs(min) < std::abs(minMul)){
				minMul = min;	
				mtd.x = livingNormX;
				mtd.y = livingNormY;
			}
			
		}
	}
	
	mtd.x *= minMul;
	mtd.y *= minMul;
	//mtd.x *= 2;
	//mtd.y *= 2;
	//std::cout << mtd.x << " ||||||||||| "<<mtd.y<<std::endl;
	return mtd;
}
