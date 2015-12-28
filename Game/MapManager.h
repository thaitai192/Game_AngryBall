#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

class MapManager{
public:
	static MapManager* s_Instance;
	static MapManager* GetMapManagerIS();
	
	int numOfMap;
	char** m_map;
	int currentmap;
	int mine_max_map;
	char** m_level;
	int Init(char* file);
	~MapManager();
};
#define GetMapIS() MapManager::GetMapManagerIS()
#endif