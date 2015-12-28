#pragma once
#include <stdio.h>
#include <string.h>
#include "define.h"
#include "Globals.h"
#include "Object.h"
#include <Time.h>
#include "../Utilities/math.h"
#include "../Utilities/utilities.h" 

class AnimSprite: public Object
{
public:
	unsigned long startTime;
	static AnimSprite *s_instance;
	static AnimSprite *getInstance();
	int** animationList;
	int currentAmination;
	int numberAnimations;
	float frameTime;
	int* currentIndexFrame;//frame which is being used
	int* numberFrames;//number of frame of each animation
	AnimSprite();
	void loadFile(char* file, char* path);
	void setCurrentFrame(int animationID, int currentFrameID);
	void Update(int animationID);
	void Render();
	Texture* getTexture(int animationID);
	Texture* getTexture(int animationID, int frameID);
	~AnimSprite();
};
#define AnimationInstance() AnimSprite::getInstance()
