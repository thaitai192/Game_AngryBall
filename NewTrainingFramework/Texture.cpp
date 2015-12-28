#include "Texture.h"
#include "define.h"

Texture::Texture(){
	
}


void Texture::Init(char* link){

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	
	int iWidth, iHeight, rgb;
	char *imageData = LoadTGA(link, &iWidth, &iHeight, &rgb);
	if (rgb==24) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char*)(imageData));
	else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)(imageData));
	 
	delete imageData;

	//Setting texture parameters:
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,m_tiling);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,m_tiling);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);


}


Texture::~Texture(){
	
}