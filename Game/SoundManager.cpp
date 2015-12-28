#ifdef WIN32
#include "SoundManager.h"
#include "string.h"
#include "define.h"
#include "log.h"

SoundManager* SoundManager::s_instance= NULL;
SoundManager* SoundManager::getInstance()
{
	if(!s_instance)
	{
		s_instance= new SoundManager();
	}
	return s_instance;
}

SoundManager::SoundManager():numberMusics(0),numberSounds(0)
{
	soundSource= NULL;
	musicPlayer= NULL;
	soundEngine= createIrrKlangDevice();
	musicEngine= createIrrKlangDevice();
}

int SoundManager::Init(const char* filename, char* path)
{
	FILE *myfile= fopen(filename,"r");
	if(!myfile) 
	{
		//LOGI("can't not load %s", filename);
		printf("Error: ");
		return -1 ;
	}
	fscanf(myfile,"# MUSICS %d\n",&numberMusics);
	//LOGI("Number music %d", numberMusics);
	musicPlayer= new ISound*[numberMusics];
	musicSource = new char*[numberMusics];
	for(int i=0;i<numberMusics;i++)
	{
		fscanf(myfile,"ID %*d\n");
		fscanf(myfile,"Name %*s\n");
		musicSource[i]= new char[100];
		char link[100];
		fscanf(myfile,"FILE %s\n",&link);
		sprintf(musicSource[i], "%s%s", path, link);
		musicPlayer[i]= musicEngine->play2D(musicSource[i],true,true,true);
		//delete[] musicSource;
	}
	fscanf(myfile,"\n# SOUNDS %d\n",&numberSounds);
	soundSource= new char*[numberSounds];
	for(int i=0;i<numberSounds;i++)
	{
		fscanf(myfile,"ID %*d\n");
		fscanf(myfile,"Name %*s\n");
		soundSource[i]= new char [100];
		char link[100];
		fscanf(myfile,"FILE %s\n",link);
		sprintf(soundSource[i],"%s%s", path, link);
	}
	fclose(myfile);
	return 0;
}

void SoundManager::setVolume(float musicVolume, float soundVolume)
{
	soundEngine->setSoundVolume(soundVolume);
	musicEngine->setSoundVolume(musicVolume);
}
void SoundManager::playSound(int soundID)
{
	soundEngine->play2D(soundSource[soundID],false);
}

void SoundManager::playMusic(int musicID,bool is_fromStart,  bool is_loop)
{
		if(!is_loop) 
		{
			musicEngine->play2D(musicPlayer[musicID]->getSoundSource()->getName());
		}
		else
		{
			if(is_fromStart) musicPlayer[musicID]->setPlayPosition(0);
			musicPlayer[musicID]->setIsPaused(false);
		}
}

void SoundManager::pauseMusic(int musicID)
{
	musicPlayer[musicID]->setIsPaused(true);
}
SoundManager::~SoundManager()
{
	for(int i=0;i<numberSounds;i++)
		delete[] soundSource[i];
	delete soundSource;
	for(int i=0;i<numberMusics;i++){
		musicPlayer[i]->drop();
		delete[] musicSource[i];
	}
	delete musicSource;
	delete musicPlayer;
	musicEngine->drop();
	soundEngine->drop();
}

#else

#include "SoundManager.h"
#include "string.h"
#include "define.h"
#include "log.h"
#include "jni_base.h"

SoundManager* SoundManager::s_instance= NULL;
SoundManager* SoundManager::getInstance()
{
	//LOGI("GetInstance");
	if(!s_instance)
	{
		s_instance= new SoundManager();
	}
	return s_instance;
}

SoundManager::SoundManager():numberMusics(0),numberSounds(0)
{
	//LOGI("Create soundmanager");
	soundSource= NULL;
	//musicPlayer= NULL;

	//soundEngine= createIrrKlangDevice();
	//musicEngine= createIrrKlangDevice();
}

int SoundManager::Init(const char* filename, char* path)
{
	//LOGI("Init soundmanager");
	FILE *myfile= fopen(filename,"r");
	if(!myfile) 
	{
		//LOGI("can't not load %s", filename);
		printf("Error: ");
		return -1 ;
	}
	fscanf(myfile,"# MUSICS %d\n",&numberMusics);
	//LOGI("Number music %d", numberMusics);
	//musicPlayer= new ISound*[numberMusics];
	musicSource = new char*[numberMusics];
	for(int i=0;i<numberMusics;i++)
	{
		fscanf(myfile,"ID %*d\n");
		fscanf(myfile,"Name %*s\n");
		musicSource[i]= new char[100];
		char link[100];
		fscanf(myfile,"FILE %s\n",&link);
		sprintf(musicSource[i], "%s%s", path, link);
		//musicPlayer[i]= musicEngine->play2D(musicSource[i],true,true,true);
		//delete[] musicSource;
	}
	//LOGI("End load number music");
	fscanf(myfile,"\n# SOUNDS %d\n",&numberSounds);
	soundSource= new char*[numberSounds];
	for(int i=0;i<numberSounds;i++)
	{
		fscanf(myfile,"ID %*d\n");
		fscanf(myfile,"Name %*s\n");
		soundSource[i]= new char [100];
		char link[100];
		fscanf(myfile,"FILE %s\n",link);
		sprintf(soundSource[i],"%s%s", path, link);
	}
	fclose(myfile);
	//LOGI("end Init soundmanager");
	//LOGI("Load SoundManager is success!");
	return 0;
}

void SoundManager::setVolume(float musicVolume, float soundVolume)
{
}
void SoundManager::playSound(int soundID)
{
//LOGI("start add sound");
	nativeAddSound(soundSource[soundID]);
	//LOGI("end add sound");
	//LOGI("add Playsound");
	nativePlaySound(0, false);
	//LOGI("end add playsound");
}


void SoundManager::playMusic(int musicID,bool is_fromStart,  bool is_loop)
{
//LOGI("start Playmusic");
	nativePlayMusic(musicSource[musicID]);
//		LOGI("end Playmusic");
}

void SoundManager::pauseMusic(int musicID)
{
//LOGI("Pause music");
	nativeStopMusic();
}
SoundManager::~SoundManager()
{
	for(int i=0;i<numberSounds;i++)
		delete[] soundSource[i];
	delete soundSource;
	for(int i=0;i<numberMusics;i++){
		//musicPlayer[i]->drop();
		delete[] musicSource[i];
	}
	delete musicSource;
	//delete musicPlayer;
	//musicEngine->drop();
	//soundEngine->drop();
}

#endif