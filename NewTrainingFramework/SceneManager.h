
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__


#include "../Utilities/utilities.h"
#include <stdio.h>
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"

class SceneManager{
public:
	unsigned char keyevent;
	int numOfObject, numOfCamera;
	int camera_active;
	Object *m_object;
	Camera **m_camera;
	
	static SceneManager *s_Instance;
	static SceneManager* getInstance();
	void Render();
	void Update(float deltaTime);

	SceneManager();
	~SceneManager();
	int Init(char* file);
	Camera* getCamera();
	void setKeyevent(unsigned char key, bool bIsPressed);

};
#define GetSMInstance() SceneManager::getInstance()
#endif
