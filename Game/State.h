#ifndef __STATE_H__
#define __STATE_H__
#include "Object.h"

class State:public Object{
public:
	State();
	enum GameState{
		STATE_LOADING,
		STATE_MAINMENU,
		STATE_GAMEPLAY,
		STATE_HELP,
		STATE_OPTIONS,
		STATE_CHOOSEMAP
	};
};
#endif