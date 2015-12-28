#include "Map.h"
#include <stdio.h>
#include <string.h>
#include "../Utilities/utilities.h"
#include "SceneManager.h"
#include "define.h"
#include "Text.h"
//#include <string.h>
#include "irrKlang.h"
#include <time.h>
#include "GS_HighScore.h"
#include "MapManager.h"
#include "GameLogic.h"
#include "GS_Stage.h"
#include "SoundManager.h"
#include "log.h"
Map::Map(){
	//GetSoundInstance()->setVolume(0);
	m_display=NULL;
	ob_dis=NULL;
	numOfDemo=60;
	ob_demo = new Object*[numOfDemo];
	for(int i=0; i<numOfDemo; i++){
		ob_demo[i]= GetSMInstance()->m_object[41].Clone();
	}
	numOfDisplay=0;
	numOfObject=0;
	//random wind
	srand(time(NULL));
	m_wind=(2*(rand()%WIND_MAX)-WIND_MAX+1);
	m_score=0;
	m_star=0;
	change_force=CHANGE_FORCE;
	m_health= new Health();

	//button on map
	m_btn_gameover=new CButton("",DEFAULT_TEXT_COLOR,0.7,0.7,
		&GetSMInstance()->m_object[GAME_OVER_POS],Vector3(15,0,0));
	m_btn_back= new CButton("",DEFAULT_TEXT_COLOR,0.7,0.7,
		&GetSMInstance()->m_object[BUTTON_BACK_POS],GetSMInstance()->m_object[BUTTON_BACK_POS].m_position);
	m_btn_next = new CButton("",DEFAULT_TEXT_COLOR,0.7,0.7,
		&GetSMInstance()->m_object[NEXT_MAP_POS],Vector3(15,0,0));
	m_btn_replay = new CButton("",DEFAULT_TEXT_COLOR,0.7,0.7,
		&GetSMInstance()->m_object[REPLAY_MAP_POS],Vector3(-15,0,0));
	m_btn_shoot= new CButton("",DEFAULT_TEXT_COLOR,0.7,0.7,
		&GetSMInstance()->m_object[BUTTON_SHOOT_POS],GetSMInstance()->m_object[BUTTON_SHOOT_POS].m_position);
	m_btn_force_pick= new CButton("",DEFAULT_TEXT_COLOR,0.7,0.7,
		&GetSMInstance()->m_object[40],GetSMInstance()->m_object[40].m_position);
	m_statement= MAP_READY;
	onGun=false;
	
	//high score
	GS_HighScore* tmp_highscore = new GS_HighScore();
	tmp_highscore->Create();
	m_highscore = tmp_highscore->score[GetMapIS()->currentmap];
	tmp_highscore->Clean();
	delete tmp_highscore;

	sound_nextmap=false;
	sound_gameover=false;
	x2_show=-1;
	x2_score=false;
	time_show=0;
}

void Map::Create(){}

