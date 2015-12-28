#include "InputManager.h"

#include "../Utilities/utilities.h" 
#include "ResourceManager.h"
#include "SceneManager.h"

InputManager* InputManager::s_Instance=NULL;
InputManager* InputManager::GetInstance(){
	if(!s_Instance){
		s_Instance = new InputManager();
	}
	return s_Instance;
}
int InputManager::Init(char* rm_link, char* sm_link, char* state_link){

	if(GetRMInstace()->Init("RM.txt")==-1) return -1;
	if(GetSMInstance()->Init("SM.txt")==-1) return -1;

	return 1;
}