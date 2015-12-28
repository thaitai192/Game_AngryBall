#ifndef __OBJECT_H__
#define __OBJECT_H__


#include "Model.h"
#include "Texture.h"
#include "../Utilities/utilities.h"
#include "../Utilities/math.h"
#include "Shaders.h"
#include "Camera.h"
//#include "CubeTexture.h"
//#include "SceneManager.h"

class SceneManager;
class Object{
public:
	int m_ID, numOfTexture;// numOfCubetexture;
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	Model *m_model;
	Shaders *m_myShaders;
	Texture **m_texture_list;
	//CubeTexture **m_cubeTexture_list;
	//CubeTexture *m_cubeTexture;

	char m_type[50], m_shape[50];
	float m_density, m_friction, m_restitution;

	Matrix m_SRT;
	bool srt_update;

	float runtime;
	

	Object();
	Object* Clone();
	void Init(char* model_link, char* texture_link);
	void setModel(char* model_link);
	void setTexture(char* texture_link);
	int setShaders(char * fileVertexShader, char * fileFragmentShader);
	void BindObject(GLuint vboId,GLuint iboId);
	void BindObjectAndIndex();
	void Rotate(Vector3 rotate);
	void Scale(Vector3 scale);
	void Translate(Vector3 translate);
	void Render();
	void Update(float deltaTime);

	void setOpposite(Camera* c);

	void updateSRT();

	

	~Object();
};

#endif