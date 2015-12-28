#ifndef __TEXT_H__
#define __TEXT_H__

#include "ft2build.h"
#include "freetype/freetype.h"
#include "../Utilities/math.h"
#include "Globals.h"
#include "Shaders.h"
#include "Texture.h"

class Text{
public:
	static Text	*TEXT_ARIAL, *TEXT_ARIALBD,*TEXT_ARIALBI,
		*TEXT_ARIALI,*TEXT_ARIBLK,*TEXT_VKUNBI;
	static void CreateFont();
	static void CleanFont();
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;
	Shaders m_myShaders;
	GLuint textureID,vboID;

	~Text();
	void Initialize(char* font);
	void RenderTextRenderString(const char *text, Vector4 color, float x, float y, float scaleX, float scaleY);

};

#endif