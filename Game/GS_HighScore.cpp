#include "GS_HighScore.h"
#include "GS_Help.h"
#include "CButton.h"
#include "SceneManager.h"
#include "Text.h"
#include "Globals.h"
#include "define.h"
#include "string.h"
#include "game.h"
#include "log.h"
#include "Globals.h"

GS_HighScore* GS_HighScore::s_Instance=NULL;
GS_HighScore* GS_HighScore::GetIS(){
	if(!s_Instance){
		s_Instance = new GS_HighScore();
		s_Instance->Create();
	}
	return s_Instance;
}
GS_HighScore::GS_HighScore(){
	/*m_newScore=0;
	index_newScore=-1;
	m_dem=0;*/
}
//GS_HighScore::GS_HighScore(int newScore){
//	m_newScore= newScore;
//	index_newScore=-1;
//	m_dem=0;
//%
//}

GS_HighScore::~GS_HighScore(){
	
}
void GS_HighScore::Clean()
{
	//copy data to s_instance
	/*for(int i=0;i<NumOfHighScore;i++){
		delete[] name[i];
		LOGI("delete %d", i);
	}*/
	//delete name;
	//delete[] score;
	//delete NameAndScore;
	delete btnBack;
	//delete[] m_star;
	LOGI("END hs clean");
}

void GS_HighScore::Init(char* txt){
	LOGI("write highscore");
	FILE *f = fopen(txt,"r");
	if(!f) {
		printf("Can't not open file %s\n",txt);
		return ;}
	fscanf(f,"#Numbers of high score: %d\n",&NumOfHighScore);
	//name=new char*[NumOfHighScore];
	//score=new int[NumOfHighScore];
	//m_star= new int[NumOfHighScore];
	for(int i=0;i<NumOfHighScore;i++){
		fscanf(f,"\nID %*s\n");
		//name[i]=new char[255];
		fscanf(f,"NAME %s\n",name[i]);
		fscanf(f,"SCORE %d\n",&score[i]);
		if(score[i]<0) score[i]=0;
		fscanf(f,"STAR %d\n",&m_star[i]);
		if(m_star[i]<0) m_star[i]=0;
		if(m_star[i]>3) m_star[i]=3;
	}
	fclose(f);

	//NameAndScore=new Text();

	//NameAndScore->Initialize(ARIAL_FONT);
	//LOGI("INIt highscore success!");
}

void GS_HighScore::Create(){
	Object *BackButton=&GetSMInstance()->m_object[13];
	Vector3 posBackButton=Vector3(0,-HEIGHT_RECTANGLE/5.5*4.7,0.0);
	btnBack=new CButton(" OK",CHOOSE_TEXT_COLOR,0.7,0.7,BackButton,posBackButton);
	file_txt=LINK_HEIGHSCORE;
	Init(file_txt);

	backgroundHighScore=&GetSMInstance()->m_object[18];
	table=&GetSMInstance()->m_object[6];
	table->m_scale=Vector3(0.5,0.3,1.0);
	table->m_position=Vector3(0.0,8.0,0.0);
	 //BackButton=NULL;
	//LOGI("create highscore success!");
}


void GS_HighScore::Update(float deltaTime){
}


void GS_HighScore::Render(){
	backgroundHighScore->Render();
	//table->Render();
	
	//LOGI("%s",
	btnBack->Render();
	char line[100];
	for(int i=0;i<NumOfHighScore;i++) {
		Text::TEXT_ARIAL->RenderTextRenderString(name[i],BROWN_COLOR,1.75*Globals::screenWidth/5,(8-i+1.5)/12.0*Globals::screenHeight,1,1);
		sprintf(line, " %d", score[i]);
		Text::TEXT_ARIAL->RenderTextRenderString(line,BLACK_COLOR,2.7*Globals::screenWidth/5,(8-i+1.5)/12.0*Globals::screenHeight,1,1);}

}

void GS_HighScore::KeyEvent(unsigned char key, bool bIsPressed){
	/*if(!bIsPressed){
		switch(key){
			case VK_RETURN:
				OnButtonBackListener();
		}
	}*/
}
void GS_HighScore::MouseEvent(int x, int y, int type){
	if(type==MOUSEUP){
		//Vector3 pos = btnBack->m_position;
		//Vector3 scale = btnBack->m_scale;
		if(btnBack->isTouch(x,y) && btnBack->is_active){
			btnBack->is_active=false;
			OnButtonBackListener();
				
		}
	}else
		if(type==MOUSEDOWN){
			if(btnBack->isTouch(x,y)) btnBack->is_active=true;
		}else
			if(type==MOUSEDRAG){
				if(btnBack->is_active && !btnBack->isTouch(x,y)) btnBack=false;
			}
}

void GS_HighScore::WriteFile(char* link){
	
	FILE* f= fopen(link, "w");
	fprintf(f,"#Numbers of high score: %d\n\n", NumOfHighScore);
	for(int i=0; i<NumOfHighScore; i++){
		fprintf(f,"ID %d\n", i);
		fprintf(f,"NAME %s\n", name[i]);
		if(score[i]<0) score[i]=0;
		if(m_star[i]<0) m_star[i]=0;
		if(m_star[i]>3) m_star[i]=3;
		fprintf(f,"SCORE %d\n", score[i]);
		fprintf(f,"STAR %d\n\n", m_star[i]);
	}
	fclose(f);
}

void GS_HighScore::OnButtonBackListener(){
	//StateBase* tmp = getStateIS()->GetCurrentState();
	GetGameIS()->GameState->PopState();
	//tmp->Clean();
	//delete tmp;
}

void GS_HighScore::Check_newScore(int new_score,int new_star, int map_index){
	if(new_score > score[map_index]) score[map_index]=new_score;
	if(new_star>m_star[map_index]) m_star[map_index]= new_star;

}