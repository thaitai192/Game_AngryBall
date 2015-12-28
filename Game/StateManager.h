#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include "StateBase.h"
#include <vector>
#include <stack>

using namespace std;
#include "GS_MainMenu.h"

class StateManager{
public:
	static StateBase** GameState;
	static int numOfGameState;
	static void makeGameState();
	static StateManager* s_Instance;
	static StateManager* getInstance();
	std::stack <StateBase*> S;
	StateManager();
	StateBase* GetCurrentState();
	void PushState(StateBase* state);
	void PopState();
	bool isEmpty();
	void Clear();

	~StateManager();
	
};
#define getStateIS() StateManager::getInstance()
#endif