int Map::Init(char* map_link, char* map_level){
	FILE *f = fopen(map_link, "r");
	if(!f) {
		printf("Can't not open file %s\n", map_link);
		return -1;}

	fscanf(f,"MAP_ID %d\n\n", &m_ID);
	fscanf(f,"OBJECTS %d\n\n", &numOfObject);
	ob_dis= new Object*[numOfObject];
	for(int i=0; i<numOfObject; i++){
		int ob_id;
		fscanf(f, "OBJECT_ID %d\n", &ob_id);
		for(int j=0; j<GetSMInstance()->numOfObject; j++){
			if(ob_id==GetSMInstance()->m_object[j].m_ID){
				ob_dis[i]=&GetSMInstance()->m_object[j];
				break;
			}
		}
		fscanf(f,"NAME %*s\n\n");
	}

	FILE *f2 = fopen(map_level, "r");
	if(!f2) {
		printf("Can't not open file %s\n", map_link);
		return -1;
	}
	int numOfDisplay1,numOfDisplay2;
	fscanf(f2,"SPRITES %d\n", &numOfDisplay2);
	fscanf(f,"SPRITES %d\n\n", &numOfDisplay1);
	numOfDisplay=numOfDisplay1 + numOfDisplay2;
	m_display= new Sprite[numOfDisplay];
	for(int i=0; i<numOfDisplay1; i++){
		fscanf(f, "SPRITE_ID %d\n", &m_display[i].m_ID);
		fscanf(f,"NAME %*s\n");
		int ob_id;
		fscanf(f,"OBJECT_ID %d\n", &ob_id);
		for(int j=0; j<GetSMInstance()->numOfObject; j++){
			if(ob_id==GetSMInstance()->m_object[j].m_ID){
				m_display[i].Clone(&GetSMInstance()->m_object[j]);
				break;
			}
		}
		Vector3 tmp;
		fscanf(f,"POSITION %f, %f, %f\n", &tmp.x,&tmp.y,&tmp.z);
		m_display[i].m_position= Vector3(tmp);
		fscanf(f, "ROTATION %f, %f, %f\n",&tmp.x,&tmp.y,&tmp.z);
		m_display[i].m_rotation=Vector3(tmp);
		fscanf(f,"SCALE %f, %f, %f\n",&tmp.x,&tmp.y,&tmp.z);
		m_display[i].m_scale=Vector3(tmp);
		char checkSensor[10];
		fscanf(f,"is_sensor %s\n\n",&checkSensor);
		if(strcmp(checkSensor,"true")==0) m_display[i].is_sensor= true;
		else m_display[i].is_sensor= false;
	}
	for(int i=0; i<numOfDisplay2; i++){
		fscanf(f2, "SPRITE_ID %d\n", &m_display[numOfDisplay1 + i].m_ID);
		fscanf(f2,"NAME %*s\n");
		int ob_id;
		fscanf(f2,"OBJECT_ID %d\n", &ob_id);
		for(int j=0; j<GetSMInstance()->numOfObject; j++){
			if(ob_id==GetSMInstance()->m_object[j].m_ID){
				m_display[numOfDisplay1 + i].Clone(&GetSMInstance()->m_object[j]);
				break;
			}
		}
		Vector3 tmp;
		fscanf(f2,"POSITION %f,%f, %f\n", &tmp.x,&tmp.y,&tmp.z);
		m_display[numOfDisplay1 + i].m_position=Vector3(tmp);
		fscanf(f2, "ROTATION %f, %f, %f\n",&tmp.x,&tmp.y,&tmp.z);
		m_display[numOfDisplay1 + i].m_rotation=Vector3(tmp);
		fscanf(f2,"SCALE %f, %f, %f\n",&tmp.x,&tmp.y,&tmp.z);
		m_display[numOfDisplay1 + i].m_scale=Vector3(tmp);
		char checkSensor[10];
		fscanf(f2,"is_sensor %s\n",&checkSensor);
		if(strcmp(checkSensor,"true")==0) m_display[numOfDisplay1 + i].is_sensor= true;
		else m_display[numOfDisplay1 + i].is_sensor= false;
		fscanf(f2, "SCORE %d\n\n",&m_display[numOfDisplay1+i].m_score);
	}
	fclose(f);
	fclose(f2);
	LOGI("Load Map is success!");

	setBox2D();
	GetSoundInstance()->pauseMusic(MUSIC_BACKGROUND);
	GetSoundInstance()->playMusic(MUSIC_IN_GAME,true, true);
	m_btn_force_pick->m_position.y = m_display[FORCE_BAR_POS].m_position.y;
	
	return 0;
}

