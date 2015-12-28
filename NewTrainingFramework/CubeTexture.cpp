#include "CubeTexture.h"
#include "define.h"

CubeTexture::CubeTexture(void){}
char* CubeTexture::ExtractCubeMap(char* data, int width, int height, int bpp, int index)
{
    int w = width / 4;
    int h = height / 3;
    int d = bpp / 8;

    char* extractedData = new char[w*h*d];
    memset(extractedData, 0, w*h*d);

    char* offset;
    switch ( index ) {
    case 0: // X+
        offset = &data[h*width*d + 3 * w*d];
        break;
    case 1: //X-
        offset = &data[h*width*d + w*d];
        break;
    case 2: //Y+
        offset = &data[2 * w*d];
        break;
    case 3: //Y-
        offset = &data[2 * h*width*d + 2 * w*d];
        break;
    case 4: //Z+
        offset = &data[h*width*d + 2 * w*d];
        break;
    case 5: //Z-
        offset = &data[h*width*d];
        break;
    }

    for ( int i = 0; i < h; i++ )
        memcpy(extractedData + i*w*d, offset + i*width*d, w*d);

    return extractedData;
}

void CubeTexture::Init(char* link){
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	
	int iWidth, iHeight, rgb;
	char *imageData = LoadTGA(link, &iWidth, &iHeight, &rgb);
	for(int i=0; i<6;i++){
	
		char* colorBuffer= ExtractCubeMap(imageData, iWidth, iHeight, rgb,i);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, RGB_RGBA(rgb),iWidth/4, iHeight/3, 0, GL_RGB,GL_UNSIGNED_BYTE, colorBuffer);
		delete colorBuffer;
	}
	delete imageData;
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

}
CubeTexture::~CubeTexture(){}