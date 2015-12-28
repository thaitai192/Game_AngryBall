#include "Object.h"
#include "camera.h"
#include "SceneManager.h"
#include "Fog.h"
#include "define.h"


Object::Object(){
	m_model=NULL;
	m_myShaders=NULL;
	srt_update=false;
	m_texture_list=NULL;
	//m_cubeTexture_list=NULL;
	m_scale= Vector3(0,0,0);
	m_rotation=Vector3(0,0,0);
	m_position= Vector3(0,0,0);
	runtime=0.5;
}

Object* Object::Clone(){
	Object* out = new Object();
	out->m_position= m_position;
	out->m_model= m_model;
	out->numOfTexture = numOfTexture;
	out->m_rotation= m_rotation;
	out->m_scale = m_scale;
	out->m_myShaders = m_myShaders;
	out->m_texture_list = new Texture*[numOfTexture];
	for(int i=0; i<numOfTexture; i++){
		out->m_texture_list[i]= m_texture_list[i];
	}
	return out;
}
void Object::setModel(char* model_link){
	m_model= new Model();
	m_model->Init(model_link, "\"\"");
	m_scale= Vector3(1,1,1);
}
void Object::setTexture(char* texture_link){
	numOfTexture=1;
	m_texture_list= new Texture*[numOfTexture];
	m_texture_list[0]= new Texture();
	m_texture_list[0]->m_tiling=GL_REPEAT;
	m_texture_list[0]->Init(texture_link);

}
void Object::Init(char* model_link, char* texture_link){
	setModel(model_link);
	setTexture(texture_link);
}
int Object::setShaders(char * fileVertexShader, char * fileFragmentShader){
	return m_myShaders->Init(fileVertexShader, fileFragmentShader);
}

//chua cho quay
void Object::updateSRT(){
	if(!srt_update){
		Matrix S, Rx, Ry, Rz, T;
		/*S.SetIdentity();
		S.m[0][0]=m_scale.x;
		S.m[1][1]=m_scale.y;
		S.m[2][2]=m_scale.z;*/
		S.SetScale(m_scale.x, m_scale.y, m_scale.z);

		/*T.SetIdentity();
		T.m[3][0]=m_position.x;
		T.m[3][1]=m_position.y;
		T.m[3][2]=m_position.z;*/
		T.SetTranslation(m_position.x, m_position.y, m_position.z);

		Rx.SetRotationX(m_rotation.x);
		Ry.SetRotationY(m_rotation.y);
		Rz.SetRotationZ(m_rotation.z);
		m_SRT=S*Rx*Ry*Rz*T;
		srt_update=true;
	}

}

void Object::Render(){

	//	m_myShaders->enableStates();	
		//glEnable(GL_CULL_FACE);
		Camera *camera= GetSMInstance()->getCamera();
		//tinh matrix mvp
		updateSRT();
		camera->calculateVP();
		glBindBuffer(GL_ARRAY_BUFFER, m_model->vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->iboId);

		glUseProgram(m_myShaders->program);
		if(m_myShaders->positionAttribute != -1)
		{
			
			glEnableVertexAttribArray(m_myShaders->positionAttribute);
			glVertexAttribPointer(m_myShaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2), 0);
		}
		if(m_myShaders->uvAttribute!=-1){
			glEnableVertexAttribArray(m_myShaders->uvAttribute);
			glVertexAttribPointer(m_myShaders->uvAttribute, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2),(GLvoid*)sizeof(Vector3));
		}
		
		if(m_myShaders->mvpUniform!=-1){
			glUniformMatrix4fv(m_myShaders->mvpUniform,1, GL_FALSE,(GLfloat*) (m_SRT* camera->m_VP).m);
		}
		if(m_myShaders->TimeUniform!=-1)
		{
			runtime+=0.01;
			glUniform1f(m_myShaders->TimeUniform,runtime);
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if(m_myShaders->MaskLocation!=-1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture_list[0]->textureID);
			glUniform1i(m_myShaders->MaskLocation,0);
			if(m_myShaders->textureLocation!=-1)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_texture_list[1]->textureID);
				glUniform1i(m_myShaders->textureLocation,1);
			}
		}
		else
		{
			if(m_myShaders->textureLocation!=-1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_texture_list[0]->textureID);
				glUniform1i(m_myShaders->textureLocation,0);
			}
		}
		glDrawElements(GL_TRIANGLES, m_model->numberOfIndices, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//glBindTexture(GL_TEXTURE_2D,0);
		//m_myShaders->disableStats();
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
}

void Object::Rotate(Vector3 rotate){
	m_rotation+=rotate;
	srt_update=false;
}
void Object::Scale(Vector3 scale){
	m_scale+=scale;
	srt_update=false;
}
void Object::Translate(Vector3 translate){
	m_position+=translate;
	srt_update=false;
}
void Object::Update(float deltaTime){
	//Render();
}

void Object::setOpposite(Camera* c){
	Vector3 ob_ca= c->m_position-m_position;
	ob_ca.y=0;
	Vector3 ob = Vector3(0.0, 0.0, 1.0);
	float value_cosY= (ob_ca.x*ob.x+ob_ca.y*ob.y+ob_ca.z*ob.z)/(ob_ca.Length()*ob.Length());
	float rotateY= acos(value_cosY);
	
	if(c->m_position.x<m_position.x)
		m_rotation=Vector3(0.0, -rotateY, 0.0);
	else m_rotation=Vector3(0.0, rotateY, 0.0);
}


Object::~Object(){
	if(m_texture_list) delete[] m_texture_list;
	m_model=NULL;
	m_myShaders=NULL;
	//if(m_cubeTexture_list)delete[] m_cubeTexture_list;
}
