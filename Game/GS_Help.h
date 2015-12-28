#ifndef __GS_HELP_H__
#define __GS_HELP_H__
#include "StateManager.h"
#include "Object.h"
#include "CButton.h"

class GS_Help: public StateBase{
public:
	GS_Help();
	CButton* btnBack;
	char* guideLine; char* guideLine2; char* guideLine3;
	Vector3 positionLine,positionLine1,positionLine2,positionLine3;
	Object *backgroundHelp;
	Object *pictureGame;
	Text *guide;
	
	void Create();
	void Update(float deltaTime);
	void Render();
	void KeyEvent(unsigned char key, bool bIsPressed);
	void MouseEvent(int x, int y, int type);
	void OnBackButtonListener();

	~GS_Help();
	void Clean();

};

#endif