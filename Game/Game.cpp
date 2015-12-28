#include <Box2D/Box2D.h>
#include "game.h"
//#include "../Utilities/utilities.h" 
#include "ResourceManager.h"
#include "SceneManager.h"
#include "define.h"
#include "MapManager.h"
//#include "../Utilities/math.h"
#include "Text.h"
#include "GS_WelcomeScreen.h"
//#include "GS_Help.h"
//#include "GS_HighScore.h"
#include "AnimSprite.h"
//#include <stdio.h>
#include <irrKlang.h>
//#include <stdlib.h>
#include "log.h"
//unsigned int __stdcall LoadData(void *p){
//	if(GetRMInstace()->Init("RM.txt")==-1) return -1;
//	if(GetSMInstance()->Init("SM.txt")==-1) return -1;
//	if(GetMapIS()->Init("GameMap.txt")==-1) return -1;
//	
//	_endthreadex( 0 );
//	return 0;
//}
Game* Game::s_Instance=NULL;
Game* Game::GetInstance(){
	if(!s_Instance)
		s_Instance = new Game();
	return s_Instance;
}

Game::Game(void){
	//AnimSprite::getInstance()->loadFile("Animation.sprite");
	AnimSprite::getInstance()->loadFile(LINK_SPRITE, DATA_PATH);
	m_soundVolume=1.0;
	m_musicVolume= 1.0;
}
int Game::Init(char* rm_link, char* sm_link, char* game_map){
	//load data
	/*HANDLE load = (HANDLE)_beginthreadex(NULL,0,&LoadData,(void*)0,0, &loadID);
	WaitForSingleObject( load, INFINITE ); 
	CloseHandle(load);*/
	LOGI("BEFORE load sound");
	if(GetSoundInstance()->Init(LINK_SOUND, DATA_PATH)==-1) return -1;
	LOGI("after load sound");
	//LOGI(LOG_TAG, "before rm");
	if(GetRMInstace()->Init(rm_link,DATA_PATH)==-1) return -1;
	if(GetSMInstance()->Init(sm_link)==-1) return -1;
	if(GetMapIS()->Init(game_map)==-1) return -1;
	//create welcome state to start game
	GameState= getStateIS();
	StateBase* wc = new GS_WelcomeScreen();
	wc->Create();
	GameState->PushState(wc);
	//set default music, sound
	LoadConfig(LINK_GAME_CONFIG);
	GetSoundInstance()->playMusic(MUSIC_BACKGROUND,true);
	GetSoundInstance()->setVolume(m_musicVolume,m_soundVolume);
	Text::CreateFont();
	return 0;

}
void Game::Render(){
	//StateBase* tmp=GameState->GetCurrentState();
	//if(!tmp) LOGI("NULL");
	GameState->GetCurrentState()->Render();
}
void Game::Update(float deltaTime)
{
	//LOGI("update");
	GameState->GetCurrentState()->Update(deltaTime);	
	//LOGI("out update");

}
void Game::KeyEvent(unsigned char key, bool bIsPressed){
	GameState->GetCurrentState()->KeyEvent(key, bIsPressed);
}

void Game::MouseDown(int x, int y){
	translateMouse(x,y);
	GameState->GetCurrentState()->MouseEvent(x,y,MOUSEDOWN);
}
void Game::MouseUp(int x, int y){
	translateMouse(x,y);
	GameState->GetCurrentState()->MouseEvent(x,y,MOUSEUP);
}
void Game::MouseDrag(int x, int y){
	translateMouse(x,y);
	GameState->GetCurrentState()->MouseEvent(x,y,MOUSEDRAG);
}

Game::~Game(){
	SaveConfig(LINK_GAME_CONFIG);
	delete GetMapIS();
	/*while(!GameState->isEmpty()){
		StateBase* tmp = GameState->GetCurrentState();
		GameState->PopState();
		tmp->Clean();
		delete tmp;
	}*/
	delete getStateIS();
	delete AnimationInstance();
	delete GetSMInstance();
	delete GetRMInstace();
	delete GetSoundInstance();
	Text::CleanFont();
}

void Game::translateMouse(int &x, int &y){
	x=x*EDGE_RECTANGLE*2/Globals::screenWidth;
	y= y*HEIGHT_RECTANGLE*2/Globals::screenHeight;
	x-=EDGE_RECTANGLE;
	y-=HEIGHT_RECTANGLE;
	y*=-1;
}

int Game::LoadConfig(char* link){
	FILE* f= fopen(link, "r");
	if(!f) {
		printf("Can't not open file %s\n",link);
		return -1;
	}
	fscanf(f, "GAMECONFIG\n\n");
	fscanf(f, "SOUND_VOLUME %f\n",&m_soundVolume);
	fscanf(f, "MUSIC__VOLUME %f\n\n", &m_musicVolume);
	fscanf(f,"CURRENT_MAP %d\n", &max_map);
	if(max_map<0) max_map=0;
	//int a=1;
	fclose(f);
	LOGI("Load GameConfig is success!");
	
	return 0;
}

int Game::SaveConfig(char* link){
	if(m_soundVolume<0) m_soundVolume=0;
	if(m_soundVolume>1) m_soundVolume=1.0;
	if(m_musicVolume<0) m_soundVolume=0;
	if(m_musicVolume>1) m_soundVolume=1.0;
	if(max_map<0) max_map=0;
	FILE* f= fopen(link, "w");
	if(!f) {
		printf("Can't not open file %s\n",link);
		return -1;
	}
	fprintf(f, "GAMECONFIG\n\n");
	fprintf(f, "SOUND_VOLUME %f\n",m_soundVolume);
	fprintf(f, "MUSIC__VOLUME %f\n\n", m_musicVolume);
	fprintf(f,"CURRENT_MAP %d\n", max_map);
	fclose(f);

	return 0;
}