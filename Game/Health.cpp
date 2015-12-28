#include "Health.h"
#include "define.h"
#include "SceneManager.h"
Health::Health(){
	numOfHealth= NUM_OF_HEALTH;
	m_display= new Object*[numOfHealth];
	m_score = new int[numOfHealth];
	for(int i=0; i<numOfHealth; i++){
		m_display[i]= GetSMInstance()->m_object[43+i].Clone();
		m_display[i]->m_scale=Vector3(0.05, 0.05, 1.0);
		m_display[i]->m_position= Vector3(-EDGE_RECTANGLE+40+12*i, HEIGHT_RECTANGLE-5, 0.0);
		m_score[i]=500+300*(numOfHealth-i-1);
	}
	m_run_score=0;
}

void Health::Render(){
	for(int i=0; i<numOfHealth; i++){
		m_display[i]->Render();
	}
}

void Health::Update(float deltaTime){
	
}

Health::~Health(){
	for(int i=0; i<NUM_OF_HEALTH; i++){
		delete m_display[i];
	}
	delete[] m_display;
	delete m_score;
}