#include "ResourceManager.h"
#include "../Utilities/utilities.h" 
#include <string.h>
#include "log.h"

ResourceManager* ResourceManager::s_Instance=NULL;
ResourceManager* ResourceManager::getInstance(){
	if(!s_Instance){
		s_Instance= new ResourceManager();
	}
	return s_Instance;
}
ResourceManager::ResourceManager(){
	m_model=NULL;
	m_texture=NULL;
	//m_cubeTexture=NULL;
	m_shader=NULL;
}
int ResourceManager::Init(char *file, char* path){
	FILE *f=fopen(file, "r");
	if(f==NULL) {
		printf("Can't not open file %s\n",file);
		return -1;	
	}
	fscanf(f,"#Models: %d\n",&numOfModel);
	
	char line[100];
	m_model= new Model[numOfModel]();
	for(int i=0; i<numOfModel; i++){
		fscanf(f,"ID %d\n",&m_model[i].m_ID);
		fgets(line,100,f);
		char heightdata[100];
		fscanf(f,"HEIGHT MAP %s\n",&heightdata);
		char model_link[100];
		sprintf(model_link, "%s%s", path, strtok(line+6, "\""));
		m_model[i].Init(model_link,heightdata);

		//doc height map
	}

	fscanf(f,"\n#2D Textures: %d\n",&numOfTexture);
	m_texture=new Texture[numOfTexture];
	for(int i=0; i<numOfTexture; i++){
		fscanf(f,"ID %d\n",&m_texture[i].m_ID);
		fgets(line, 100, f);

		char texture_link[100];
		sprintf(texture_link, "%s%s" ,path,strtok(line+6, "\""));
		m_texture[i].Init(texture_link);
		fscanf(f,"TILING %s\n",&line);
		//fgets(line,100,f);

		if(strcmp(line, "CLAMP")==0){
			m_texture[i].m_tiling= GL_CLAMP_TO_EDGE;
		}
		else m_texture[i].m_tiling=GL_REPEAT;
		
	}
	//fscanf(f,"\n#Cube Textures: %d\n",&numOfCubeTexture);
	//m_cubeTexture= new CubeTexture[numOfCubeTexture];
	/*for(int i=0; i<numOfCubeTexture; i++){
		fscanf(f,"ID %d\n", &(m_cubeTexture[i].m_ID));
		fgets(line, 100, f);

		m_cubeTexture[i].Init(strtok(line+6, "\""));
		fscanf(f,"TILING %s\n",&line);

		if(strcmp(line, "CLAMP")==0){
			m_cubeTexture[i].m_tiling= GL_CLAMP_TO_EDGE;
		}
		else m_cubeTexture[i].m_tiling=GL_REPEAT;
	}*/
	fscanf(f, "\n#Shaders: %d\n", &numOfShader);
	m_shader= new Shaders[numOfShader];
	for(int i=0; i<numOfShader; i++){
		fscanf(f,"ID %d\n",&m_shader[i].m_ID);
		char fs[100],vs[100];
		fgets(line,100,f);
		sprintf(vs, "%s%s", path, strtok(line+4,"\""));
		fgets(line,100,f);
		sprintf(fs, "%s%s", path, strtok(line+4,"\""));
		m_shader[i].Init(vs,fs);
		fscanf(f,"STATES %d\n",&m_shader[i].numOfState);
		for(int j=0; j<m_shader[i].numOfState; j++){
			fscanf(f,"STATE %s\n",&line);
			//strcpy(line, strtok(line+6,""));
			if(strcmp(line, "DEPTH_TEST")==0) {
				m_shader[i].m_state[j]=GL_DEPTH_TEST;
			}
			else if(strcmp(line, "ALPHA")==0) m_shader[i].m_state[j]=GL_ALPHA;
			else m_shader[i].m_state[j]=GL_CULL_FACE;
			
		}
	}
	fclose(f);
	LOGI("Load RM is success!");
	return 0;
}

ResourceManager::~ResourceManager(){
	delete []m_model;
	delete []m_texture;
	delete []m_shader;
	//if(m_cubeTexture) delete []m_cubeTexture;
}