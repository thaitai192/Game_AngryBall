#include "GameLogic.h"
#include "define.h"
#include "Game.h"
#include "MapManager.h"
#include "GS_HighScore.h"
#include "GS_Stage.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "log.h"
int GameLogic::UpdateStatement(Map *map){
	Sprite* ball = &(map->m_display[BALL_POS]);
	Sprite* basket = &(map->m_display[BASKET_POS]);

	Vector3 ball_pos= ball->m_position;
	Vector3 b_pos= basket->m_position;	

	LOGI("Start update statement");
	if((ball->m_position.y<basket->m_position.y&&abs(ball->m_body->GetLinearVelocity().y)<=0.002)||
		ball->m_body->GetLinearVelocity().Length()<SPEED_STOP){
			//ball->m_body->SetLinearVelocity(b2Vec2(0,0));
		LOGI("Start statement map next");
			if(ball_pos.x > b_pos.x- basket->m_scale.x*EDGE_RECTANGLE+3 &&
				ball_pos.x < b_pos.x+ basket->m_scale.x*EDGE_RECTANGLE-3 &&
				ball_pos.y>b_pos.y-basket->m_scale.y*EDGE_RECTANGLE&&
				ball_pos.y<b_pos.y+basket->m_scale.y*EDGE_RECTANGLE)
			{
				return MAP_NEXT;
			}
			if(map->m_health->numOfHealth==0) return MAP_GAMEOVER;
			return MAP_READY;
	}
	else{
		LOGI("Start map_playign");
		return MAP_PLAYING;
	}
}
void GameLogic::GameOver(){
	//Map* tmp=(Map*)GetGameIS()->GameState->GetCurrentState(); 
	GetGameIS()->GameState->PopState();
	GetGameIS()->GameState->PopState();
	StateBase* stage = new GS_Stage();
		stage->Create();
		getStateIS()->PushState(stage);
	//GetSoundInstance()->pauseMusic(MUSIC_SHOW_SCORE);
	//GS_Stage::is_update=false;
	//tmp->Clean();
	//delete tmp;

}
void GameLogic::NextMap(Map* map_in){

	//add score
	if(map_in->m_health->m_run_score!=0){
		map_in->m_score-= map_in->m_health->m_run_score;
	}
	for(int i=map_in->m_health->numOfHealth-1; i>=0; i--){
		map_in->m_score+=map_in->m_health->m_score[i];
		map_in->m_health->numOfHealth--;
	}

	//StateBase* map = getStateIS()->GetCurrentState();
	

	//check highscore and star
	GS_HighScore *highscore = new GS_HighScore();
	highscore->Create();
	highscore->Check_newScore(map_in->m_score,map_in->m_star, GetMapIS()->currentmap);
	highscore->WriteFile(highscore->file_txt);
	highscore->Clean();
	delete highscore;

	GetGameIS()->GameState->PopState();
	GetGameIS()->GameState->PopState();
	StateBase* stage = new GS_Stage();
		stage->Create();
		getStateIS()->PushState(stage);
	//add next stage
	if(GetMapIS()->currentmap<GetMapIS()->numOfMap-1){
		int index= ++GetMapIS()->currentmap;
		
		Map* map2 = new Map();
		if(map2->Init(GetMapIS()->m_map[index],GetMapIS()->m_level[index])==-1) return;
		getStateIS()->PushState((StateBase*)map2);
	}
	//map->Clean();
	//delete map;
}

void GameLogic::Replay(Map* map_in){
	//add score
	if(map_in->m_health->m_run_score!=0){
		map_in->m_score-= map_in->m_health->m_run_score;
	}
	for(int i=map_in->m_health->numOfHealth-1; i>=0; i--){
		map_in->m_score+=map_in->m_health->m_score[i];
		map_in->m_health->numOfHealth--;
	}

	//StateBase* map = getStateIS()->GetCurrentState();
	
	
	//check highscore
	GS_HighScore *highscore = new GS_HighScore();
	highscore->Create();
	highscore->Check_newScore(map_in->m_score,map_in->m_star, GetMapIS()->currentmap);
	highscore->WriteFile(highscore->file_txt);
	highscore->Clean();
	delete highscore;

	getStateIS()->PopState();
	//replay stage
	int index= GetMapIS()->currentmap%GetMapIS()->numOfMap;
	
	Map* map2 = new Map();
	if(map2->Init(GetMapIS()->m_map[index],GetMapIS()->m_level[index])==-1) return;
	getStateIS()->PushState((StateBase*)map2);
	//map->Clean();
	//delete map;
}

void GameLogic::getDemo(b2Vec2 start_pos, b2Vec2 velocity,  b2Vec2 a_velocity, 
						Sprite* m_sprite, int numOfSprite, int &numOfDemo , Object** out){
	float t=2/60.0;
	numOfDemo=60;
	for(int i=0; i<numOfDemo; i++){
		float tmp_x = (start_pos.x + velocity.x*t + a_velocity.x*t*t/2)/SCALE_BOX2D;
		float tmp_y = (start_pos.y + velocity.y*t + a_velocity.y*t*t/2)/SCALE_BOX2D;
		out[i]->m_position= Vector3(tmp_x, tmp_y, 0);
		out[i]->srt_update=false;
		t+=3/60.0;
		for(int j=10; j<numOfSprite-3; j++){
			if(m_sprite[j].isTouch(tmp_x, tmp_y)) numOfDemo=i;
		}
		
	}
}