#include "StateBase.h"
#include "GS_OptionMenu.h"
#include "SceneManager.h"
#include "game.h"
#include "define.h"
#include "log.h"
void GS_OptionMenu::Clean(){	
	delete SoundPointer;
	delete MusicPointer;
	delete btnBack;
	delete btnMute;
	delete btnMute2;
}

void GS_OptionMenu::Create(){
	//char link[100];
	//sprintf(link, "%s%s", DATA_PATH, "data/arial.ttf");
	//SoundText.Initialize(link);
	//MusicText.Initialize(link);

	SoundBar = &GetSMInstance()->m_object[14];
	SoundPointer=GetSMInstance()->m_object[15].Clone();
	MusicBar = &GetSMInstance()->m_object[16];
	MusicPointer=GetSMInstance()->m_object[17].Clone();

	SoundBar->m_position=Vector3(10.0,16.5,0.0);
	SoundBar->m_scale=Vector3(0.61/1.25,0.04/1.25,1.0);

	SoundPointer->m_position=Vector3(-35.6,16.5,0.0);
	SoundPointer->m_position.x= GetGameIS()->m_soundVolume*2*(SoundBar->m_scale.x*EDGE_RECTANGLE)+
		(SoundBar->m_position.x-SoundBar->m_scale.x*EDGE_RECTANGLE);
	SoundPointer->m_scale=Vector3(0.06,0.04,1.0);

	MusicBar->m_position=Vector3(10.0,-4.2,0.0);
	MusicBar->m_scale=Vector3(0.61/1.25,0.04/1.25,1.0);

	MusicPointer->m_position=Vector3(-35.6,-4.2,0.0);
	MusicPointer->m_position.x= GetGameIS()->m_musicVolume*2*(MusicBar->m_scale.x*EDGE_RECTANGLE)+
		(MusicBar->m_position.x-MusicBar->m_scale.x*EDGE_RECTANGLE);
	MusicPointer->m_scale=Vector3(0.06,0.04,1.0);
	
	Object *BackButton=&GetSMInstance()->m_object[13];
	Object *MuteButton=&GetSMInstance()->m_object[32];
	MuteButton->m_scale=Vector3(0.03/1.25,0.03/1.25,1.0);

	Vector3 posBackButton=Vector3(0,-HEIGHT_RECTANGLE/5.5*4,0.0);
	Vector3 posMuteButton=Vector3(65.0,16.5,0.0);
	Vector3 posMuteButton2=Vector3(65.0,-4.2,0.0);

	btnBack=new CButton(" Back",WHITE_COLOR,0.8,0.8,BackButton,posBackButton);
	btnMute=new CButton("",WHITE_COLOR,0.7,0.7,MuteButton,posMuteButton);
	btnMute2=new CButton("",WHITE_COLOR,0.7,0.7,MuteButton,posMuteButton2);
	
	positionSoundBar=Vector2(200,400);
	positionMusicBar=Vector2(200,350);

	//backgroundOption=&GetSMInstance()->m_object[30];
	backgroundOption0=&GetSMInstance()->m_object[30];
}


void GS_OptionMenu::Update(float deltaTime){
	//Render();
}


void GS_OptionMenu::Render(){
	backgroundOption0->Render();
	//backgroundOption->Render();
	SoundBar->Render();
	SoundPointer->Render();
	MusicBar->Render();
	MusicPointer->Render();
	btnBack->Render();
	//btnMute->Render();
	//btnMute2->Render();

	/*SoundText.RenderTextRenderString(" Sound",BLACK_COLOR,positionSoundBar.x,positionSoundBar.y,1.0,1.0);
	MusicText.RenderTextRenderString(" Music",BLACK_COLOR,positionMusicBar.x,positionMusicBar.y,1.0,1.0);*/
}

void GS_OptionMenu::KeyEvent(unsigned char key, bool bIsPressed){
	//if(!bIsPressed){
	//	switch(key){
	//		case VK_RETURN: //do something here
	//			onButtonBackListener();
	//			break;
	//	}
	//}

}

void GS_OptionMenu::MouseEvent(int x, int y, int type){
	LOGI("On touch option");
	if(type==MOUSEUP){
		LOGI("On up option");
		//Vector3 pos = btnBack->m_position;
		//Vector3 scale = btnBack->m_scale;
		if(btnBack->isTouch(x,y) && btnBack->is_active){
			btnBack->is_active=false;
			onButtonBackListener();
		}
	}else
	if(type==MOUSEDRAG)
	{
		LOGI("On drag option");
		Vector3 pos_soundbar= SoundBar->m_position;
		Vector3 pos_mucsicbar = MusicBar->m_position;
		Vector3 posSoundPointer = SoundPointer->m_position;
		Vector3 scaleSoundPointer = SoundPointer->m_scale;
		if(x > pos_soundbar.x-SoundBar->m_scale.x*EDGE_RECTANGLE+2&&
					x< pos_soundbar.x+SoundBar->m_scale.x*EDGE_RECTANGLE-2&&
			y < posSoundPointer.y+ EDGE_RECTANGLE*scaleSoundPointer.y+5 && 
			y > posSoundPointer.y - EDGE_RECTANGLE*scaleSoundPointer.y-5){
					SoundPointer->m_position.x=x;
					SoundPointer->srt_update=false;
					GetGameIS()->m_soundVolume= (x-(pos_soundbar.x-SoundBar->m_scale.x*EDGE_RECTANGLE)) /
						2/(SoundBar->m_scale.x*EDGE_RECTANGLE);
					if(GetGameIS()->m_soundVolume<0.05) GetGameIS()->m_soundVolume=0;
		}
		Vector3 posMusicPointer = MusicPointer->m_position;
		Vector3 scaleMusicPointer = MusicPointer->m_scale;
		if(x>pos_mucsicbar.x-MusicBar->m_scale.x*EDGE_RECTANGLE+2&&
			x<pos_mucsicbar.x+MusicBar->m_scale.x*EDGE_RECTANGLE-2&&
			y < posMusicPointer.y+ EDGE_RECTANGLE*scaleMusicPointer.y+5 &&
			y > posMusicPointer.y - EDGE_RECTANGLE*scaleMusicPointer.y-5){
				MusicPointer->m_position.x=x;
				MusicPointer->srt_update=false;
				GetGameIS()->m_musicVolume= (x-(pos_mucsicbar.x-MusicBar->m_scale.x*EDGE_RECTANGLE)) /
					2/(MusicBar->m_scale.x*EDGE_RECTANGLE);
				if(GetGameIS()->m_musicVolume<0.05) GetGameIS()->m_musicVolume=0;
		}

		if(btnBack->is_active && !btnBack->isTouch(x,y)) btnBack->is_active=false;
	}else{
		if(type==MOUSEDOWN){
			if(btnBack->isTouch(x,y)) btnBack->is_active=true;
		}
	}
	GetSoundInstance()->setVolume(GetGameIS()->m_musicVolume,GetGameIS()->m_soundVolume);
}

GS_OptionMenu::~GS_OptionMenu(){}

void GS_OptionMenu::onButtonBackListener(){
	//StateBase* tmp = GetGameIS()->GameState->GetCurrentState();
	GetGameIS()->GameState->PopState();
	//tmp->Clean();
	//int a=1;
	//delete tmp;
}