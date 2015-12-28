#ifndef __MAP_H__
#define __MAP_H__

#include "StateManager.h"
#include "Sprite.h"
#include "Text.h"
#include "MyContactListener.h"
#include "Health.h"
#include "CButton.h"
#include "game.h"
class Map: public StateBase{
public: 
	//box2D
	b2World *world;	
	MyContactListener myContactListenerInstance;

	int m_ID;
	Object **ob_dis, **ob_demo;
	Sprite *m_display;
	int numOfDisplay, numOfObject, numOfDemo;
	int m_statement;
	
	int m_wind;
	char source[100];
	float change_force;
	float force;

	int m_score,  m_live, m_star, m_highscore, x2_show;
	Health* m_health;
	//bool is_finishMap, is_next;
	CButton	*m_btn_gameover, *m_btn_back, *m_btn_next, *m_btn_replay, *m_btn_shoot, *m_btn_force_pick;
	bool onGun, sound_nextmap, sound_gameover, x2_score;
	float time_show;

	
	

	Map();
	void Create();
	int Init(char* map_link, char* map_level);
	void Render();
	void Update(float deltaTime);
	void MouseDownEvent(int x, int y);
	void  MouseUpEvent(int x, int y);
	void MouseDragEvent(int x, int y);
	void KeyEvent(unsigned char key, bool bIsPressed);
	void Loadtobox2D();
	void MouseEvent(int x, int y, int type);
	void Clean();
	void OnBackButtonListener();
	//int checkWin_lose();
	void OnShootBall();
	void processNext(float deltaTime);
	void processGameOver(float deltaTime);
	void printScore();
	void OnForce_pick(int x, int y);
	bool isGunTouch(int x, int y);
	void setBox2D();
	void setObDemo();
	~Map();
};
#endif