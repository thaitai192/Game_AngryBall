#include "GS_Help.h"
#include "CButton.h"
#include "SceneManager.h"
#include "Text.h"
#include "Globals.h"
#include "define.h"

GS_Help::~GS_Help(){
}
void GS_Help::Clean(){
	delete btnBack;
	delete guide;
}
GS_Help::GS_Help(){}

void GS_Help::Create(){
	Object *BackButton=&GetSMInstance()->m_object[13];

	Vector3 posBackButton=Vector3(0,-HEIGHT_RECTANGLE/5.5*4,0.0);
	btnBack=new CButton(" Back",CHOOSE_TEXT_COLOR,0.7,0.7,BackButton,posBackButton);
	positionLine=Vector3(340.0,470.0,0.0);
	positionLine1=Vector3(Globals::screenWidth/1.95,Globals::screenHeight/1.5,0.0);
	positionLine2=Vector3(positionLine1.x,positionLine1.y-Globals::screenHeight/4.8,0.0);
	positionLine3=Vector3(positionLine1.x,325.0,0.0);
	backgroundHelp=&GetSMInstance()->m_object[19];
	pictureGame=&GetSMInstance()->m_object[20];
	pictureGame->m_scale=Vector3(0.35,0.2,1.0);
	pictureGame->m_position=Vector3(0,-HEIGHT_RECTANGLE/5.5*1.5,0.0);
	guide=new Text();
	guide->Initialize(ARIAL_FONT);
}


void GS_Help::Update(float deltaTime){
}


void GS_Help::Render(){
	backgroundHelp->Render();
	//pictureGame->Render();
	btnBack->Render();
	//Text::TEXT_ARIAL->RenderTextRenderString(" HOW TO PLAY ", RED_COLOR, positionLine.x,positionLine.y,2.0,2.0);
	Text::TEXT_ARIAL->RenderTextRenderString(" Press and hold bottom",BLACK_COLOR,positionLine1.x,positionLine1.y,0.7,0.7);
	Text::TEXT_ARIAL->RenderTextRenderString(" of the ack-ack to",BLACK_COLOR,positionLine1.x,positionLine1.y-Globals::screenHeight/19.2,0.7,0.7);
	Text::TEXT_ARIAL->RenderTextRenderString(" change angle of gun.",BLACK_COLOR,positionLine1.x,positionLine1.y-2*Globals::screenHeight/19.2,0.7,0.7);
	Text::TEXT_ARIAL->RenderTextRenderString(" Press and hold green ",BLACK_COLOR,positionLine2.x,positionLine2.y,0.7,0.7);
	Text::TEXT_ARIAL->RenderTextRenderString(" button to adjust force.",BLACK_COLOR,positionLine2.x,positionLine2.y-Globals::screenHeight/19.2,0.7,0.7);
	//Text::TEXT_ARIAL->RenderTextRenderString(" Play and have fun...",BLACK_COLOR,positionLine3.x,positionLine3.y,1.0,1.0);
}

void GS_Help::KeyEvent(unsigned char key, bool bIsPressed){
	//if(!bIsPressed){
	//	switch(key){
	//		case VK_RETURN: //do something here
	//			OnBackButtonListener();
	//	}
	//}
}
void GS_Help::MouseEvent(int x, int y, int type){
	if(type==MOUSEUP){
		//Vector3 pos = btnBack->m_position;
		//Vector3 scale = btnBack->m_scale;
		if(btnBack->isTouch(x,y) && btnBack->is_active){
			btnBack->is_active=false;
			OnBackButtonListener();
		}
	}else
		if(type==MOUSEDOWN){
			if(btnBack->isTouch(x,y)) btnBack->is_active=true;
		}else
			if(type==MOUSEDRAG){
				if(btnBack->is_active && !btnBack->isTouch(x,y)) btnBack=false;
			}
}

void GS_Help::OnBackButtonListener(){
	//StateBase* tmp = getStateIS()->GetCurrentState();
	getStateIS()->PopState();
	//tmp->Clean();
	//delete tmp;
}