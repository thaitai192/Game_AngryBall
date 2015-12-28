#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "../Utilities/utilities.h"

class Texture{
public:
	int m_ID;

	GLint m_tiling;
	GLuint textureID;

	Texture();

	~Texture();
	void Init(char* link);
};
#endif