#pragma once

#include <stdio.h>
#include "irrklang.h"

using namespace irrklang;


class SoundManager
{
public:
	static SoundManager *s_instance;
	static SoundManager *getInstance();
	char** soundSource, **musicSource;
	ISound **musicPlayer;
	int numberMusics, numberSounds;
	ISoundEngine *musicEngine, *soundEngine;
	SoundManager();
	int Init(const char* filename, char* path);
	void playMusic(int musicID,bool is_fromStart=true,bool is_loop= true);
	void pauseMusic(int musicID);
	void playSound(int soundID);
	void setVolume(float musicVolume=1.0, float soundVolume=1.0);
	~SoundManager();
};

#define GetSoundInstance() SoundManager::getInstance()