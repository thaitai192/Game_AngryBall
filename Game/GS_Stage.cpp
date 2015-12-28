#include "GS_Stage.h"
#include "StateBase.h"
#include "CButton.h"
#include "SceneManager.h"
#include "Globals.h"
#include "define.h"
#include "GS_OptionMenu.h"
#include "GS_Help.h"
#include "Map.h"
#include "MapManager.h"
#include "game.h"
#include "GS_HighScore.h"
#include "log.h"


//bool GS_Stage::is_update=false;
void GS_Stage::Clean(){
	LOGI("start gs_stage clean");
	LOGI("start delete button");
	/*for(int i=0; i<numOfStage; i++)
		btn[i].Clean();*/
	LOGI("end delete button");
	/*delete[] btn;*/
	/*LOGI("start delete btnBack");
	
	LOGI("end delete btnBack");
	
	for(int i=0; i<numOfStage; i++){
		for(int j=0; j<starEachStage[i]; j++){
			delete star[i][j];
		}
		delete star[i];
	}
	delete star;
	LOGI("end delete star[][]");
	delete starEachStage;
	LOGI("end stareachstage");*/
	delete btnBack;
	
}
GS_Stage::GS_Stage(){
	//is_update=false;
}
void GS_Stage::Create(){
	max_map= GetGameIS()->max_map;
	numOfStage= 8;
	Object *BackButton=&GetSMInstance()->m_object[42];
	Vector3 posBackButton=Vector3(0,-HEIGHT_RECTANGLE/5.5*3,0.0);
	btnBack=new CButton(" Back",DEFAULT_TEXT_COLOR,0.7,0.7,BackButton,posBackButton);
	Object *obj=&GetSMInstance()->m_object[23];
	Vector3 *posStage=new Vector3[8];
	 posStage[0]=Vector3(-EDGE_RECTANGLE/5*3,HEIGHT_RECTANGLE/5.5*3,0.0);
	 posStage[1]=Vector3(-EDGE_RECTANGLE/5*1,HEIGHT_RECTANGLE/5.5*3,0.0);
	 posStage[2]=Vector3( EDGE_RECTANGLE/5*1,HEIGHT_RECTANGLE/5.5*3,0.0);
	 posStage[3]=Vector3( EDGE_RECTANGLE/5*3,HEIGHT_RECTANGLE/5.5*3,0.0);

	 posStage[4]=Vector3(-EDGE_RECTANGLE/5*3,HEIGHT_RECTANGLE/5.5*0,0.0);
	 posStage[5]=Vector3(-EDGE_RECTANGLE/5*1,HEIGHT_RECTANGLE/5.5*0,0.0);
	 posStage[6]=Vector3( EDGE_RECTANGLE/5*1,HEIGHT_RECTANGLE/5.5*0,0.0);
	 posStage[7]=Vector3( EDGE_RECTANGLE/5*3,HEIGHT_RECTANGLE/5.5*0,0.0);

	//btn = new CButton*[numOfStage];
	//starEachStage=new int[numOfStage];
	/*FILE *f = fopen(LINK_HEIGHSCORE,"r");
	if(!f) {
		printf("Can't not open file.\n");
		return ;}
	fscanf(f,"#Numbers of high score: %d\n",&numOfStage);
	for(int i=0;i<numOfStage;i++){
		fscanf(f,"\nID %*s\n");
		fscanf(f,"NAME %*s\n");
		fscanf(f,"SCORE %*d\n");
		fscanf(f,"STAR %d\n",&starEachStage[i]);
	}
	fclose(f);*/
	GS_HighScore *highscore= new GS_HighScore();
 	highscore->Create();
	for(int i=0; i<highscore->NumOfHighScore; i++){
		starEachStage[i]= highscore->m_star[i];
	}
	highscore->Clean();
	delete highscore;
	obj->m_scale=Vector3(0.1,0.1,1.0);
	 for(int i=0;i<max_map;i++){
	  char* line=new char[10];
	  sprintf(line," %d",i+1);
	  btn[i].Init(line,DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[i]);
	  delete line;
	 }
	 obj=&GetSMInstance()->m_object[27];
	 obj->m_scale=Vector3(0.075,0.075,1.0);
	 for(int i=max_map;i<numOfStage;i++){
		  char* line1=new char[10];
		  sprintf(line1," %d",i+1);
		  btn[i].Init(line1,DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[i]);
		  delete line1;
	 }
	/*btn[0]=new CButton	 (" 1 ",DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[0]);
	btn[1]=new CButton	 (" 2",DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[1]);
	btn[2]=new CButton	 (" 3",DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[2]);
	btn[3]=new CButton	 (" 4",DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[3]);
	btn[4]=new CButton	 (" 5",DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[4]);
	btn[5]=new CButton	 (" 6",DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[5]);
	btn[6]=new CButton	 (" 7",DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[6]);
	btn[7]=new CButton	 (" 8",DEFAULT_TEXT_COLOR,1.0,1.0,obj,posStage[7]);*/

	//star=new Sprite**[numOfStage];
	//for(int i=0; i<numOfStage; i++){
	//	star[i]= new Sprite*[NUM_OF_STAR];
	//}
	////numOfStar=3;
	//for(int j=0;j<numOfStage;j++){
	//for(int i=0;i<starEachStage[j];i++){
	//	star[j][i]= new Sprite(&GetSMInstance()->m_object[26]);
	//	star[j][i]->m_scale=Vector3(0.025,0.025,1.0);
	//	star[j][i]->m_position=Vector3(posStage[j].x-6+6*i,posStage[j].y-13,posStage[j].z);
	//}
	//}
	//set background
	backgroundStage=&GetSMInstance()->m_object[22];
//chosedButton= 0;
	//btn[chosedButton]->text_color= CHOOSE_TEXT_COLOR;
	delete[] posStage;

}


