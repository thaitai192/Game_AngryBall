#ifndef __GS_WELCOMESCREEN_H__
#define __GS_WELCOMESCREEN_H__

#include "StateManager.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "Text.h"



class GS_WelcomeScreen: public StateBase{
public:
	Vector4 color;
	float timeLoading;
	char m_text[20];

	GS_WelcomeScreen();
	Text loading;
	Object *obj;
	void Create();
	void Render();
	void Update(float deltaTime);
	void Clean();
	void KeyEvent(unsigned char key, bool bIsPressed);
	void MouseEvent(int x, int y, int type);
	~GS_WelcomeScreen();

};

#endif