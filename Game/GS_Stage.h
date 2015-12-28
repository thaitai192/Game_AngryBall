#ifndef __GS_STAGE_H__
#define __GS_STAGE_H__

#include "StateManager.h"
#include "Object.h"
#include "CButton.h"


class GS_Stage: public StateBase{
public:
	CButton btn[8];
	CButton* btnBack;
	int numOfStage;
	//int chosedButton;
	int numOfStar;
	Object*  backgroundStage;
	//Sprite*** star;
	int starEachStage[8];
	int max_map;
	//static bool is_update;

	GS_Stage();
	void Create();
	void Update(float deltaTime);
	void Render();
	void KeyEvent(unsigned char key, bool bIsPressed);
	void MouseEvent(int x, int y, int type);
	void addStage(int index);
	void Clean();
	~GS_Stage();

};

#endif