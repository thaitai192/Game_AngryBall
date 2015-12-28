#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	int m_ID, numOfState;
	GLuint m_state[10];
	/*char* m_vertexFile;
	char* m_fragFile;*/
	GLuint program, vertexShader, fragmentShader;
	GLint positionAttribute;
	GLint uvAttribute;
	GLint mvpUniform;
	GLint textureLocation;
	GLint MaskLocation;
	GLint ForceUniform;
	GLint ColorUniform;
	GLint positionAttribute2;
	//GLint cubetexLocation;
	//GLint m_locBlendingmap;
	//GLint m_locTexture1,m_locTexture2,m_locTexture3;
	//GLint camUniform, fogStartUniform, fogLengthUniform, fogColorUniform;
	//GLint mUniform;
	//GLint FireTextureUniform, FireMaskUniform, Displ_texUniform, u_TimeUniform;
	GLint TimeUniform;
	Shaders();
	void enableStates();
	void disableStats();

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};