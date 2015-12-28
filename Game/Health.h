#ifndef __HEALTH_H__
#define __HEALTH_H__

#include "Object.h"
class Health{
public:
	int numOfHealth;
	Object** m_display;
	int *m_score, m_run_score;

	Health();
	void Render();
	void Update(float deltaTime);

	~Health();

};

#endif