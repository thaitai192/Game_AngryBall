#ifndef __FOG_H__
#define __FOG_H__

#include "../Utilities/math.h"

class Fog{
	public:
		static Fog* s_Instance;
		static Fog* getInstance();
		float fogStart;
		float fogLength;
		Vector3 fogColor;

		Fog(void);
};

#endif