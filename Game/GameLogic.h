#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

#include "map.h"
class GameLogic{
public:
	static int UpdateStatement(Map* map);
	static void GameOver();
	static void NextMap(Map* map);
	static void Replay(Map* map);
	static void getDemo(b2Vec2 start_pos, b2Vec2 velocity,  b2Vec2 a_velocity, 
						Sprite* m_display, int numOfSprite, int &numOfDemo , Object** out);
};
#endif