void Map::MouseDownEvent(int x, int y)
{
	if(m_btn_back->isTouch(x,y)) 
	{
		m_btn_back->setTexture(4,1);
		m_btn_back->is_active=true;
		return;
	}
	if(m_btn_gameover->isTouch(x,y) && m_statement==MAP_GAMEOVER){m_btn_gameover->is_active=true; return;}
	if(m_btn_replay->isTouch(x,y) &&(m_statement==MAP_GAMEOVER||m_statement==MAP_NEXT)){m_btn_replay->is_active=true; return;}
	if(m_btn_next->isTouch(x,y) && m_statement==MAP_NEXT){
		m_btn_next->is_active=true; return;}
	//on shoot
	if(m_btn_shoot->isTouch(x,y)&&(m_statement==MAP_READY)){
		Sprite* ball = &m_display[BALL_POS];
		ball->is_display=false;
		ball->force=FORCE_MIN+0.001;
		m_btn_shoot->setTexture(0,1);
		m_btn_shoot->is_active=true;
		return;
	}
	//fix gun
	if(isGunTouch(x,y)) {onGun=true;return;}
	OnForce_pick(x,y);
	
}
void Map::MouseUpEvent(int x, int y)
{	
	m_btn_shoot->setTexture(0,0);
	m_btn_back->setTexture(4,0);
	if(onGun) {onGun=false; return;}
	if(m_btn_shoot->is_active && m_btn_shoot->isTouch(x,y))
	{
		m_btn_shoot->is_active=false;
		GetSoundInstance()->playSound(SOUND_SHOOTING);
		OnShootBall();
		return;
	}
	if(m_statement==MAP_GAMEOVER && m_btn_gameover->isTouch(x,y) && m_btn_gameover->is_active) {
		m_btn_gameover->is_active=false;
		GameLogic::GameOver(); return;
	}
	else if(m_statement==MAP_NEXT && m_btn_next->isTouch(x,y)&& m_btn_next->is_active){ 
		m_btn_next->is_active=false;
		GameLogic::NextMap(this); return;}
	else if(m_btn_replay->isTouch(x,y) && m_btn_replay->is_active){
		m_btn_replay->is_active=false;
		GameLogic::Replay(this);return;}
	else if(m_btn_back->isTouch(x,y) && m_btn_back->is_active)
	{
		GetSoundInstance()->pauseMusic(MUSIC_IN_GAME);
		GetSoundInstance()->playMusic(MUSIC_BACKGROUND, true, true);
		m_btn_back->is_active=false;
		OnBackButtonListener();
		return;
	}
}

void Map::MouseDragEvent(int x, int y){
	if(m_btn_back->is_active && !m_btn_back->isTouch(x,y)){m_btn_back->is_active=false;return;}
	if(m_btn_gameover->is_active && !m_btn_gameover->isTouch(x,y)){m_btn_gameover->is_active=false; return;}
	if(m_btn_replay->is_active && !m_btn_replay->isTouch(x,y)) {m_btn_replay->is_active=false; return;}
	if(m_btn_next->is_active && !m_btn_next->isTouch(x,y)){m_btn_next->is_active=false;return;}
	if(m_btn_shoot->is_active && !m_btn_shoot->isTouch(x,y)){
		m_btn_shoot->is_active=false;
		GetSoundInstance()->playSound(SOUND_SHOOTING);
		OnShootBall();
		return;
	}
	if(onGun){
		b2Vec2 ca_pos = m_display[CANNON_POS].m_body->GetPosition();
		Vector3 cannon_pos= m_display[CANNON_POS].m_position;
		Vector3 direct = cannon_pos-Vector3(x,y,0);
		Vector3 ground = Vector3(1,0,0);
		float alpha_cos = ground.Dot(direct)/ground.Length()/direct.Length();
		float alpha = acos(alpha_cos);
		if(y>cannon_pos.y) alpha=-alpha;
		if(alpha < CANNON_ANGLE_MAX && alpha > CANNON_ANGLE_MIN){
			m_display[CANNON_POS].m_body->SetTransform(b2Vec2(ca_pos.x,
						ca_pos.y),alpha);
		}
		return;
	}else{
		OnForce_pick(x,y);
	}
}
void Map::MouseEvent(int x, int y, int type){
	switch(type){
		case MOUSEDOWN: MouseDownEvent(x, y); break;
		case MOUSEUP: MouseUpEvent(x, y); break;
		case MOUSEDRAG: MouseDragEvent(x,y); break;
	}
}


