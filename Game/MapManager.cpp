#include "MapManager.h"
#include "../Utilities/utilities.h" 
#include <stdio.h>
#include <string.h>
#include "define.h"
#include "log.h"

MapManager* MapManager::s_Instance=NULL;
MapManager* MapManager::GetMapManagerIS(){
	if(!s_Instance)
		s_Instance=new MapManager();
	return s_Instance;
}

int MapManager::Init(char* file){
	
	FILE* f=fopen(file, "r");
	if(!f){
		printf("Can't open file: %s", file);
		return -1;
	}
	fscanf(f,"MAPS %d\n\n",&numOfMap);
	m_map= new char*[numOfMap];
	m_level= new char*[numOfMap];
	for(int i=0; i<numOfMap; i++){
		fscanf(f,"MAP %*d\n");
		char line[100];
		fscanf(f,"SOURCE %s\n",&line);
		m_map[i]= new char[100];
		m_level[i]=new char[100];
		sprintf(m_map[i],"%s%s",DATA_PATH, strtok(line+1, "\""));
		//strcpy(m_map[i], strtok(line+1, "\""));

		fscanf(f,"LEVEL %s\n\n",&line);
		sprintf(m_level[i], "%s%s", DATA_PATH, strtok(line+1, "\""));
		//strcpy(m_level[i], strtok(line+1, "\""));
		//int t=1;
	}
	fclose(f);
	LOGI("Load MapManager is success!");
	return 0;
}

MapManager::~MapManager(){
	for(int i=0; i<numOfMap; i++){
		delete m_map[i];
	}
	delete[] m_map;
	for(int i=0; i<numOfMap; i++){
		delete m_level[i];
	}
	delete[] m_level;
}