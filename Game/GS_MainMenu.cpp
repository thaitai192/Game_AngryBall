#include "StateBase.h"
#include "GS_MainMenu.h"
//#include "CButton.h"
#include "SceneManager.h"
#include "Globals.h"
#include "define.h"
#include "GS_OptionMenu.h"
#include "GS_Help.h"
#include "MapManager.h"
#include "map.h"
#include "GS_Stage.h"
#include "GS_HighScore.h"
#include "log.h"


GS_MainMenu::GS_MainMenu(){
	numOfButton=5;
	Object *obj=&GetSMInstance()->m_object[13];
	obj->m_scale=Vector3(0.24,0.0675,1.0);

	Vector3 posPlayButton=Vector3(0,HEIGHT_RECTANGLE/3.5*2.0,0.0);
	Vector3 posHighScoreButton=Vector3(0,HEIGHT_RECTANGLE/3.5*1.0,0.0);
	Vector3 posOptionButton=Vector3(0,-HEIGHT_RECTANGLE/3.5*0,0.0);
	Vector3 posHelpButton=Vector3(0,-HEIGHT_RECTANGLE/3.5*1,0.0);
	Vector3 posQuitButton=Vector3(0,-HEIGHT_RECTANGLE/3.5*2,0.0);

	btn = new CButton*[numOfButton];
	title= new char*[5];
	for(int i=0; i<5; i++) title[i]  = new char[25];
	strcpy(title[0], " Play");
	strcpy(title[1], " High Score ");
	strcpy(title[2], " Options");
	strcpy(title[3], " Help");
	strcpy(title[4], " Quit");
	btn[0]=new CButton	 (title[0],DEFAULT_TEXT_COLOR,1,1,obj,posPlayButton);
	btn[1]=new CButton	 (title[1],DEFAULT_TEXT_COLOR,1,1,obj,posHighScoreButton);
	btn[2]=new CButton	 (title[2],DEFAULT_TEXT_COLOR,1,1,obj,posOptionButton);
	btn[3]=new CButton	 (title[3],DEFAULT_TEXT_COLOR,1,1,obj,posHelpButton);
	btn[4]=new CButton	 (title[4],DEFAULT_TEXT_COLOR,1,1,obj,posQuitButton);
}
void GS_MainMenu::Create(){

	//set background
	backgroundMenu=&GetSMInstance()->m_object[25];
//chosedButton=-1;
}


void GS_MainMenu::Update(float deltaTime){
	//LOGI("in gs_mainmenu");
	for(int i=0; i<numOfButton; i++){
		btn[i]->Update(deltaTime);
	}
	//LOGI("out of gs_mainmenu");
}


void GS_MainMenu::Render(){
	//LOGI("RESUME");
	backgroundMenu->Render();
	for(int i=0; i<numOfButton; i++)
		btn[i]->Render();
		//LOGI("%s",title[0]);
}

GS_MainMenu::~GS_MainMenu(){
	/*backgroundMenu=NULL;
	for(int i=0; i<numOfButton; i++)
		delete btn[i];
	delete[] btn;*/
}

void GS_MainMenu::Clean(){
	//backgroundMenu=NULL;
	for(int i=0; i<numOfButton; i++)
		delete btn[i];
	delete[] btn;
	for(int i=0; i<5; i++) delete title[i];
	delete title;
}
void GS_MainMenu::KeyEvent(unsigned char key, bool bIsPressed){
	/*if(!bIsPressed){
		int tmp;
		btn[chosedButton]->text_color= DEFAULT_TEXT_COLOR;
		if(chosedButton== numOfButton-1)
		{
		}
		switch(key){
			case VK_DOWN: 
				tmp= chosedButton;
				chosedButton=(chosedButton+1)%numOfButton;
					btn[tmp]->m_scale.x=0.12;
					btn[tmp]->m_scale.y=0.03;
					btn[tmp]->srt_update= false;
				btn[chosedButton]->m_scale.x*=1.2;
				btn[chosedButton]->m_scale.y*=1.2;
				btn[chosedButton]->srt_update= false;
				break;
			case VK_UP:
				if(chosedButton==-1) chosedButton=0;
				tmp= chosedButton;
				chosedButton=(chosedButton+numOfButton-1)%numOfButton;
				btn[tmp]->m_scale.x=0.12;
				btn[tmp]->m_scale.y=0.03;
				btn[tmp]->srt_update= false;
				btn[chosedButton]->m_scale.x*=1.2;
				btn[chosedButton]->m_scale.y*=1.2;
				btn[chosedButton]->srt_update= false;
				break;
		}
		btn[chosedButton]->text_color= CHOOSE_TEXT_COLOR;
		if(key==VK_RETURN) addState();
	}*/
}
void GS_MainMenu::MouseEvent(int x, int y, int type){
	Vector3 pos, scale;
	if(type==MOUSEDOWN){
		for(int i=0; i < numOfButton; i++){
			pos = btn[i]->m_position;
			scale = btn[i]->m_scale;
			if(btn[i]->isTouch(x,y))
			{
				//chosedButton= i;
				btn[i]->text_color=CHOOSE_TEXT_COLOR;
				btn[i]->m_scale.x= scale.x*1.2;
				btn[i]->m_scale.y =scale.y*1.2;
				btn[i]->srt_update=false;
				btn[i]->is_active=true;
				return;
			}
		}
	}else 
	if(type==MOUSEUP){
		for(int i=0; i < numOfButton; i++){
			pos = btn[i]->m_position;
			scale = btn[i]->m_scale;
			if(btn[i]->isTouch(x,y)&& btn[i]->is_active)
			{	
				btn[i]->text_color= DEFAULT_TEXT_COLOR;
				btn[i]->m_scale.x/=1.2;
				btn[i]->m_scale.y/=1.2;
				btn[i]->srt_update=false;
				//chosedButton=i;
				addState(i);
				btn[i]->is_active=false;
				return;
				//chosedButton=-1;
			}
		}
	}else
		if(type==MOUSEDRAG){
			for(int i=0; i<numOfButton; i++){
				if(btn[i]->is_active&&!btn[i]->isTouch(x,y)){
					btn[i]->text_color= DEFAULT_TEXT_COLOR;
					btn[i]->m_scale.x/=1.2;
					btn[i]->m_scale.y/=1.2;
					btn[i]->srt_update=false;
					btn[i]->is_active=false;
					return;
				}
			}
		}
}
void GS_MainMenu::addState(int chosedButton){
	if(chosedButton==0){
		StateBase* stage = new GS_Stage();
		stage->Create();
		getStateIS()->PushState(stage);
	}
	if(chosedButton==1){
		StateBase* hs = new GS_HighScore();
		hs->Create();
		getStateIS()->PushState(hs);
	}
	if(chosedButton==2){
		StateBase* option = new GS_OptionMenu();
		option->Create();
		getStateIS()->PushState(option);
	}else{
		if(chosedButton==3){
			StateBase* help = new GS_Help();
			help->Create();
			getStateIS()->PushState(help);
		}else{
			if(chosedButton==4) exit(true);
		}

	}
}