void Map::Render(){
	//show sprite, object
	for(int i=0; i<numOfObject; i++){
		ob_dis[i]->Render();
	}
	for(int i=0; i<numOfDisplay; i++){
		m_display[i].Render();
	}

	//show button
	m_btn_shoot->Render();
	m_btn_back->Render();
	m_btn_force_pick->Render();
	if(m_statement==MAP_GAMEOVER) {
		m_btn_gameover->Render();
		m_btn_replay->Render();
	}else if(m_statement==MAP_NEXT){
		LOGI("start render Map next");
		m_btn_next->Render();
		m_btn_replay->Render();
		LOGI("ENd render map next");
	}

	//text
	char* line=new char[100];
		sprintf(line," %d.0",abs(m_wind));
	Text::TEXT_ARIAL->RenderTextRenderString(line, Vector4(0.0,0.0,0.0,1.0),
		Globals::screenWidth/2-8, Globals::screenHeight-50,0.5,0.5);
	if(m_statement!=MAP_NEXT&&m_statement!=MAP_GAMEOVER){
		sprintf(line," %d",m_score);
		Text::TEXT_ARIAL->RenderTextRenderString(line, Vector4(0.0,0.5,0.5,1.0),
			3*Globals::screenWidth/4.5, Globals::screenHeight-40,1.5,1.5);
	} else printScore();
	sprintf(line, " %d", m_highscore);
	Text::TEXT_ARIAL->RenderTextRenderString(" HighScore", BROWN_COLOR, 
		5*Globals::screenWidth/6, Globals::screenHeight-20,0.8,0.8);
	Text::TEXT_ARIAL->RenderTextRenderString(line, BLACK_COLOR, 
		5*Globals::screenWidth/6+10, Globals::screenHeight-40,0.5,0.5);
	delete line;

	//score when next or gameover map
	
	m_health->Render();
	
	//show demo point
	if(m_statement==MAP_READY)
		for(int i=0;  i<numOfDemo; i++) {
			Object* tmp = ob_demo[i];
			ob_demo[i]->Render();
		}
	
}
void Map::Update(float deltaTime){
	for(int i=0; i<numOfObject; i++){
		//ob_dis[i]->Update(deltaTime);
	}
	for(int i=0; i<numOfDisplay; i++){
		m_display[i].Update(deltaTime);
	}

	world->Step(timeStep*deltaTime*60, velocityIterations, positionIterations);
	LOGI("STEP time: %d",timeStep*deltaTime*60);
	//printf("%f\n", deltaTime);
	if(m_statement==MAP_PLAYING||
		m_display[BALL_POS].m_body->GetLinearVelocity().Length()>0.0005) {
			LOGI("Playing");
			m_statement = GameLogic::UpdateStatement(this);
	
	}
	if(m_statement==MAP_NEXT){ 
		LOGI("start next");
		//if(time_show==-1) time_show=2000;
		processNext(deltaTime);
	LOGI("end process next");}
	if(m_statement==MAP_GAMEOVER){
		LOGI("Game over");
		processGameOver(deltaTime);
	}

	//update force
	Sprite* ball = &m_display[BALL_POS];
	if(m_btn_shoot->is_active){
		ball->force+=change_force;
		if(ball->force<=FORCE_MIN||ball->force>=FORCE_MAX) 
			change_force*=-1;
		m_display[FORCE_BAR_POS].force=ball->force;
		if(ball->force<=FORCE_MIN) 
			ball->force=FORCE_MIN+change_force;
		LOGI("update force");
	}

	//test point demo
	setObDemo();
	LOGI("%d", m_statement);

}
void Map::KeyEvent(unsigned char key, bool bIsPressed){

}

void Map::Loadtobox2D(){
	world->ClearForces();
	for(int i=0; i<numOfDisplay; i++){
		m_display[i].Loadtobox2D(world);
	}
	m_display[CANNON_POS].m_body->SetGravityScale(0);
}


