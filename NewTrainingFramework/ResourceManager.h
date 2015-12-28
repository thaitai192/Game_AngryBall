#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include <stdio.h>
//#include "CubeTexture.h"

class ResourceManager{
public:
	int numOfModel;
	int numOfTexture;
	int numOfShader;
	//int numOfCubeTexture;
	Model *m_model;
	Texture *m_texture;
	//CubeTexture *m_cubeTexture;
	Shaders *m_shader;
	ResourceManager();
	static ResourceManager *s_Instance;
	static ResourceManager* getInstance();
	int Init(char *file, char* path);
	~ResourceManager();
};

#define GetRMInstace() ResourceManager::getInstance()

#endif