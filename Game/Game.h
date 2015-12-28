#ifndef __GAME_H__
#define __GAME_H__


#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
//#include "Sprite.h"
#include "Map.h"
#include "StateManager.h"
#include "SoundManager.h"
class Game{
public:
	StateManager* GameState;
	float m_soundVolume, m_musicVolume;
	Game(void);
	static Game* s_Instance;
	static Game* GetInstance();
	unsigned loadID;
	int max_map;


	int Init(char* rm_link, char* sm_link, char* state_link);
	void Update(float deltaTime);
	void Render();
	void KeyEvent(unsigned char key, bool bIsPressed);
	void MouseDown(int x, int y);
	void MouseUp(int x, int y);
	void MouseDrag(int x, int y);
	int LoadGameMap(int index);
	void translateMouse(int &x, int &y);
	int LoadConfig(char* link);
	int SaveConfig(char* link);
	~Game();
};
#define GetGameIS() Game::GetInstance()
#endif