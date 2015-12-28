#include "GS_WelcomeScreen.h"
#include "SceneManager.h"
//#include "StateManager.h"
#include "Globals.h"
#include <time.h>
#include "Globals.h"


void GS_WelcomeScreen::Render(){
	obj->Render();
	//Vector4 red=Vector4(0.0,1.0,0.0,1.0);
	Text::TEXT_VKUNBI->RenderTextRenderString(m_text,color,Globals::screenWidth/2-7*20,Globals::screenHeight/3,3.0,3.0);
	
}

GS_WelcomeScreen::GS_WelcomeScreen(){
	obj = NULL;
	
}

void GS_WelcomeScreen::Create(){
	timeLoading=  4000;
	obj = &GetSMInstance()->m_object[0];
	char link[100];
	sprintf(link, "%s%s",DATA_PATH,"data/arial.ttf");
	//loading.Initialize(link);
	color = Vector4(0.56,0.56,0.56,1.0);
	strcpy(m_text, " Loading");
}
void GS_WelcomeScreen::Update(float deltaTime){
	if(timeLoading>=0)
	{
		timeLoading-=1000*deltaTime;
		int tmp= timeLoading/300;
		if(timeLoading>=tmp*300 && timeLoading< tmp*333){
			if(strcmp(m_text," Loading")==0){
				strcpy(m_text, " Loading.");
			}else{
				if(strcmp(m_text," Loading.")==0){
					strcpy(m_text, " Loading..");
				}else{
					if(strcmp(m_text," Loading..")==0){
						strcpy(m_text, " Loading...");
					}else{
						strcpy(m_text, " Loading");
					}
				}
			 }
			 timeLoading= tmp*300-1;
		 }
	  
	 }else{
		  StateBase* mainmenu=new GS_MainMenu();
		  mainmenu->Create();
		  //StateBase* wc = getStateIS()->GetCurrentState();
		  getStateIS()->PopState();
		  //delete wc;
		  getStateIS()->PushState(mainmenu);
	 }
}

void GS_WelcomeScreen::KeyEvent(unsigned char key, bool bIsPressed){}
void GS_WelcomeScreen::MouseEvent(int x, int y, int type){}

GS_WelcomeScreen::~GS_WelcomeScreen(){
	//obj=NULL;
}
void GS_WelcomeScreen::Clean(){
	//obj=NULL;
}