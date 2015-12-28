#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Texture.h"
#include "Globals.h"
class Animation{
public:
	int m_ID;
	Texture **m_frame;
	int numOfFrame;
	
	Animation(void){
		numOfFrame=0;
		m_frame=NULL;
	}
	~Animation(){
		delete m_frame;
	}
};
#endif