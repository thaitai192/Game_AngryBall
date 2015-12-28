#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__


class InputManager{
public:
	static InputManager* s_Instance;
	static InputManager* GetInstance();
	int Init(char* rm_link, char* sm_link, char* state_link);
};
#define GetIM_IS() InputManager::GetInstance()
#endif