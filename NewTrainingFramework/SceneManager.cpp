
#include "SceneManager.h"
#include "define.h"
#include "log.h"

SceneManager::SceneManager(){
	keyevent=0;
	camera_active=0;
}

SceneManager* SceneManager::s_Instance=NULL;
SceneManager* SceneManager::getInstance(){
	if(!s_Instance){
		s_Instance= new SceneManager();
	}
	return s_Instance;
}

void SceneManager::setKeyevent(unsigned char key,bool bIsPressed){
	//set camera
	/*if(bIsPressed){
		switch(key){
			case 'A': case 'a':{			keyevent|=MOVE_LEFT; break;}
			case 'D': case 'd':{			keyevent|=MOVE_RIGHT; break;}
			case 'W': case 'w':{			keyevent|=MOVE_FORWARD; break;}
			case 'S': case 's':{			keyevent|=MOVE_BACKWARD; break;}
			case VK_UP:{		keyevent|=ROTATION_UP; break;}
			case VK_DOWN:{		keyevent|=ROTATION_DOWN; break;}
			case VK_RIGHT:{		keyevent|=ROTATION_RIGHT; break;}
			case VK_LEFT:{		keyevent|=ROTATION_LEFT; break;}
			case '1':					camera_active=0; break;
			case '2':					camera_active=1; break;
			case '3':					camera_active=2; break;
		}
	}else{
		switch(key){
			case 'A': case 'a':{			keyevent&=~MOVE_LEFT; break;}
			case 'D': case 'd':{			keyevent&=~MOVE_RIGHT; break;}
			case 'W': case 'w':{			keyevent&=~MOVE_FORWARD; break;}
			case 'S': case 's':{			keyevent&=~MOVE_BACKWARD; break;}
			case VK_UP:{		keyevent&=~ROTATION_UP; break;}
			case VK_DOWN:{		keyevent&=~ROTATION_DOWN; break;}
			case VK_RIGHT:{		keyevent&=~ROTATION_RIGHT; break;}
			case VK_LEFT:{		keyevent&=~ROTATION_LEFT; break;}
			case '1':					keyevent=0; break;
			case '2':					keyevent=0; break;
			case '3':					keyevent=0; break;
		}
	}	*/
}
int SceneManager::Init(char* file){
	FILE *f=fopen(file, "r");
	if(!f) {
		printf("Can't not open file %s\n",file);
		return -1;}
	fscanf(f, "#Object: %d\n\n", &numOfObject);
	m_object = new Object[numOfObject];

	for(int i=0; i<numOfObject; i++){
		fscanf(f, "NAME %*s\n");

		fscanf(f,"ID %d\n",&m_object[i].m_ID);
		int tmp;
		fscanf(f,"MODEL %d\n",&tmp);
		//get model
		for(int k=0; k<GetRMInstace()->numOfModel; k++){
			if(tmp==GetRMInstace()->m_model[k].m_ID) {
				m_object[i].m_model=&GetRMInstace()->m_model[k];
				break;
			}
		}
		fscanf(f,"TEXTURES %d\n",&(m_object[i].numOfTexture));
		if(m_object[i].numOfTexture!=0) m_object[i].m_texture_list=new Texture*[m_object[i].numOfTexture];
		for(int j=0; j<m_object[i].numOfTexture; j++){
			int texture_id;
			fscanf(f,"TEXTURE %d\n",&texture_id);
			for(int k=0; k<GetRMInstace()->numOfTexture; k++){
					if(texture_id==GetRMInstace()->m_texture[k].m_ID){
					m_object[i].m_texture_list[j]=&GetRMInstace()->m_texture[k];
					break;
				}
			}
			
		}

		//set 1 texture ve cho object
		//if(m_object[i].numOfTexture) m_object[i].m_texture=m_object[i].m_texture_list[0];
		
		
		/*fscanf(f,"CUBETEXTURES %*d\n");
		if(m_object[i].numOfCubetexture!=0)
			m_object[i].m_cubeTexture_list= new CubeTexture*[m_object[i].numOfCubetexture];
		for(int j=0; j<m_object[i].numOfCubetexture; j++){
			int cube_id;
			fscanf(f,"CUBETEX %d\n",&cube_id);
			for(int k=0; k<GetRMInstace()->numOfCubeTexture; k++){
				if(cube_id==GetRMInstace()->m_cubeTexture[k].m_ID){
					m_object[i].m_cubeTexture_list[j]=&GetRMInstace()->m_cubeTexture[k];
					break;
				}
			}
		}*/
		//if(m_object[i].numOfCubetexture!=0)m_object[i].m_cubeTexture=m_object[i].m_cubeTexture_list[0];
		int shader_id;
		fscanf(f,"SHADER %d\n",&shader_id);
		for(int j=0; j<GetRMInstace()->numOfShader; j++){
			if(shader_id==GetRMInstace()->m_shader[j].m_ID){
				m_object[i].m_myShaders=&GetRMInstace()->m_shader[j];
				break;
			}
		}
		//bo qua lightpost
		fscanf(f,"LIGHTS %*d\n");
		fscanf(f,"POSITION %f, %f, %f\n",&m_object[i].m_position.x,&m_object[i].m_position.y,&m_object[i].m_position.z); 
		fscanf(f,"ROTATION %f, %f, %f\n", &m_object[i].m_rotation.x, &m_object[i].m_rotation.y,&m_object[i].m_rotation.z);
		fscanf(f,"SCALE %f, %f, %f\n", &m_object[i].m_scale.x,&m_object[i].m_scale.y,&m_object[i].m_scale.z);
		fscanf(f,"TYPE %s\n", &m_object[i].m_type);
		fscanf(f,"SHAPE %s\n",&m_object[i].m_shape);
		fscanf(f,"DENSITY %f\n",&m_object[i].m_density);
		fscanf(f,"FRICTION %f\n", &m_object[i].m_friction);
		fscanf(f,"RESTITUTION %f\n\n",&m_object[i].m_restitution);
	}
	fscanf(f,"#LIGHTS\n");
	fscanf(f,"AmbientColor %*f,%*f,%*f\n");
	fscanf(f,"AmbientWeight %*f\n");
	fscanf(f, "LightsCount: %*d\n\n");

	fscanf(f,"#CAMERA %d\n",&numOfCamera);
	m_camera=new Camera*[numOfCamera];
	
	for(int i=0; i<numOfCamera; i++){
		m_camera[i]=new Camera();
	//m_camera= Camera::getCamera();
		fscanf(f,"ID %d\n", &(m_camera[i]->m_ID));
		fscanf(f,"UP %f, %f, %f\n",&(m_camera[i]->m_up.x),&(m_camera[i]->m_up.y),&(m_camera[i]->m_up.z));
		fscanf(f, "POSITION %f,%f,%f\n",&(m_camera[i]->m_position.x),&(m_camera[i]->m_position.y),&(m_camera[i]->m_position.z));
		fscanf(f,"TARGET %f,%f,%f\n",&(m_camera[i]->m_target.x),&(m_camera[i]->m_target.y),&(m_camera[i]->m_target.z));
		fscanf(f, "NEAR %f\n", &(m_camera[i]->m_near));
		fscanf(f,"FAR %f\n", &(m_camera[i]->m_far));
		fscanf(f,"FOV %f\n",&(m_camera[i]->m_fov));
		fscanf(f,"SPEED %f\n",&(m_camera[i]->m_speed));

		//dua position camera vao vram
		fscanf(f,"\n");
	}
	fclose(f);
	LOGI("Load SM is success!");
	return 0;

}
void SceneManager::Render(){
	for(int i=0; i<numOfObject; i++){
		m_object[i].Render();
	}
}
void SceneManager::Update(float deltaTime){
	
	getCamera()->update(deltaTime, keyevent);
	for(int i=0; i<numOfObject; i++){
		m_object[i].Update(deltaTime);
	}

	//xu ly lua xoay
	
}

Camera* SceneManager::getCamera(){
	return m_camera[camera_active];
}
SceneManager::~SceneManager(){
	delete[] m_object;
	for(int i=0; i<numOfCamera; i++){
		delete m_camera[i];
	}
	delete m_camera;
}