Map::~Map()
{
	
}
void Map::Clean(){
	world->ClearForces();
	delete world;
	delete[] ob_dis;
	delete m_health;
	delete []m_display;
	for(int i=0; i<60; i++) delete ob_demo[i];
	delete []ob_demo;
	delete m_btn_gameover;
	delete m_btn_back;
	delete m_btn_next;
	delete m_btn_replay;
	delete m_btn_shoot;
	delete m_btn_force_pick;
	//GetSoundInstance()->setVolume(GetGameIS()->m_musicVolume);
}


//cac ham phu

void Map::setBox2D(){
	//wind direct
	if(m_wind>0) ob_dis[WIND_POS]->m_rotation.z=3.14;
	else ob_dis[WIND_POS]->m_rotation.z=0;
	ob_dis[WIND_POS]->srt_update=false;
	//box2D
	b2Vec2 gravity((float)m_wind/5, -10.0f);
	world= new b2World(gravity);

	m_display[CANNON_POS].is_sensor=true;

	Loadtobox2D();
	b2RevoluteJointDef rjd;
	b2Vec2 tmp = m_display[WHEEL_POS].m_body->GetPosition();
	rjd.Initialize(  m_display[WHEEL_POS].m_body,m_display[CANNON_POS].m_body ,b2Vec2(tmp.x, tmp.y));
	world->CreateJoint(&rjd);

	b2DistanceJointDef jd1;
	jd1.frequencyHz=1.0;
	jd1.dampingRatio=1.0;
	jd1.bodyA= m_display[GROUND_POS].m_body;
	jd1.bodyB= m_display[WHEEL_POS].m_body;
	b2Vec2 pos = m_display[BESUNG].m_body->GetPosition()-m_display[GROUND_POS].m_body->GetPosition()
		+b2Vec2(m_display[BESUNG].m_scale.x*EDGE_RECTANGLE*SCALE_BOX2D,m_display[BESUNG].m_scale.y*EDGE_RECTANGLE*SCALE_BOX2D);
	jd1.localAnchorA.Set(pos.x, pos.y);
	jd1.localAnchorB.Set(-0.0f, -0.0f);
	b2Vec2 b1, b2, dis;
	b1 = jd1.bodyA->GetWorldPoint(jd1.localAnchorA);
	b2 = jd1.bodyB->GetWorldPoint(jd1.localAnchorB);
	dis=b2-b1;
	jd1.length=dis.Length();
	world->CreateJoint(&jd1);

	jd1.bodyA= m_display[GROUND_POS].m_body;
	jd1.bodyB= m_display[WHEEL_POS].m_body;
	pos = m_display[BESUNG].m_body->GetPosition()-m_display[GROUND_POS].m_body->GetPosition()
		+b2Vec2(0.0f,m_display[BESUNG].m_scale.y*EDGE_RECTANGLE*SCALE_BOX2D);
	jd1.localAnchorA.Set(pos.x, pos.y);
	jd1.localAnchorB.Set(-0.0f, -0.0f);
	dis=b2-b1;
	jd1.length=dis.Length();
	world->CreateJoint(&jd1);


	//m_display[BALL_POS].m_body->SetUserData(&m_display[BALL_POS]);
	myContactListenerInstance.Create();
	world->SetContactListener(&myContactListenerInstance);
	//m_display[BALL_POS].is_display=false;
}

void Map::OnBackButtonListener(){
	if(m_statement==MAP_NEXT){
	//add score
		for(int i=this->m_health->numOfHealth-1; i>=0; i--){
			this->m_score+=this->m_health->m_score[i];
			this->m_health->numOfHealth--;
		}
		
		//check highscore
		GS_HighScore *highscore = new GS_HighScore();
		highscore->Create();
		highscore->Check_newScore(this->m_score,this->m_star, GetMapIS()->currentmap);
		highscore->WriteFile(highscore->file_txt);
		highscore->Clean();
		delete highscore;
	}
	//StateBase* map = getStateIS()->GetCurrentState();
	getStateIS()->PopState();

//GS_Stage::is_update=false;

	
	//map->Clean();
	//delete map;
}

