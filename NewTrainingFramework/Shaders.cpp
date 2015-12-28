#include "Shaders.h"

Shaders::Shaders(){}
int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	uvAttribute = glGetAttribLocation(program,"a_uv");
	mvpUniform=glGetUniformLocation(program,"u_MVP");
	textureLocation=glGetUniformLocation(program,"u_texture");
	MaskLocation   =glGetUniformLocation(program,"u_mask");
	ForceUniform   =glGetUniformLocation(program,"u_force");
	TimeUniform   = glGetUniformLocation(program,"u_Time");
	ColorUniform= glGetUniformLocation(program,"u_color");
	positionAttribute2=glGetAttribLocation(program, "a_position");
	//camUniform= glGetUniformLocation(program, "u_camPosition");
	//fogStartUniform= glGetUniformLocation(program,"u_fogStart");
	//fogLengthUniform = glGetUniformLocation(program, "u_fogLength");
	//fogColorUniform= glGetUniformLocation(program, "u_fogColor");
	//mUniform = glGetUniformLocation(program, "u_M");

	////fire
	//FireTextureUniform= glGetUniformLocation(program,"FireTexture");
	//FireMaskUniform= glGetUniformLocation(program,"FireMask"); 
	//Displ_texUniform=glGetUniformLocation(program, "Displ_tex");
	//u_TimeUniform= glGetUniformLocation(program,"u_Time");
	return 0;
}

void Shaders::enableStates(){
	for(int i=0; i<numOfState; i++){
		glEnable(m_state[i]);
	}
}
void Shaders::disableStats(){
	for(int i=0; i<numOfState; i++){
		glDisable(m_state[i]);
	}
}


Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
