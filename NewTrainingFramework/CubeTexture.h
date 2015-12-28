#ifndef __CUBETEXTURE_H__
#define __CUBETEXTURE_H__

#include "../Utilities/utilities.h" 
#include "Texture.h"
class CubeTexture:public Texture{
public:
	CubeTexture(void);
	~CubeTexture();
	char* CubeTexture::ExtractCubeMap(char* data, int width, int height, int bpp, int index);
	void Init(char* link);
};
#endif