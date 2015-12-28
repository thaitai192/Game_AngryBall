#include "StateManager.h"
#include "GS_WelcomeScreen.h"
#include "GS_OptionMenu.h"
#include "GS_Help.h"
#include "GS_Stage.h"
#include "GS_HighScore.h"
#include "log.h"
#include <stack>

using namespace std;


StateManager* StateManager::s_Instance=NULL;
StateManager* StateManager::getInstance(){
	if(!s_Instance) s_Instance= new StateManager();
	return s_Instance;
}
StateManager::StateManager(){
	
}

StateBase* StateManager::GetCurrentState(){
	if(!isEmpty()){
		return S.top();
	}
	else{
		LOGI("Het state, khong get curent dc");
		exit(true);
	}
}


void StateManager::PushState(StateBase* state){
	S.push(state);
}

void StateManager::PopState(){
	if(!isEmpty()){
		StateBase* tmp = GetCurrentState();
		tmp->Clean();
		delete tmp;
		S.pop();
		
	}
	else {
		LOGI("het state, khong pop duoc");
		exit(true);
	}

}
bool StateManager::isEmpty(){
	return S.empty();
}

StateManager::~StateManager(){
	while(!isEmpty()){
		//StateBase* tmp = GetCurrentState();
		PopState();
		//tmp->Clean();
		//delete tmp;
	}
}