void GS_Stage::Update(float deltaTime){
	for(int i=0; i<numOfStage; i++){
		btn[i].Update(deltaTime);
	}
	/*if(!is_update) {
		this->Clean();
		Create();
		is_update=true;
	}*/
}


void GS_Stage::Render(){
	backgroundStage->Render();
	btnBack->Render();
	for(int i=0; i<numOfStage; i++)
		btn[i].Render();
	
	for(int j=0;j<max_map;j++){
		for(int i=0;i<starEachStage[j];i++){
			Sprite* star = new Sprite(&GetSMInstance()->m_object[26]);
			star->m_position= btn[j].m_position-Vector3(btn[j].m_scale.x* EDGE_RECTANGLE-4*i-5,
				btn[j].m_scale.y* EDGE_RECTANGLE+2, 0.0);
			star->Render();
			delete star;
		}
	}
	
	
}

GS_Stage::~GS_Stage()
{
	LOGI("delete gs_Stage");	
}

void GS_Stage::KeyEvent(unsigned char key, bool bIsPressed){
	/*if(!bIsPressed){
		if(chosedButton!=-1){
			btn[chosedButton]->text_color= DEFAULT_TEXT_COLOR;
		}
		btnBack->text_color=DEFAULT_TEXT_COLOR;
		switch(key){
			case VK_RIGHT: if(chosedButton!=7)
							   chosedButton=(chosedButton+numOfStage+1)%numOfStage;
						   else chosedButton=-1;
				break;
			case VK_LEFT: if(chosedButton!=0)
							  if(chosedButton==-1)
								  chosedButton=7;
							  else
								  chosedButton=(chosedButton+numOfStage-1)%numOfStage;
						   else chosedButton=-1;
				break;
			case VK_DOWN: if(chosedButton+4<numOfStage&&chosedButton!=-1)
							  chosedButton=(chosedButton+4)%numOfStage;
						  else chosedButton=-1;
				break;
			case VK_UP:	 if(chosedButton==-1)
							  chosedButton=numOfStage-3;
						 else if(chosedButton>3)
							 chosedButton=(chosedButton+4)%numOfStage;
						 else chosedButton=-1;

				break;
		}
		if(chosedButton==-1)
			btnBack->text_color=CHOOSE_TEXT_COLOR;
		else
			btn[chosedButton]->text_color= CHOOSE_TEXT_COLOR;

		if(key==VK_RETURN) addStage();
	}*/
}
void GS_Stage::MouseEvent(int x, int y, int type){

	if(type==MOUSEUP){
		for(int i=0; i < max_map; i++){
			Vector3 pos = btn[i].m_position;
			Vector3 scale = btn[i].m_scale;
			if(btn[i].isTouch(x,y)&&btn[i].is_active)
			{
				//chosedButton=i;
					addStage(i);
					btn[i].is_active=false;
					btn[i].setTexture(3,0);
			}
			
		}
		Vector3 posBack = btnBack->m_position;
			Vector3 scaleBack = btnBack->m_scale;
			
			if(btnBack->isTouch(x,y) && btnBack->is_active)
			{
				btnBack->setTexture(2,0);
				btnBack->is_active=false;
				//StateBase* tmp = getStateIS()->GetCurrentState();
				GetGameIS()->GameState->PopState();
				
				LOGI("Stage Back");

			}
	}else

	if(type==MOUSEDOWN){
		for(int i=0; i < max_map; i++){
			Vector3 pos = btn[i].m_position;
			Vector3 scale = btn[i].m_scale;
			if(btn[i].isTouch(x,y))
			{
				GetSoundInstance()->playSound(SOUND_PICK_MAP);
				btn[i].setTexture(3,1);
				btn[i].is_active=true;
				return;
			}
		}
		Vector3 posBack = btnBack->m_position;
		Vector3 scaleBack = btnBack->m_scale;
		if(btnBack->isTouch(x,y))
		{
			btnBack->setTexture(2,1);
			btnBack->is_active=true;
		}
	}else
		if(type==MOUSEDRAG){
			for(int i=0; i<max_map; i++){
				if(btn[i].is_active && !btn[i].isTouch(x,y)){
					btn[i].is_active=false;
					btn[i].setTexture(3,0);
					return;
				}
			}
			if(btnBack->is_active && !btnBack->isTouch(x,y)){
				btnBack->is_active=false;
				btnBack->setTexture(2,0);
			}
		}
}

void GS_Stage::addStage(int chosedButton){
	if(chosedButton==-1){
		//StateBase* tmp = getStateIS()->GetCurrentState();
					//GetGameIS()->GameState->PopState();
					//tmp->Clean();
					//delete tmp;
	}
	else if(chosedButton < GetMapIS()->numOfMap){
		GetMapIS()->currentmap= chosedButton;
		Map* map = new Map();
		if(map->Init(GetMapIS()->m_map[chosedButton],GetMapIS()->m_level[chosedButton])==-1) return;
		getStateIS()->PushState((StateBase*)map);
	}

}