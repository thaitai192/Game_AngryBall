#ifndef __DEFINE_H__
#define __DEFINE_H__

#ifdef WIN32
#define LINK_SPRITE				"../Resources/Animation.sprite"
#define LINK_RM					"../Resources/RM.txt"
#define LINK_SM					"../Resources/SM.txt"
#define LINK_MAP				"../Resources/GameMap.txt"
#define LINK_GAME_CONFIG		"../Resources/GameConfig.txt"
#define LINK_HEIGHSCORE			"../Resources/HighScore.txt"
#define LINK_SOUND				"../Resources/SoundManager.txt"
#define DATA_PATH				"../Resources/"

#define FONT_BUTTON				"../Resources/data/arial.ttf"
#define ARIAL_FONT				"../Resources/data/arial.ttf"
#define HIGHSCORE_FONT			"../Resources/data/VKUNBI.ttf"
#define TEXT_PIXEL				5.0
#define IS_WIN32				true

//music
//#define playMusic(x, y, z)		playMusic(x, y, z)

#else
//data
#define LINK_SPRITE				"/sdcard/AngryBall/Animation.sprite"
#define LINK_RM					"/sdcard/AngryBall/RM.txt"
#define LINK_SM					"/sdcard/AngryBall/SM.txt"
#define LINK_MAP				"/sdcard/AngryBall/GameMap.txt"
#define LINK_GAME_CONFIG		"/sdcard/AngryBall/GameConfig.txt"
#define LINK_HEIGHSCORE			"/sdcard/AngryBall/HighScore.txt"
#define LINK_SOUND				"/sdcard/AngryBall/SoundManager.txt"
#define DATA_PATH				"/sdcard/AngryBall/"

//font
#define FONT_BUTTON "/sdcard/AngryBall/data/arial.ttf"
#define ARIAL_FONT  "/sdcard/AngryBall/data/arial.ttf"
#define HIGHSCORE_FONT  "/sdcard/AngryBall/data/VKUNBI.ttf"
#define TEXT_PIXEL				5
#define IS_WIN32				false

#endif
//box2d
const float timeStep = 1.0f / 48.0f;
const int velocityIterations = 6;
const int positionIterations = 2;
const float SCALE_BOX2D = 0.05f;

//sprite
#define EDGE_RECTANGLE 100.0
#define	HEIGHT_RECTANGLE 56.25
#define FPS_DEFAULT 24.0;
#define F_MAX 400.0;

#define MOUSEDOWN 1
#define MOUSEUP 2
#define MOUSEDRAG 3

//map
#define WIND_MAX 5
#define CHANGE_FORCE 0.13
#define FORCE_MAX 13.0
#define FORCE_MIN 0.2
#define SPEED_STOP 0.3
#define CANNON_ANGLE_MAX 1.3
#define CANNON_ANGLE_MIN -0.3
#define CANNON_ANGLE_CHANGE 0.05
#define NUM_OF_HEALTH 4
#define GAME_OVER_POS 21
#define NEXT_MAP_POS 24
#define REPLAY_MAP_POS 28
#define BUTTON_SHOOT_POS 34
//statement of map
#define MAP_READY 0
#define MAP_PLAYING 1
#define MAP_GAMEOVER 2
#define MAP_NEXT 3

//sprite
#define BALL_POS 0
#define GROUND_POS 1
#define WIND_POS 1
#define BASKET_POS 5
#define CANNON_POS 6
#define WHEEL_POS 8
#define FORCE_BAR_POS 7
#define BESUNG 4
#define STAR_POS 17
//object
#define BUTTON_BACK_POS 9

//color
#define DEFAULT_TEXT_COLOR	Vector4(1.0,1.0,1.0,1.0)
#define CHOOSE_TEXT_COLOR	Vector4(1.0,0.0,0.0,1.0)
#define WHITE_COLOR			Vector4(1.0,1.0,1.0,1.0)
#define BLACK_COLOR			Vector4(0.0,0.0,0.0,1.0)
#define RED_COLOR			Vector4(1.0,0.0,0.0,1.0)
#define YEALLOW_COLOR		Vector4(1.0,1.0,0.0,1.0)
#define BROWN_COLOR		Vector4(0.8,0.5,0.0,1.0)

//highscore
#define POS_NAME_COLUMN EDGE_RECTANGLE*3.7
#define POS_SCORE_COLUMN EDGE_RECTANGLE*6
#define POS_ROWN_0 HEIGHT_RECTANGLE*6.6

//Sounds and musics
#define MUSIC_BACKGROUND 0
#define MUSIC_IN_GAME 1
#define MUSIC_SHOW_SCORE 2
#define MUSIC_GAME_OVER 3
#define SOUND_SHOOTING 0
#define SOUND_GET_A_SCORE 2
#define SOUND_HIT_A_STAR 3
#define SOUND_CLICK_BUTTON 1
#define SOUND_PICK_MAP 4

#define NUM_OF_STAR 3
#endif