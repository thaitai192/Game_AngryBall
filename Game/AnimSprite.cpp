#include "AnimSprite.h"
#include <Time.h>
#include "log.h"

AnimSprite *AnimSprite::s_instance= NULL;

AnimSprite *AnimSprite::getInstance()
{
	if(!s_instance)
	{
		s_instance= new AnimSprite();
	}
	return s_instance;
}

AnimSprite::AnimSprite():frameTime(0.042), currentAmination(0),numberAnimations(0)
{
	currentIndexFrame=NULL;
	numberFrames= NULL;
	startTime= 0;
}

void AnimSprite::loadFile(char* file, char* path)
{
	FILE *pfile= fopen(file,"r");
	if(!pfile)
	{
		perror("error: ");
	}
	else
	{
		//Reading the display time of each frame by ms
		fscanf(pfile,"Seconds Per Frame %f\n\n",&frameTime);
		//Reading source of images(save the name of image/texture file)
		fscanf(pfile,"IMAGES %d\n",&numOfTexture);
		m_texture_list= new Texture*[numOfTexture];
		for(int i=0;i<numOfTexture;i++)
		{
			char imageName[255];
			fscanf(pfile,"ID %*d\n");
			fscanf(pfile,"FILE %s\n",&imageName);
			char link[100];
			sprintf(link, "%s%s", path, imageName);
			m_texture_list[i]= new Texture();
			m_texture_list[i]->Init(link);
		}
		fscanf(pfile,"\n");
		
		//Reading list of texture for each animation
		fscanf(pfile,"ANIMATIONS %d\n",&numberAnimations);
		if(numberAnimations>0)
		{
			animationList= new int*[numberAnimations];
			numberFrames= new int[numberAnimations];
			currentIndexFrame= new int[numberAnimations];

			for(int i=0;i<numberAnimations;i++)
			{
				fscanf(pfile,"ID %*d\n");
				fscanf(pfile,"NAME %*s\n");
				fscanf(pfile,"FRAMES %d\n",&numberFrames[i]);
				animationList[i]= new int[numberFrames[i]];
				currentIndexFrame[i]=0;
				for(int j =0;j<numberFrames[i];j++)
				{
					fscanf(pfile,"%d\n",&animationList[i][j]);
				}
			}
		}
	}
	fclose(pfile);
	LOGI("Load AniSprite is success!");
}

void AnimSprite::setCurrentFrame(int animationID,int currentFrameID)
{
	currentAmination= animationID;
	currentIndexFrame[currentAmination]= currentFrameID;
}
Texture * AnimSprite::getTexture(int animationID)
{
	int textureID= animationList[animationID] [ currentIndexFrame[animationID]];
	return m_texture_list[textureID];
}

void AnimSprite::Update(int animationID)
{
	if(clock()-startTime>=frameTime)
	{
		if(currentIndexFrame[animationID] < numberFrames[animationID]-1)
			currentIndexFrame[animationID]++;
		else currentIndexFrame[animationID]=0;
		startTime= clock();
	}
	//Sleep(frameTime);
}

Texture * AnimSprite::getTexture(int animationID, int frameID)
{
	int location= animationList[animationID][frameID];
	currentIndexFrame[animationID]= frameID;
	return m_texture_list[location];
}

AnimSprite::~AnimSprite()
{
	for(int i=0;i<numberAnimations;i++)
	{
		delete[] animationList[i];
	}
	for(int i=0;i<numOfTexture;i++)delete m_texture_list[i];
	delete[]currentIndexFrame;
	delete[]numberFrames;
	delete[] animationList;
}