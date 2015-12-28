#include "CButton.h"
#include "log.h"
#include "SoundManager.h"
CButton::CButton(){
	buttName= NULL;
}
CButton::CButton(char* buttn, Vector4 color, float scaleX, float scaleY, Object* obj, Vector3 position){
	buttName= new char[100];
	strcpy(buttName, buttn);
	text_color=color;
	text_scaleX=scaleX;
	text_scaleY=scaleY;
	numOfTexture= obj->numOfTexture;
	m_texture_list= new Texture*[numOfTexture];
	if(numOfTexture>=2)
		m_currentTexture=1;
	else m_currentTexture=0;
	is_sensor=false;
	for(int i=0; i<numOfTexture; i++)
		m_texture_list[i]= obj->m_texture_list[i];
	m_model= obj->m_model;
	m_myShaders= obj->m_myShaders;
	m_position= Vector3(position);
	m_rotation = Vector3(obj->m_rotation);
	m_scale= Vector3(obj->m_scale);

	//title.Initialize(FONT_BUTTON);
	text_pos=getTextPos();
	is_active=false;
}
void CButton::Init(char* buttn, Vector4 color, float scaleX, float scaleY, Object* obj, Vector3 position){
	buttName= new char[100];
	strcpy(buttName, buttn);
	text_color=color;
	text_scaleX=scaleX;
	text_scaleY=scaleY;
	numOfTexture= obj->numOfTexture;
	m_texture_list= new Texture*[numOfTexture];
	if(numOfTexture>=2)
		m_currentTexture=1;
	else m_currentTexture=0;
	is_sensor=false;
	for(int i=0; i<numOfTexture; i++)
		m_texture_list[i]= obj->m_texture_list[i];
	m_model= obj->m_model;
	m_myShaders= obj->m_myShaders;
	m_position= Vector3(position);
	m_rotation = Vector3(obj->m_rotation);
	m_scale= Vector3(obj->m_scale);

	//title.Initialize(FONT_BUTTON);
	text_pos=getTextPos();
	is_active=false;
}
void CButton::Render(){
	Sprite::Render();
	//draw text
	Text::TEXT_ARIAL->RenderTextRenderString(buttName, text_color,  text_pos.x,text_pos.y, text_scaleX, text_scaleY);

}

Vector3 CButton::getTextPos(){
	Vector3 out;
	out.x=(m_position.x+EDGE_RECTANGLE)/2/EDGE_RECTANGLE*Globals::screenWidth;
	out.y= (m_position.y+HEIGHT_RECTANGLE)/2/HEIGHT_RECTANGLE*Globals::screenHeight;
	out.x-=6*text_scaleX*(strlen(buttName)-1);
	out.x-=8*text_scaleX;
	out.y-=10*text_scaleY;
	return out;
}

void CButton::Update(float deltaTime){}

bool CButton::isTouch(int x, int y){
	Vector3 pos= m_position;
	Vector3 scale = m_scale;
	if(x < pos.x+EDGE_RECTANGLE*scale.x+1 && x > pos.x - EDGE_RECTANGLE*scale.x-1 &&
		y < pos.y+ EDGE_RECTANGLE*scale.y+1 && y > pos.y - EDGE_RECTANGLE*scale.y-1)
	{
		GetSoundInstance()->playSound(SOUND_CLICK_BUTTON);
		return true;
	}
	return false;
}
void CButton::Clean(){
}

CButton::~CButton(){
	if(!buttName) delete buttName;
}