void Map::processNext(float deltaTime){
	if(!sound_nextmap)
	{
		LOGI("star sound next");
		GetSoundInstance()->pauseMusic(MUSIC_IN_GAME);
		GetSoundInstance()->playMusic(MUSIC_SHOW_SCORE,true,false);
		sound_nextmap= true;
	}
	/**loi**/
	for(int i=0; i<m_health->numOfHealth-1; i++){
		m_score+=m_health->m_score[i];
	}
	m_health->numOfHealth=0;
	if(m_star==NUM_OF_STAR){
		LOGI("3 star");
		if(!x2_score) {m_score*=2; x2_score=true;}
	}
	/**loi**/
	//increase max stage
	if(GetGameIS()->max_map < GetMapIS()->currentmap+2&&GetMapIS()->currentmap+2<=GetMapIS()->numOfMap){
		GetGameIS()->max_map = GetMapIS()->currentmap+2;}
	//change star

}

void Map::processGameOver(float deltaTime){
	if(!sound_gameover)
	{
		GetSoundInstance()->pauseMusic(MUSIC_IN_GAME);
		GetSoundInstance()->playMusic(MUSIC_GAME_OVER,true,false);
		sound_gameover= true;
	}
	if(m_score>0) m_score-=10;
	m_star=0;
}
void Map::printScore(){
	if(m_statement==MAP_NEXT||m_statement==MAP_GAMEOVER){
		//text score
		char line[100];
		sprintf(line," %d",m_score);
		Text::TEXT_ARIAL->RenderTextRenderString(line, Vector4(0.0,0.5,0.5,1.0),
			Globals::screenWidth/2-100, Globals::screenHeight-180,2.5,2.5);
			//score under ball

		if(m_statement==MAP_NEXT){
			for(int i=0; i<m_star; i++){
				Object *obj = GetSMInstance()->m_object[26].Clone();
				obj->Scale(Vector3(obj->m_scale.x/2, obj->m_scale.y/2, 0.0));
				obj->m_position= Vector3(10*i-10, 10, 0);
				obj->Render();
				delete obj;
			}
		}
	}
}
void Map::OnShootBall(){
	Sprite* ball = &m_display[BALL_POS];
	Sprite* cannon = &m_display[CANNON_POS];
	b2Vec2 cannon_pos=cannon->m_body->GetPosition();
	b2Vec2 ball_pos= ball->m_body->GetPosition();
	//hien qua bong
	ball->is_display=true;
	//set new location of the ball
	float alpha=(cannon->m_rotation.z);
	b2Vec2 ball_newposition =b2Vec2((cannon_pos.x+EDGE_RECTANGLE*cannon->m_scale.x*cos(alpha)*SCALE_BOX2D),
		(cannon_pos.y + EDGE_RECTANGLE * cannon->m_scale.x*sin(alpha)*SCALE_BOX2D));
	ball->m_body->SetTransform(ball_newposition,0);
	ball->m_body->SetLinearVelocity(b2Vec2(ball->force*cos(alpha), ball->force*sin(alpha)));
	//float tmp = ball->m_body->GetLinearVelocity().Length();
	//update force_pick
	m_btn_force_pick->m_position.y = ball->force/FORCE_MAX*2*m_display[FORCE_BAR_POS].m_scale.x*EDGE_RECTANGLE +
		(m_display[FORCE_BAR_POS].m_position.y - m_display[FORCE_BAR_POS].m_scale.x*EDGE_RECTANGLE);
	m_btn_force_pick->srt_update=false;
	ball->force=0.0;
	m_display[FORCE_BAR_POS].force=0.001;
	//ball->m_body->SetType(b2_dynamicBody);
	//engine->drop();

	//move besung
	m_display[WHEEL_POS].m_body->SetLinearVelocity(b2Vec2(-7, -1));
	m_display[WHEEL_POS].m_body->SetAngularDamping(1.0);
	//health
	m_health->numOfHealth--;
	m_display[9].m_body->SetTransform(ball_newposition,alpha-1.57);
	m_display[9].is_playAnimation=true;
	m_display[9].currentAnimation=5;
	AnimationInstance()->startTime=0;

	m_statement=MAP_PLAYING;
}

