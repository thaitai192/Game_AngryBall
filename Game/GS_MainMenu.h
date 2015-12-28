#ifndef __GS_MAINMENU_H__
#define __GS_MAINMENU_H__

#include "StateManager.h"
#include "Object.h"
#include "CButton.h"


class GS_MainMenu: public StateBase{
public:
	CButton** btn;
	int numOfButton;
	//int chosedButton;
	Object*  backgroundMenu;
	char **title;

	GS_MainMenu();
	void Create();
	void Update(float deltaTime);
	void Render();
	void KeyEvent(unsigned char key, bool bIsPressed);
	void MouseEvent(int x, int y, int type);
	void addState(int choise);
	void Clean();
	~GS_MainMenu();

};

#endif