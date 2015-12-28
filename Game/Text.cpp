#include "Text.h"
#include "ResourceManager.h"
#include "../Utilities/utilities.h"
#include "define.h"

void Text::Initialize(char* font){
	if(FT_Init_FreeType(&m_ft))
	{
		printf("Could not init freetype library\n");
		return;
	}
	if(FT_New_Face(m_ft, font, 0, & m_face)) {
		printf("Could not open font %s\n",font);
		return;
	}
	FT_Set_Pixel_Sizes(m_face, 0, 48);
	m_glyphSlot = m_face->glyph;
	char link_vs[100], link_fs[100];
	sprintf(link_vs, "%s%s", DATA_PATH, "Shaders/TextShaderVS.vs");
	sprintf(link_fs, "%s%s", DATA_PATH, "Shaders/TextShaderFS.fs");
	m_myShaders.Init(link_vs,link_fs);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	//m_texture = new Texture();
	
}

void Text::RenderTextRenderString(const char *text, Vector4 color, float x, float y, float scaleX, float scaleY){

	// use glProgram, bind texture & pass color uniform here
	glUseProgram(m_myShaders.program);

	if(m_myShaders.ColorUniform!=-1){
		glUniform4f(m_myShaders.ColorUniform, color.x, color.y, color.z, color.w);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	float sx = 1.0f / Globals::screenWidth * scaleX;
	float sy = 1.0f / Globals::screenHeight * scaleY;
	x = -1.0f + 2.0f * x/Globals::screenWidth;
	y = -1.0f + 2.0f * y/Globals::screenHeight;
	for(const char *p = text; *p; p++)
	{
	glBindTexture(GL_TEXTURE_2D, textureID);

	if(FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
	{
	continue;
	}
	glTexImage2D(GL_TEXTURE_2D,0,GL_ALPHA,m_glyphSlot->bitmap.width,m_glyphSlot->bitmap.rows
		,0,GL_ALPHA,GL_UNSIGNED_BYTE,m_glyphSlot->bitmap.buffer);
	float x2 = x + m_glyphSlot->bitmap_left * sx;
	float y2 = -y - m_glyphSlot->bitmap_top * sy;
	float w = m_glyphSlot->bitmap.width * sx;
	float h = m_glyphSlot->bitmap.rows * sy;
	GLfloat box[4][4] = {
	{x2, -y2 , 0, 0},
	{x2 + w, -y2 , 1, 0},
	{x2, -y2 - h, 0, 1},
	{x2 + w, -y2 - h, 1, 1},
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
	
	if(m_myShaders.textureLocation!=-1){
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(m_myShaders.textureLocation,1);
	}

	if(m_myShaders.positionAttribute2!=-1){
		glEnableVertexAttribArray(m_myShaders.positionAttribute2);
		glVertexAttribPointer(m_myShaders.positionAttribute2, 4, GL_FLOAT, GL_FALSE,4*sizeof(GLfloat),0);
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	x += (m_glyphSlot->advance.x >> 6) * sx;
	y += (m_glyphSlot->advance.y >> 6) * sy;
	}
	glDisable(GL_BLEND);
}

Text::~Text(){
}
Text* Text::TEXT_ARIAL = NULL;
Text* Text::TEXT_ARIALBD = NULL;
Text* Text::TEXT_ARIALBI = NULL;
Text* Text::TEXT_ARIALI = NULL;
Text* Text::TEXT_ARIBLK = NULL;
Text* Text::TEXT_VKUNBI = NULL;
void Text::CreateFont(){
	TEXT_ARIAL = new Text();
	TEXT_ARIALBD = new Text();
	TEXT_ARIALBI = new Text();
	TEXT_ARIALI = new Text();
	TEXT_ARIBLK = new Text();
	TEXT_VKUNBI = new Text();
	char link[100];
	sprintf(link, "%s%s", DATA_PATH, "data/arial.ttf");
	TEXT_ARIAL->Initialize(link);
	sprintf(link, "%s%s", DATA_PATH, "data/arialbd.ttf");
	TEXT_ARIALBD->Initialize(link);
	sprintf(link, "%s%s", DATA_PATH, "data/arialbi.ttf");
	TEXT_ARIALBI->Initialize(link);
	sprintf(link, "%s%s", DATA_PATH, "data/ariali.ttf");
	TEXT_ARIALI->Initialize(link);
	sprintf(link, "%s%s", DATA_PATH, "data/ariblk.ttf");
	TEXT_ARIBLK->Initialize(link);
	sprintf(link, "%s%s", DATA_PATH, "data/VKUNBI.ttf");
	TEXT_VKUNBI->Initialize(link);


}
void Text::CleanFont(){
	delete TEXT_ARIAL;
	delete TEXT_ARIALBD;
	delete TEXT_ARIALBI;
	delete TEXT_ARIALI;
	delete TEXT_ARIBLK;
	delete TEXT_VKUNBI;
}