void Map::OnForce_pick(int x, int y){
	Vector3 force_pos=m_display[FORCE_BAR_POS].m_position;
	Vector3 pick_pos = m_btn_force_pick->m_position;
	Vector3 force_scale = m_display[FORCE_BAR_POS].m_scale;
	Vector3 pick_scale = m_btn_force_pick->m_scale;
	bool tmp = x > pick_pos.x-pick_scale.x*EDGE_RECTANGLE-2 && 
		x < pick_pos.x+pick_scale.x*EDGE_RECTANGLE+2;
	tmp = y > force_pos.y-force_scale.x*EDGE_RECTANGLE-2 &&
		y < force_pos.y + force_scale.x*EDGE_RECTANGLE + 2;
	if(x > pick_pos.x-pick_scale.x*EDGE_RECTANGLE-2 && 
		x < pick_pos.x+pick_scale.x*EDGE_RECTANGLE+2 && 
		y > force_pos.y-force_scale.x*EDGE_RECTANGLE &&
		y < force_pos.y + force_scale.x*EDGE_RECTANGLE){
			m_btn_force_pick->m_position.y = y;
			m_btn_force_pick->srt_update=false;
	}
}

bool Map::isGunTouch(int x, int y){
	Vector3 pos= m_display[CANNON_POS].m_position;
	Vector3 scale = m_display[CANNON_POS].m_scale;
	Vector3 tmp = Vector3(x-pos.x, y-pos.y, 0);
	
	Vector3 identifyX= Vector3(1,0,0);
	float alpha_cos= tmp.Dot(identifyX)/tmp.Length()/identifyX.Length();
	float alpha= acos(alpha_cos);
	if(tmp.y<0) alpha=-alpha;
	
	alpha-=  m_display[CANNON_POS].m_rotation.z;
	x=tmp.Length()*cos(alpha);
	y=tmp.Length()*sin(alpha);
	x+=pos.x;
	y+=pos.y;
	if(x < pos.x+EDGE_RECTANGLE*scale.x && x > pos.x - EDGE_RECTANGLE*scale.x -3&&
			y < pos.y+ EDGE_RECTANGLE*scale.y +2&& y > pos.y - EDGE_RECTANGLE*scale.y-2)
			return true;
	return false;
}

void Map::setObDemo(){
	Sprite* ball = &m_display[BALL_POS];
	Sprite* cannon = &m_display[CANNON_POS];
	b2Vec2 cannon_pos=cannon->m_body->GetPosition();
	b2Vec2 ball_pos= ball->m_body->GetPosition();
	float alpha = m_display[CANNON_POS].m_rotation.z;
	b2Vec2 pos =b2Vec2((cannon_pos.x+EDGE_RECTANGLE*cannon->m_scale.x*cos(alpha)*SCALE_BOX2D),
		(cannon_pos.y + EDGE_RECTANGLE * cannon->m_scale.x*sin(alpha)*SCALE_BOX2D));

	float force = (m_btn_force_pick->m_position.y - 
		(m_display[FORCE_BAR_POS].m_position.y - m_display[FORCE_BAR_POS].m_scale.x*EDGE_RECTANGLE))
		/2/(m_display[FORCE_BAR_POS].m_scale.x*EDGE_RECTANGLE)*FORCE_MAX;

	
	b2Vec2 velocity = b2Vec2(force*cos(alpha), force*sin(alpha));
	b2Vec2 a_velocity = world->GetGravity();
	GameLogic::getDemo(pos, velocity, a_velocity, m_display, numOfDisplay, numOfDemo, ob_demo);
}