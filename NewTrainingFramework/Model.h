#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdio.h>
#include "Vertex2.h"
#include "../Utilities/utilities.h" 
#include <stdio.h>
#include "../Utilities/math.h"
#include <math.h>
class Model{
public:
	int m_ID;
	int numberOfVertices;
	int numberOfIndices;
	GLuint vboId,iboId;

	Model();
	void loadHeightmap(char *link, Vertex2 vertices[]);
	float getHeightAt(unsigned char* heightmapData, Vector2 uv, int length);
	void Init(char* pos_link, char* heightmap_link);
	~Model();
	
};
#endif