#pragma once
#include "StateBase.h"
#include "Sprite.h"
#include "Text.h"
#include "Object.h"
#include "CButton.h"

class GS_OptionMenu: public StateBase{
public:
	Object* backgroundOption;
	Object* backgroundOption0;
	Object* SoundBar;
	Object* SoundPointer;
	Text SoundText;
	Object* MusicBar;
	Object* MusicPointer;
	Text MusicText;
	CButton* btnBack;
	CButton* btnMute;
	CButton* btnMute2;
	Vector2 positionMusicBar;
	Vector2 positionSoundBar;

	void Create();
	void Update(float deltaTime);
	void Render();
	void KeyEvent(unsigned char key, bool bIsPressed);
	void MouseEvent(int x, int y, int type);
	void onButtonBackListener();
	void Clean();
	~GS_OptionMenu();

};